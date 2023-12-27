#define LILYGO_TDISPLAY_AMOLED_SERIES

#include "LilyGo_AMOLED.h"      //To use LilyGo AMOLED series screens, please include <LilyGo_AMOLED.h>
#include <TFT_eSPI.h>   //https://github.com/Bodmer/TFT_eSPI

#include "smallFont.h"
#include "middleFont.h"
#include "font.h"

TFT_eSPI tft = TFT_eSPI();
TFT_eSprite spr = TFT_eSprite(&tft);
LilyGo_Class amoled;

#define WIDTH  amoled.height()
#define HEIGHT amoled.width()

static int16_t x, y;
unsigned short grays[15];
bool deb=false;
bool deb2=false;
byte number=0;
bool autoMode=true;

int posX[8]={25,85,145,205,265,325,385,445};
int posY=150;
bool value[8]={0,0,0,0,0,0,0,0};
unsigned short col[2]={0x8851,0x0B91};
unsigned short linecol[2]={0x8410,0x7E7C};

unsigned long savedTime=0;
int period=400;
String state[2]={"OFF","ON"};

void setup()
{
    amoled.begin();
    amoled.setBrightness(110);
    spr.createSprite(WIDTH, HEIGHT);
    spr.setSwapBytes(1);

       int co=225;
       for(int i=0;i<15;i++)
        {
          grays[i]=tft.color565(co, co, co);
          co=co-15;
        }
}

void draw()
{
  spr.fillSprite(TFT_BLACK);
  spr.setTextDatum(4);

  
  for(int i=0;i<8;i++)
  {
      spr.loadFont(middleFont);
      spr.fillRoundRect(posX[i],posY,54,54,4,col[value[i]]);
      spr.fillCircle(posX[i]+27,posY-10,4,linecol[value[i]]);

      spr.drawLine(posX[i]+27,posY-10,posX[i]+27,posY-46+(i*4),linecol[value[i]]);
      spr.drawLine(posX[i]+27,posY-46+(i*4),472-((7-i)*8),posY-46+(i*4),linecol[value[i]]);
      spr.drawLine(472-((7-i)*8),posY-46+(i*4),472-((7-i)*8),posY-58,linecol[value[i]]);
      spr.fillCircle(472-((7-i)*8),posY-58,2,linecol[value[i]]);
      //spr.fillCircle(472-((7-i)*8),posY-68,2,grays[6]);

      
   spr.setTextColor(TFT_WHITE,col[value[i]]);
   spr.drawString(String(value[i]),posX[i]+27,posY+30); 
   spr.setTextColor(grays[4],TFT_BLACK); 
   spr.unloadFont();
   spr.loadFont(smallFont);
   spr.drawString(String((int)pow(2,7-i)),posX[i]+27,posY+74); }
  
   
   spr.setTextColor(TFT_ORANGE,TFT_BLACK); 
   spr.drawString("DECADE",414,14);
   spr.drawString("HEX",254,20);
   spr.drawString("ASCII",248,66);
   spr.setTextColor(grays[4],TFT_BLACK); 
   spr.drawString("AUTO",170,15);
   spr.unloadFont();
   spr.fillRect(150,28,42,14,0x0B91);
   spr.setTextColor(grays[0],0x0B91);
   spr.drawString(state[autoMode],172,35,2);
  

   spr.fillRoundRect(posX[6],30,120,54,4,TFT_ORANGE);
   spr.fillRoundRect(posX[4]+20,0,70,40,3,grays[10]);
   spr.fillRoundRect(posX[4]+20,44,70,40,3,grays[10]);
   spr.fillCircle(posX[6]-16,57,4,0x7E7C);
   spr.fillCircle(posX[6]-16,20,4,0x7E7C);
   spr.fillCircle(posX[6]-108,57,3,0x7E7C);
   spr.fillCircle(posX[6]-108,20,3,0x7E7C);
   spr.fillRect(posX[6]-17,20,3,34,0x7E7C);

   spr.fillRect(posX[6]-25,18,6,3,0x7E7C);
   spr.fillRect(posX[6]-25,56,20,3,0x7E7C);
  

  
  spr.loadFont(middleFont);
  spr.setTextColor(TFT_WHITE,TFT_BLACK); 
  spr.drawString("BINARY",84,26);
  spr.drawString("CONVERT",98,72);
  spr.setTextColor(TFT_BLACK,TFT_ORANGE); 
  spr.drawString(String(number),posX[6]+60,60);
  spr.setTextColor(grays[0],grays[10]); 
  spr.unloadFont();
  spr.loadFont(fontt);
  //spr.drawString("HEX",posX[3]+110,6);
  spr.drawString("0x"+String(number,HEX),posX[3]+114,24);
  spr.unloadFont();
  spr.drawString(String((char)number),posX[3]+114,64,4);
  amoled.pushColors(0, 0, WIDTH, HEIGHT, (uint16_t *)spr.getPointer());
}



void loop()
{
 
   bool touched = amoled.getPoint(&x, &y);
   if(touched)
   {if(!deb2)
   {deb2=true; if(x>580) {autoMode=!autoMode; number=0;
   for(int i=0;i<8;i++)
   value[i]=bitRead(number, 7-i);
   draw();
   } }
   }else deb2=0;
   

   if(!autoMode)
   if(touched)
   {if(!deb)
   {deb=true;
    for(int i=0;i<8;i++)
    if(x>posX[i] && x<posX[i]+60 && y>posY &&y<posY+60)
    {value[i]=!value[i]; bitWrite(number, 7-i, value[i]);}
    
   }draw();
   }else deb=false;

   if(autoMode)
   {
   draw();
   if(millis()>savedTime+period)
   {number++;
   savedTime=millis();
   if(number==256) number=0;
   for(int i=0;i<8;i++)
   value[i]=bitRead(number, 7-i);
   }
   
   }

   
  

}




