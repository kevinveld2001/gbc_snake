#include <gb/gb.h>
#include <stdio.h>
#include <gb/cgb.h>
#include "snake.h"

#define DIRECTION_UP 0
#define DIRECTION_RIGHT 1
#define DIRECTION_DOWN 2
#define DIRECTION_LEFT 3

#define SNAKE_TAIL_UP 15
#define SNAKE_TAIL_RIGHT 16
#define SNAKE_TAIL_DOWN 17
#define SNAKE_TAIL_LEFT 18

#define SNAKE_BODY_HORISONTAL 20
#define SNAKE_BODY_VERTICAL 19

#define SNAKE_HEAD_TILE_UP 25
#define SNAKE_HEAD_TILE_RIGHT 26
#define SNAKE_HEAD_TILE_DOWN 27
#define SNAKE_HEAD_TILE_LEFT 28

int direction = DIRECTION_RIGHT;

struct SnakeBody {
    int x;
    int y;
    int tile;
    int direction;
    struct SnakeBody *prev;
    struct SnakeBody *next;
};

struct SnakeBody snakeHead;
struct SnakeBody snakeTail;


void init_snake() {
    snakeTail.x = 2;
    snakeTail.y = 9;
    snakeTail.tile = SNAKE_TAIL_RIGHT;
    snakeTail.direction = DIRECTION_RIGHT;
    snakeTail.prev = NULL;
    snakeTail.next = NULL;


    struct SnakeBody snakeBody = {3, 9, SNAKE_BODY_HORISONTAL, DIRECTION_RIGHT, &snakeTail, NULL};
    snakeTail.next = &snakeBody;

    snakeHead.x = 4;
    snakeHead.y = 9;
    snakeHead.tile = SNAKE_HEAD_TILE_RIGHT;
    snakeHead.direction = DIRECTION_RIGHT;
    snakeHead.prev = &snakeBody;
    snakeHead.next = NULL;
    snakeBody.next = &snakeHead;

    //display snake
    struct SnakeBody *current = &snakeHead;
    while (current != NULL) {
        set_bkg_tile_xy(current->x, current->y, current->tile);
        current = current->prev;
    }
}

void get_user_input() {
    if (joypad() & J_UP) direction = DIRECTION_UP;
    else if (joypad() & J_RIGHT) direction = DIRECTION_RIGHT;
    else if (joypad() & J_DOWN) direction = DIRECTION_DOWN;
    else if (joypad() & J_LEFT) direction = DIRECTION_LEFT;
}

void update_snake() {
    //add body at head position
    int newx = snakeHead.x;
    int newy = snakeHead.y;
    int newSnakeHeadTile = 0;
    if (direction == DIRECTION_UP) {
        newy--;
        newSnakeHeadTile = SNAKE_HEAD_TILE_UP;
    } else if (direction == DIRECTION_RIGHT) {
        newx++;
        newSnakeHeadTile = SNAKE_HEAD_TILE_RIGHT;
    } else if (direction == DIRECTION_DOWN) {
        newy++;
        newSnakeHeadTile = SNAKE_HEAD_TILE_DOWN;
    } else if (direction == DIRECTION_LEFT) {
        newx--;
        newSnakeHeadTile = SNAKE_HEAD_TILE_LEFT;
    }

    struct SnakeBody newHead = {newx, newy, newSnakeHeadTile, direction, &snakeHead, NULL};
    snakeHead.next = &newHead;
    if (snakeHead.direction == DIRECTION_UP || snakeHead.direction == DIRECTION_DOWN) {
        snakeHead.tile = SNAKE_BODY_VERTICAL;
    } else {
        snakeHead.tile = SNAKE_BODY_HORISONTAL;
    }
    if ((snakeHead.direction == DIRECTION_UP && direction == DIRECTION_RIGHT)
    || (snakeHead.direction == DIRECTION_LEFT && direction == DIRECTION_DOWN)) {
        snakeHead.tile = 21;
    }
    if ((snakeHead.direction == DIRECTION_UP && direction == DIRECTION_LEFT)
    || (snakeHead.direction == DIRECTION_RIGHT && direction == DIRECTION_DOWN)) {
        snakeHead.tile = 22;
    }
    if ((snakeHead.direction == DIRECTION_RIGHT && direction == DIRECTION_UP)
    || (snakeHead.direction == DIRECTION_DOWN && direction == DIRECTION_LEFT)) {
        snakeHead.tile = 23;
    }
    if ((snakeHead.direction == DIRECTION_LEFT && direction == DIRECTION_UP)
    || (snakeHead.direction == DIRECTION_DOWN && direction == DIRECTION_RIGHT)) {
        snakeHead.tile = 24;
    }

    set_bkg_tile_xy(snakeHead.x, snakeHead.y, snakeHead.tile);
    
    snakeHead = *&newHead;
    set_bkg_tile_xy(snakeHead.x, snakeHead.y, snakeHead.tile);

    //remove tail
    // set_bkg_tile_xy(snakeTail.x, snakeTail.y, 0);
    // snakeTail = *snakeTail.next;
    // snakeTail.prev = NULL;
    // snakeTail.tile = SNAKE_TAIL_UP + snakeTail.direction;
    // set_bkg_tile_xy(snakeTail.x, snakeTail.y, snakeTail.tile);
}