好，既然已经确认是 **TIM2 中断里画时间条导致的花屏**，那就好办了 👍

核心思路只有一句话：

> **中断里只改“状态/时间变量 + 设一个标志”，真正的 `CLEAR_TIMER / DRAW_TIMER` 只在主循环里做。**

这样既不会和主循环抢 FSMC/LCD，又能保证时间更新“够及时”。

---

## 1. 第一步：加一个“需要刷新时间”的标志

在全局变量区加一个标志（记得 `volatile`）：

```c
volatile uint8_t need_redraw_timer = 0;
```

你原来就有：

```c
volatile int time = 1801;
```

这个可以继续用。

---

## 2. 第二步：改 TIM2_IRQHandler —— 不再画 LCD，只动变量 + 设标志

把现在这个中断：

```c
void TIM2_IRQHandler(void)
{
    if(TIM2->SR & 1<<0)
    {
        if(time == -9)
        {
            status = 4;
            TIM2->CR1 &= 0xFFFFFFFE;
        }
        else{
            CLEAR_TIMER();
            DRAW_TIMER(time);
            time-=10;
        }
    }
    TIM2->SR &= ~(1<<0);
}
```

改成：

```c
void TIM2_IRQHandler(void)
{
    if (TIM2->SR & (1<<0))
    {
        if (time == -9)
        {
            status = 4;
            TIM2->CR1 &= ~1;      // 关闭定时器
        }
        else
        {
            time -= 10;           // 只改时间变量
            need_redraw_timer = 1; // 告诉主循环“该重画时间了”
        }
        TIM2->SR &= ~(1<<0);      // 清除更新中断标志
    }
}
```

> ✅ 现在中断里不会再去动 `lcd_wr_reg/lcd_wr_data`，和主循环完全解耦。

---

## 3. 第三步：在主循环里专门处理这个标志

你在 `status == 3` 的地方，有这么一段：

```c
else if (status == 3)
{
    tim2_init(7999, 8999);
    while(1)
    {
        if(status != 3)
        {
            break;
        }
        if(TASKS[0] == 1)
        {
            ...
            CLEAR_TIMER();
            DRAW_TIMER(time);
            ...
        }
        if(TASKS[1] == 1)
        {
            ...
        }
        ...
    }
}
```

在这个 `while(1)` 里面加入对 `need_redraw_timer` 的检查就行了，例如：

```c
else if (status == 3)
{
    tim2_init(7999, 8999);
    while (1)
    {
        if (status != 3)
        {
            break;
        }

        // ① 先处理计时器的重画请求
        if (need_redraw_timer)
        {
            need_redraw_timer = 0;   // 先清标志
            CLEAR_TIMER();
            DRAW_TIMER(time);
        }

        // ② 再处理原来的 TASKS[0] / TASKS[1] 之类
        if (TASKS[0] == 1)
        {
            TASKS[0] = 3;
            ...
            CHARACTER_MOVE_NEW(&character1, instruction1);
            delay(100000);
            CHARACTER_MOVE_NEW(&character2, instruction2);
            delay(1000000);
            ...
            UPDATE_BULLET_STATUS(&character1, &character2);
            HP_PACKS_FALLING();
        }

        if (TASKS[1] == 1)
        {
            TASKS[1] = 3001;
            INIT_HP_PACKS_DROP();
        }

        last_status = 3;
        DS1_Off;
        DS0_Off;
    }
}
```

这样：

* **中断只负责“时间走格子”**（`time -= 10`），
* **主循环负责“看到标志就重画一次时间条”**。

---

## 4. “能不能保证及时？”——关键是别在主循环里卡太久

你现在主循环里有这种东西：

```c
CHARACTER_MOVE_NEW(&character1, instruction1);
delay(100000);
CHARACTER_MOVE_NEW(&character2, instruction2);
delay(1000000);
```

这两个 `delay` 是**硬阻塞延时**，期间 CPU 什么都不干，当然也不会去检查 `need_redraw_timer`。
所以：

* 如果 TIM2 每 0.1 秒中断一次，而你在主循环一次循环里 `delay` 总共耗时 > 0.1 秒，
* 那时间变量 `time` 会正常往下减，但是**画面上的计时条会“卡一会儿才动一下”**。

### 怎么改善？

**短期、改动最小的做法：**

* 把这两个 `delay` 适当减小（比如先都减 10 倍），让主循环“跑得更快一些”，这样就能更频繁地检查 `need_redraw_timer`，时间刷新会更平滑。

**长期、正统的做法（以后有空可以搞）：**

* 你已经有 `systick_init_10ms();`，很可能有一个全局的时间基（比如一个 `tick_10ms` 递增）。
* 把“人物移动速度”“子弹速度”改成：

  * 记录上次移动的时间戳 `last_move_time`；
  * 在主循环里每次看 `if (now - last_move_time >= 某个间隔)` 再动一步；
  * 中间不用 `delay()`，让主循环保持高频循环。

这样：

* 主循环一秒能跑上千圈；
* 每一圈都能快速检查 `need_redraw_timer`，
* 时间条刷新就几乎是“立刻”的，而且游戏动作也会更丝滑。

---

## 5. 小结一口气帮你捋一下：

1. **中断里不要画 LCD**：TIM2_IRQHandler 只改 `time` + 设 `need_redraw_timer=1`。
2. **主循环里轮询这个标志**：看到 1 就执行 `CLEAR_TIMER(); DRAW_TIMER(time);`。
3. **想更“及时”：减少大 `delay()`，或用 SysTick 做非阻塞节拍控制**。

你先按上面的“标志 + 主循环绘制”改一版跑跑看，基本可以同时解决：

* 花屏 / 不规则黑块（因为不再有中断和主循环抢 FSMC）；
* 计时条更新不同步的问题（只要主循环不被 delay 卡死，刷新就会很快）。

如果你愿意，我也可以帮你把 `delay(100000)` / `delay(1000000)` 那一段改成基于 `SysTick` 的“非阻塞移动逻辑”版本，让整个游戏 loop 变成一个又快又稳定的状态机。
