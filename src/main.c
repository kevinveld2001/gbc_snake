#include <gb/gb.h>
#include <stdio.h>
#include <gb/cgb.h>
#include "assets/background.h"
#include "assets/tiles.h"
#include "snake.h"

const UWORD backgroundPalette[] = {
    tilesCGBPal0c0, tilesCGBPal0c1, tilesCGBPal0c2, tilesCGBPal0c3,
    tilesCGBPal1c0, tilesCGBPal1c1, tilesCGBPal1c2, tilesCGBPal1c3,
    tilesCGBPal2c0, tilesCGBPal2c1, tilesCGBPal2c2, tilesCGBPal2c3,
    tilesCGBPal3c0, tilesCGBPal3c1, tilesCGBPal3c2, tilesCGBPal3c3,
    tilesCGBPal4c0, tilesCGBPal4c1, tilesCGBPal4c2, tilesCGBPal4c3,
    tilesCGBPal5c0, tilesCGBPal5c1, tilesCGBPal5c2, tilesCGBPal5c3,
    tilesCGBPal6c0, tilesCGBPal6c1, tilesCGBPal6c2, tilesCGBPal6c3,
    tilesCGBPal7c0, tilesCGBPal7c1, tilesCGBPal7c2, tilesCGBPal7c3,
    tilesSGBPal2c0, tilesSGBPal2c1, tilesSGBPal2c2, tilesSGBPal2c3,
    tilesSGBPal3c0, tilesSGBPal3c1, tilesSGBPal3c2, tilesSGBPal3c3
};

void main() 
{
    set_bkg_palette(0, 8, &backgroundPalette[0]);
    set_bkg_data(0, 30, tiles);

    VBK_REG = 1;
    set_bkg_tiles(0, 0, backgroundWidth, backgroundHeight, backgroundPLN1);
    VBK_REG = 0;
    set_bkg_tiles(0, 0, backgroundWidth, backgroundHeight, backgroundPLN0);

    SHOW_BKG;
    DISPLAY_ON;
    init_snake();

    int timecounter = 0;
    while (1)
    {
        timecounter++;
        get_user_input();
        if (timecounter < 1000) continue;
        timecounter = 0;
        wait_vbl_done();
        update_snake();

    }
    

}