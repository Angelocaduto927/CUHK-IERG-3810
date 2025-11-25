#pragma once
#include "stm32f10x.h"

#define SPEED 10
#define LENGTH 10

typedef struct {
  int x, y;
	int rate;
	int facing;
}BULLET;

typedef struct {
    BULLET bullets[100];
    size_t size;
} BulletList;

extern BulletList bulletlist1;
extern BulletList bulletlist2;

void Bullet_list_init(BulletList* list);

//void Bullet_list_free(BulletList* list);

void Bullet_list_push(BulletList* list, BULLET entity);

void Bullet_list_remove_at(BulletList* list, size_t index);

const BULLET* Bullet_list_get(const BulletList* list, size_t index);

size_t Bullet_list_size(const BulletList* list);


