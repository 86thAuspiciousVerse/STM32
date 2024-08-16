#include "snake.h"

#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include "font.h"
#include "tim.h"
#include "stdio.h"


uint8_t map[MAP_WIDTH][MAP_HEIGHT];//地图数据，包含蛇和食物和墙
Snake snake;//全局蛇变量
char score[];//分数
bool directionChanged = false;
//生成地图
void CreateMap() {
    OLED_Init();//初始化OLED
    OLED_NewFrame();//新建帧
    for (uint8_t i=0; i<MAP_WIDTH; i++) {
        for (uint8_t j=0; j<MAP_HEIGHT; j++) {
            if (i==0 || i== MAP_WIDTH-1 || j==0 || j== MAP_HEIGHT-1) {
                map[i][j] = WALL;//墙
            }else {
                map[i][j] = EMPTY;//空白
            }
        }
    }
    OLED_PrintString(0,0,"得分：",&font16x16,OLED_COLOR_NORMAL);
}
//生成食物
void GenerateFood() {
    uint8_t x, y;
    srand(__HAL_TIM_GET_COUNTER(&htim3));//随机数种子设置
    do {
        x = rand() % (MAP_WIDTH - 2) + 1;
        y = rand() % (MAP_HEIGHT - 2) + 1;
    } while (map[x][y] != EMPTY);
    map[x][y] = FOOD;
}
//初始化蛇
void InitSnake(){
    snake.length = 3;//蛇的长度
    snake.direction = DOWN;//蛇的方向
    for (uint8_t i=0;i<snake.length;i++) {
        snake.body[i].x = 3+i;
        snake.body[i].y = 3;
        map[snake.body[i].x][snake.body[i].y] = SNAKE;//设定为蛇
    }//初始化蛇的位置,位置是固定的，在3,3到5,3
    GenerateFood();//生成食物
}

void UpdateSnake() {

    Point head = snake.body[0]; // 蛇头
    switch (snake.direction) {
        case UP:
            head.y--;
            break;
        case DOWN:
            head.y++;
            break;
        case LEFT:
            head.x--;
            break;
        case RIGHT:
            head.x++;
            break;
    } // 根据方向更新蛇头的位置

    if (map[head.x][head.y] == WALL || map[head.x][head.y] == SNAKE) {
        // 撞墙和撞自己
        return;
    }

    if (map[head.x][head.y] == FOOD) {
        // 吃到食物
        snake.length++;
        sprintf(score,"%d",snake.length-3);
        GenerateFood();
    } else {
        // 清除蛇尾
        Point tail = snake.body[snake.length - 1];
        map[tail.x][tail.y] = EMPTY;
    }

    // 移动蛇
    for (uint8_t i = snake.length - 1; i > 0; i--) {
        snake.body[i] = snake.body[i - 1];
    }
    snake.body[0] = head;
    map[head.x][head.y] = SNAKE; // 更新蛇头的位置
    directionChanged = false; // 重置标志位

}

void ChangeDirection(Direction new_direction) {
        snake.direction = new_direction;
        directionChanged = true; // 设置标志位
}
//打印数据
void PrintData() {
    for (uint8_t i = 0; i < MAP_WIDTH; i++) {
        for (uint8_t j = 0; j < MAP_HEIGHT; j++) {
            if (map[i][j] == WALL || map[i][j] == FOOD) {
                OLED_DrawFilledRectangle(i * 4, (j + 4) * 4, 3, 4, OLED_COLOR_NORMAL);
            } else if (map[i][j] == EMPTY) {
                OLED_DrawFilledRectangle(i * 4, (j + 4) * 4, 3, 4, OLED_COLOR_REVERSED);
            } else if (map[i][j] == SNAKE) {
                OLED_DrawRectangle(i * 4, (j + 4) * 4, 3, 3, OLED_COLOR_NORMAL);
            }
        }
    }
    OLED_PrintString(47, 0, score, &font16x16, OLED_COLOR_NORMAL);
    OLED_ShowFrame();
}




