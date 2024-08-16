#ifndef SNAKE_SNAKE_H
#define SNAKE_SNAKE_H
#include "main.h"
#include "oled.h"
#include <sys/types.h>
//地图定义
#define MAP_WIDTH 32
#define MAP_HEIGHT 12
//数据定义
#define WALL 1
#define SNAKE 2
#define FOOD 3
#define EMPTY 0
//方向定义
typedef enum {
    UP = 100,
    DOWN,
    LEFT,
    RIGHT
} Direction;
//点定义
typedef struct {
    uint8_t x;
    uint8_t y;
}Point;
//蛇定义
typedef struct {
    uint8_t length;
    Direction direction;
    Point body[MAP_WIDTH*MAP_HEIGHT];
}Snake;



void CreateMap();
void PrintData();
void GenerateFood();
void InitSnake();
void UpdateSnake();
void ChangeDirection(Direction new_direction);
#endif //SNAKE_SNAKE_H

