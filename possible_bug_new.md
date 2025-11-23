我先直接说结论：
**从你这几大坨代码看，99% 是软件画错了，不是屏坏。**
而且我已经能看到几个**很有嫌疑、会在“游戏进行一段时间后，边缘出现不规则黑块”**的地方。

我帮你拆成两大类问题讲：

---

## 一眼就能看出来的两类高危点

### 1⃣ 在中断里画 LCD（跟主循环一起抢总线）——极大嫌疑犯

你在 **TIM2_IRQHandler** 里面直接画 LCD：

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
            CLEAR_TIMER();        // 这里
            DRAW_TIMER(time);    // 这里
            time-=10;
        }
    }
    TIM2->SR &= ~(1<<0);
}
```

而主循环在 `status == 3` 的时候也在不停地：

* 移动角色、画角色（`DRAW_CHARACTER`）
* 更新子弹（`UPDATE_BULLET_STATUS` → 肯定会 `Draw_Bullet` / `CLEAR_BULLET`）
* 掉血包（`HP_PACKS_FALLING` → `Draw_HealPack` / `CLEAR_HP`）

也就是说：**主循环和 TIM2 中断是同时在操作 `lcd_wr_reg/lcd_wr_data` 的。**

这会发生什么？

* 主循环刚刚执行到 `lcd_wr_reg(0x2A);` / `lcd_wr_reg(0x2B);` 设置好窗口；
* 还没写完那一块数据，**中断进来了**，TIM2 把窗口改成清计时条的那一块，又写了一堆数据；
* 中断退出回到主循环，主循环继续往它“以为”的窗口里写数据，但窗口已经被改过了，于是**一堆像素写到了完全不该去的地方**。

结果就是：
👉 **屏幕某处出现一块“不规则、边缘乱七八糟”的黑斑/花斑**，而且之后你不再覆盖那一块，它就一直在。

> ✋ 这类“中断+主循环同时画 LCD”导致的花屏/乱块，是 STM32+FSMC+LCD 项目里非常典型的坑。

**这和你说的现象完全契合：**

* 开始正常（没画太多东西、中断还没和主循环“撞车”）；
* 游戏进行一段时间（人动、子弹飞、计时器在跑），某一帧刚好撞在一起 → 出现一块不规则黑东西；
* 之后那块一直不变。

🔧 **强烈建议：先做一个改动验证这点——中断里不画 LCD：**

```c
volatile uint8_t need_redraw_timer = 0;

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
            time -= 10;
            need_redraw_timer = 1;   // 只打个标记
        }
    }
    TIM2->SR &= ~(1<<0);
}

// 在 main 的 status==3 那个 while(1) 里加：
if (need_redraw_timer) {
    need_redraw_timer = 0;
    CLEAR_TIMER();
    DRAW_TIMER(time);
}
```

这样所有 `lcd_*` 调用**都在主循环里执行**，再跑一会儿看那个不规则黑块还会不会出现。
如果明显好转/消失，那根因就是“中断里画 LCD + 主循环同时画”。

---

### 2⃣ 你有很多 `lcd_fillRectangle` 在靠边缘画，容易越界或画到奇怪位置

看你所有的绘图函数：

```c
void CLEAR_CHARACTER(CHARACTER character)
{
    if(character.facing == -1){
        lcd_fillRectangle(c_white, character.x-6 , 25, character.y-8, 20);
    }
    if(character.facing == 1){
        lcd_fillRectangle(c_white, character.x-6 , 25, character.y-11, 20);
    }
}

void CLEAR_HP(HP hp)
{
    lcd_fillRectangle(c_white, hp.x-7 , 15, hp.y-8, 16);
}

void CLEAR_BULLET(BULLET bullet)
{
    lcd_fillRectangle(c_white, bullet.x , 2, bullet.y, 10);
}

void Draw_Bullet(u16 x, u16 y, u16 color)
{
    lcd_fillRectangle(color, x, 2, y, 10);
}
```

以及一堆角色绘制：

```c
coordy = y + 18 - i; 
coordx = x - (11 - j)*d;
drawDotForChar(tempcolor, coordy, coordx);   // 最后进 lcd_drawDot(coordy, coordx)
```

这些有什么共同点？

* 很多都是在**人物、子弹靠近屏幕边缘时**画矩形/像素；
* 一旦 `character.x`、`character.y`、`bullet.x`、`bullet.y` 超出你“想象的界限”，就会：

  * 要么 start_x/start_y 变成负数（在 u16 下直接变成 655xx 这种巨大的值）；
  * 要么 start_x + length_x - 1 > 239 或 start_y + length_y - 1 > 319（超出屏幕范围）。

举个具体的例子（假设屏幕是 240×320，x:0~239，y:0~319）：

* 子弹飞到最右边，`bullet.x = 239`；
* `Draw_Bullet(bullet.x, bullet.y, ...)` → `lcd_fillRectangle(color, 239, 2, y, 10);`
* 在 `lcd_fillRectangle` 里计算 X 终点：`239 + 2 - 1 = 240`，已经超出 0~239 范围。
  不同 LCD 控制器的行为不完全一样：有的会截断，有的会 wrap，有的直接无视，都会有“边缘诡异线条/块”的可能。

再比如角色清除区域：

```c
lcd_fillRectangle(c_white, character.x-6 , 25, character.y-8, 20);
```

如果角色靠近最上边，`character.x` 只有 3：

* `character.x - 6` 在 `u16` 下变成 `65533`，你等于让 FSMC/ILI9341 以“65533 这一列”为起点画了 25 列……
* 然后地址设置、数据写入全部乱飞，最后就形成一些你完全想象不到形状的“花块/黑块”。

**你现在看见的“不规则黑块”，很有可能就是很多次这种“越界矩形画错地方”的叠加结果。**

---

## 建议你加一个“安全版矩形”做调试

不用一下子全重构，可以先加一个 wrapper，专门用来查越界：

```c
// 假定屏幕分辨率是 240 x 320：x:0~239, y:0~319
#define LCD_MAX_X 240
#define LCD_MAX_Y 320

