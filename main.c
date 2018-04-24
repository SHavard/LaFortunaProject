#include "lcd.h"
#include <stdlib.h>

#define BG GREEN
#define HOLE_HEIGHT LCDHEIGHT / 8
#define HOLE_WIDTH LCDHEIGHT / 6
const rectangle SCREEN = {0,LCDHEIGHT,0,LCDWIDTH};

void init_game(void);
void background(uint16_t colour);
void drawHole(rectangle r);
void drawMole(uint8_t hole);

const rectangle left = {10, 10 + HOLE_WIDTH, LCDWIDTH/2 - HOLE_HEIGHT/2, LCDWIDTH/2 + HOLE_HEIGHT/2};
const rectangle right = {LCDHEIGHT - HOLE_WIDTH - 10, LCDHEIGHT - 10, LCDWIDTH/2 - HOLE_HEIGHT/2, LCDWIDTH/2 + HOLE_HEIGHT/2};
const rectangle centre = {LCDHEIGHT/2 - HOLE_WIDTH/2, LCDHEIGHT/2 + HOLE_WIDTH/2, LCDWIDTH/2 - HOLE_HEIGHT/2, LCDWIDTH/2 + HOLE_HEIGHT/2};
const rectangle top = {LCDHEIGHT/2 - HOLE_WIDTH/2, LCDHEIGHT/2 + HOLE_WIDTH/2, 10, 10 + HOLE_HEIGHT};
const rectangle bottom = {LCDHEIGHT/2 - HOLE_WIDTH/2, LCDHEIGHT/2 + HOLE_WIDTH/2, LCDWIDTH-10-HOLE_HEIGHT, LCDWIDTH-10};

void main(void)
{
  init_lcd();
  
  set_frame_rate_hz(100);
  
  init_game();
  
  for (;;){
    
    int random = rand() % 5;
    // drawMole(random);
    
  }
}

void init_game(void)
{
  background(BG);
  /* left mole hole */
  drawHole(left);
  /* right mole hole */
  drawHole(right);
  /* centre mole hole */
  drawHole(centre);
  /* top mole hole */
  drawHole(top);
  /* bottom mole hole */
  drawHole(bottom);
}

void background(uint16_t colour)
{
  fill_rectangle(SCREEN, colour);
}

void drawHole(rectangle r)
{
  rectangle hole_border = {r.left - 4, r.right + 4, r.top - 4, r.bottom + 4};
  rectangle hole_w = {r.left, r.right, r.top + 10, r.bottom - 10};
  rectangle hole_h = {r.left + 10, r.right - 10, r.top, r.bottom};
  fill_rectangle(hole_border, BROWN);
  fill_rectangle(hole_w, BLACK);
  fill_rectangle(hole_h, BLACK);
}

void drawMole(uint8_t hole){
  rectangle r;
  switch (hole){
    /*left*/
    case 0: {
      r.left = 8;
      r.right = 8+HOLE_WIDTH+2;
      r.top = (LCDWIDTH/2 - (HOLE_HEIGHT)/2)-2;
      r.bottom = (LCDWIDTH/2 - (HOLE_HEIGHT)/2)+HOLE_HEIGHT+2;
      fill_rectangle(r, RED); 
      break;
    }
    /*right*/
    case 1: {
      r.left = LCDHEIGHT - (HOLE_WIDTH) - 10;
      r.right = LCDHEIGHT - (HOLE_WIDTH) - 8 + HOLE_WIDTH;
      r.top = (LCDWIDTH/2 - (HOLE_HEIGHT)/2)-2;
      r.bottom = (LCDWIDTH/2 - (HOLE_HEIGHT)/2)+HOLE_HEIGHT+2;
      fill_rectangle(r, ORANGE); 
      break;
    }
    /*top*/
    case 2:  {
      r.left = LCDHEIGHT/2 - (HOLE_WIDTH)/2 -2;
      r.right = LCDHEIGHT/2 - (HOLE_WIDTH)/2 + HOLE_WIDTH +2;
      r.top = 8;
      r.bottom = 10+HOLE_HEIGHT;
      fill_rectangle(r, BLACK); 
      break;
    }
    /*bottom*/
    case 3:  {
      r.left = LCDHEIGHT/2 - (HOLE_WIDTH)/2 -2;
      r.right = LCDHEIGHT/2 - (HOLE_WIDTH)/2 + HOLE_WIDTH +2;
      r.top = LCDWIDTH - HOLE_HEIGHT - 12;
      r.bottom = LCDWIDTH - 10;
      fill_rectangle(r, PURPLE); 
      break;
    }
    /*centre*/
    case 4:  {
      r.left = LCDHEIGHT/2 - (HOLE_WIDTH)/2 -2;
      r.right = LCDHEIGHT/2 - (HOLE_WIDTH)/2 + HOLE_WIDTH +2;
      r.top = (LCDWIDTH/2 - (HOLE_HEIGHT)/2)-2;
      r.bottom = (LCDWIDTH/2 - (HOLE_HEIGHT)/2)+HOLE_HEIGHT+2;
      fill_rectangle(r, BLUE); 
      break;
    }
  }
}












