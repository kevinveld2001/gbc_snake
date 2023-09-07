#include <gb/gb.h>
#include <stdio.h>
#include <rand.h>
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
BOOLEAN check_apple_collision();

struct SnakeBody {
    int x;
    int y;
    int tile;
    int direction;
};
struct SnakeBody snake[256];

uint8_t snakeHead = 2;
uint8_t snakeTail = 0;


void init_snake() {
    snake[0].x = 2;
    snake[0].y = 9;
    snake[0].tile = SNAKE_TAIL_RIGHT;
    snake[0].direction = DIRECTION_RIGHT;

    snake[1].x = 3;
    snake[1].y = 9;
    snake[1].tile = SNAKE_BODY_HORISONTAL;
    snake[1].direction = DIRECTION_RIGHT;

    snake[2].x = 4;
    snake[2].y = 9;
    snake[2].tile = SNAKE_HEAD_TILE_RIGHT;
    snake[2].direction = DIRECTION_RIGHT;

    for (int i = 0; i < 3; i++) {
        set_bkg_tile_xy(snake[i].x, snake[i].y, snake[i].tile);
    }

}

void get_user_input() {
    if (joypad() & J_UP && direction != DIRECTION_DOWN) direction = DIRECTION_UP;
    else if (joypad() & J_RIGHT && direction != DIRECTION_LEFT) direction = DIRECTION_RIGHT;
    else if (joypad() & J_DOWN && direction != DIRECTION_UP) direction = DIRECTION_DOWN;
    else if (joypad() & J_LEFT && direction != DIRECTION_RIGHT) direction = DIRECTION_LEFT;
}

void update_snake() {
    //add body at head position
    int newx = snake[snakeHead].x;
    int newy = snake[snakeHead].y;
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


    if (snake[snakeHead].direction == DIRECTION_UP || snake[snakeHead].direction == DIRECTION_DOWN) {
        snake[snakeHead].tile = SNAKE_BODY_VERTICAL;
    } else {
        snake[snakeHead].tile = SNAKE_BODY_HORISONTAL;
    }
    if ((snake[snakeHead].direction == DIRECTION_UP && direction == DIRECTION_RIGHT)
    || (snake[snakeHead].direction == DIRECTION_LEFT && direction == DIRECTION_DOWN)) {
        snake[snakeHead].tile = 21;
    }
    if ((snake[snakeHead].direction == DIRECTION_UP && direction == DIRECTION_LEFT)
    || (snake[snakeHead].direction == DIRECTION_RIGHT && direction == DIRECTION_DOWN)) {
        snake[snakeHead].tile = 22;
    }
    if ((snake[snakeHead].direction == DIRECTION_RIGHT && direction == DIRECTION_UP)
    || (snake[snakeHead].direction == DIRECTION_DOWN && direction == DIRECTION_LEFT)) {
        snake[snakeHead].tile = 23;
    }
    if ((snake[snakeHead].direction == DIRECTION_LEFT && direction == DIRECTION_UP)
    || (snake[snakeHead].direction == DIRECTION_DOWN && direction == DIRECTION_RIGHT)) {
        snake[snakeHead].tile = 24;
    }

    
    snakeHead++;
    snake[snakeHead].x = newx;
    snake[snakeHead].y = newy;
    snake[snakeHead].tile = newSnakeHeadTile;
    snake[snakeHead].direction = direction;

    //remove tail
    if (check_apple_collision()) {

    } else {
        snakeTail++;
        snake[snakeTail].tile = SNAKE_TAIL_UP + snake[snakeTail + 1].direction;
    }

    //update snake
    set_bkg_tile_xy(snake[snakeHead-1].x, snake[snakeHead-1].y, snake[snakeHead-1].tile);
    set_bkg_tile_xy(snake[snakeHead].x, snake[snakeHead].y, snake[snakeHead].tile);
    set_bkg_tile_xy(snake[snakeTail-1].x, snake[snakeTail-1].y, 0);
    set_bkg_tile_xy(snake[snakeTail].x, snake[snakeTail].y, snake[snakeTail].tile);
}
void spawn_new_apple() {
    int randomXApplePos = 0;
    int randomYApplePos = 0;
    while (1) {
        randomXApplePos = rand() % 20;
        randomYApplePos = rand() % 18;
        if (get_bkg_tile_xy(randomXApplePos, randomYApplePos) == 0) {
            VBK_REG = 1;
            int colorPallet = get_bkg_tile_xy(randomXApplePos, randomYApplePos);
            VBK_REG = 0;
            if (colorPallet == 1) break;
        }
    }
    VBK_REG = 1;
    set_bkg_tile_xy(randomXApplePos, randomYApplePos, 3);
    VBK_REG = 0;
    set_bkg_tile_xy(randomXApplePos, randomYApplePos, 1);
}

BOOLEAN check_apple_collision() {
    int tile = get_bkg_tile_xy(snake[snakeHead].x, snake[snakeHead].y);
    if (tile == 1) {
        //change pallet of apple
        VBK_REG = 1;
        set_bkg_tile_xy(snake[snakeHead].x, snake[snakeHead].y, 1);
        VBK_REG = 0;

        spawn_new_apple();
        return TRUE;
    }
    return FALSE;
}