#include "lcd.h"
#include <stdlib.h>
#include <util/delay.h>
#include "ruota.h"
#include <avr/io.h>
#include <avr/interrupt.h>

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

uint16_t spawn_delay = 500;

struct Board {
  uint8_t leftMole : 1;
  uint8_t rightMole : 1;
  uint8_t topMole : 1;
  uint8_t bottomMole : 1;
  uint8_t centreMole : 1;
} game_board;

void main(void)
{
  init_lcd();
  
  init_game();
  
  /* game loop */
  for (;;)
  {
    
    /* pick a random spawn location */
    int random = rand() % 5;

    /* prevent spawn at location of existing mole */
    drawMole(random);
    
    /* variable delay between spawns */
    int i;
    for (i = 0; i < spawn_delay/10; i++)
    {
      _delay_ms(10);
    }
    
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
  
  game_board.leftMole=0;
  game_board.rightMole=0;
  game_board.topMole=0;
  game_board.bottomMole=0;
  game_board.centreMole=0;
  
  spawn_delay = 500;
  
  TCCR0A = _BV(WGM01);
  TCCR0B = _BV(CS01) | _BV(CS00);
  
  OCR0A = (uint8_t)(F_CPU / (64.0 * 1000) - 1);
  
  TIMSK0 |= _BV(OCIE0A);
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
  fill_rectangle(hole_border, SANDY_BROWN);
  fill_rectangle(hole_w, BLACK);
  fill_rectangle(hole_h, BLACK);
}

void drawMole(uint8_t hole){
  rectangle r = {0,0,0,0};
  switch (hole){
    /*left*/
    case 0: {
      if (game_board.leftMole==1){
        break;
      }
      game_board.leftMole=1;
      r = left;
      break;
    }
    /*right*/
    case 1: {
      if (game_board.rightMole==1){
        break;
      }
      game_board.rightMole=1;
      r = right;
      break;
    }
    /*top*/
    case 2:  {
      if (game_board.topMole==1){
        break;
      }
      game_board.topMole=1;
      r = top;
      break;
    }
    /*bottom*/
    case 3:  {
      if (game_board.bottomMole==1){
        break;
      }
      game_board.bottomMole=1;
      r = bottom;
      break;
    }
    /*centre*/
    case 4:  {
      if (game_board.centreMole==1){
        break;
      }
      game_board.centreMole=1;
      r = centre;
      break;
    }
  }
  
  rectangle body = {r.left + HOLE_WIDTH/4, r.right - HOLE_WIDTH/4, r.top - 10, r.bottom - 10};
  fill_rectangle(body, BROWN);
  
}

ISR(TIMER0_COMPA_vect)
{
  scan_switches(0);
}












