
#define LILYGO_TDISPLAY_AMOLED_SERIES

#include "LilyGo_AMOLED.h"      //To use LilyGo AMOLED series screens, please include <LilyGo_AMOLED.h>
#include <TFT_eSPI.h>   //https://github.com/Bodmer/TFT_eSPI

TFT_eSPI tft = TFT_eSPI();
TFT_eSprite spr = TFT_eSprite(&tft);
LilyGo_Class amoled;

#define WIDTH  amoled.height()
#define HEIGHT amoled.width()


void setup()
{
    amoled.begin();
    spr.createSprite(WIDTH, HEIGHT);
    spr.setSwapBytes(1);
}

void draw(int x, int y)
{
  spr.fillSprite(TFT_BLACK);
  spr.drawString("HELLO WORLD"+String(x)+"    "+String(y),100,100,4);
  amoled.pushColors(0, 0, WIDTH, HEIGHT, (uint16_t *)spr.getPointer());
}

void loop()
{
   static int16_t x, y;
   bool touched = amoled.getPoint(&x, &y);
   if(touched)
   draw(x,y);

}