void lcd_fillRectangle_safe(u16 color, int start_x, int length_x,
                            int start_y, int length_y)
{
    // 记录原始参数可以打 log 或点灯
    // original_* = ...

    // 简单裁剪 + 越界检测
    if (length_x <= 0 || length_y <= 0) return;

    if (start_x < 0) {
        length_x += start_x;   // 减去负的那一段
        start_x = 0;
    }
    if (start_y < 0) {
        length_y += start_y;
        start_y = 0;
    }

    if (start_x >= LCD_MAX_X || start_y >= LCD_MAX_Y) {
        // 明显越界了，可以在这里点亮 LED 看看有没有进来
        return;
    }

    if (start_x + length_x > LCD_MAX_X) {
        length_x = LCD_MAX_X - start_x;
    }
    if (start_y + length_y > LCD_MAX_Y) {
        length_y = LCD_MAX_Y - start_y;
    }

    // 最终安全范围
    lcd_fillRectangle(color, (u16)start_x, (u16)length_x, (u16)start_y, (u16)length_y);
}
```

然后把所有这些地方临时换掉：

```c
// 原来：
lcd_fillRectangle(c_white, character.x-6 , 25, character.y-8, 20);

// 调试：
lcd_fillRectangle_safe(c_white, character.x-6 , 25, character.y-8, 20);
```

子弹、HP 包、清背景之类都换成 `_safe` 版本。

如果换完之后：

* 黑块不再出现 → 十有八九是原来某些时候参数越界了，被你悄悄裁掉了；
* 你还可以在上面 `if (start_x >= LCD_MAX_X || start_y >= LCD_MAX_Y)` 里点个 LED 或 `USART` 打一行日志，看**到底是谁传了奇怪的坐标**。

---

## 还有一些小问题，虽然不是黑块的主因，但顺手提一下

### 🔹 DRAW_CHARACTER 里武器判断的 strcmp 逻辑反了

```c
if (strcmp(character.weapon.name, "Pistol"))
{
    weapon = 0;
}
else if(strcmp(character.weapon.name, "Vandal"))
{
    weapon = 1;
}
...
```

`strcmp` 相等时返回 0，不相等返回非 0。
你现在的写法是：

* 名字正好是 "Pistol" → `strcmp(...) == 0` → if(0) 不进，结果 `weapon` 还是初始的 0；
* 名字是 "Vandal" → 第一行 `strcmp("Vandal","Pistol") != 0` → if(非0) 进，`weapon=0`，根本不会走到后面的 `else if`。

也就是说：**不管你名字是什么，weapon 基本永远是 0（pistol）**。
虽然这不会直接导致黑块，但行为肯定不是你想要的。

应该写成：

```c
if (strcmp(character.weapon.name, "Pistol") == 0)
    weapon = 0;
else if (strcmp(character.weapon.name, "Vandal") == 0)
    weapon = 1;
...
```

---

## 一步到位的“排雷顺序”建议

我帮你排个顺序，你可以按这个来：

1. **先彻底避免在中断里画 LCD**

   * 把 `TIM2_IRQHandler` 里的 `CLEAR_TIMER()` / `DRAW_TIMER()` 换成设置一个 `need_redraw_timer` 标志，在主循环里画。
   * 这样先消除“主循环 + IRQ 抢 FSMC”的不确定因素。

2. **引入 `lcd_fillRectangle_safe`，替换所有动态对象的清画函数**

   * `CLEAR_CHARACTER` / `CLEAR_BULLET` / `CLEAR_HP` / `Draw_Bullet` / `Draw_HealPack` 等等。
   * 看有没有频繁触发越界裁剪（可以在里面点灯/打 log）。

3. **检查角色 / 子弹位置的边界限制**

   * 在 `CHARACTER_MOVE_NEW`、`UPDATE_BULLET_STATUS`、`HP_PACKS_FALLING` 里，确保：

     * `0 <= character.x <= 239`，`0 <= character.y <= 319`（or 相反，看你约定）；
     * 子弹的 `x` 保证 `x <= 238`，`y <= 309`，保证加上 width/height 不会出界。

4. 写一个**纯 LCD 压力测试程序**（只跑 `lcd_fillRectangle` 四种颜色循环）验证硬件：

   * 如果那种纯刷屏程序跑一小时都没黑块，硬件基本无辜。

---

## 最后再回答你一句：「是硬件问题吗？」

以你现在给的所有代码和现象：

* 一开始正常，运行一段时间后才出现；
* 黑块形状不规则；
* 你有**中断里画 LCD + 边界不做保护的清除/子弹/角色矩形**；

👉 **我会把锅优先扣在软件头上，而不是屏坏。**
硬件坏一般是“固定位置、固定形状、一上电就不对”，或者“晃排线就闪来闪去”。

先把上面这两个大坑（中断画 LCD、矩形越界）排干净，再看还会不会出现黑块，基本就能定性了。
