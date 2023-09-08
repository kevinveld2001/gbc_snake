#include <gb/gb.h>
#include <gb/cgb.h>
#include "score.h"

#define NUMBER_ZERO 5

int score = 0;

void init_score() {
    score = 0;
    set_bkg_tile_xy(2, 0, NUMBER_ZERO);
    set_bkg_tile_xy(3, 0, NUMBER_ZERO);
    set_bkg_tile_xy(4, 0, NUMBER_ZERO);
}


void score_add(int points) {
    score += points;
    int hundreds = score / 100;
    int tens = (score - hundreds * 100) / 10;
    int ones = score - hundreds * 100 - tens * 10;
    set_bkg_tile_xy(2, 0, NUMBER_ZERO + hundreds);
    set_bkg_tile_xy(3, 0, NUMBER_ZERO + tens);
    set_bkg_tile_xy(4, 0, NUMBER_ZERO + ones);
}