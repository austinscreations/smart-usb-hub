/* animations for neopixel control */ 

#ifndef neopixel_h
#define neopixel_h

void colorWipe(uint8_t r,uint8_t g,uint8_t b,uint8_t w){
  for(int a=0; a<4; a++) {
    strip.setPixelColor(a,r,g,b,w);         //  Set pixel's color (in RAM)
    strip.show();
   }
//  neo_update[c] = false;
}

void colorSet(uint8_t c, uint8_t r,uint8_t g,uint8_t b,uint8_t w){
    strip.setPixelColor(c,r,g,b,w);         //  Set pixel's color (in RAM)
    strip.show();
  neo_update[c] = false;
}

void doubleflash(uint8_t c, uint8_t r,uint8_t g,uint8_t b,uint8_t w,uint8_t r1,uint8_t g1,uint8_t b1,uint8_t w1)
{
    if ((millis() - lastdouble) > 100)
    {
      doubletime++;
      if (doubletime >= 14){doubletime = 0;}
      lastdouble = millis();
    }

    if (doubletime == 0)
    {
      strip.setPixelColor(c,r,g,b,w);         //  Set pixel's color (in RAM)
      strip.show();
    }
    if (doubletime == 1)
    {
      strip.setPixelColor(c,0,0,0,0);         //  Set pixel's color (in RAM)
      strip.show();
    }
    if (doubletime == 2)
    {
      strip.setPixelColor(c,r,g,b,w);         //  Set pixel's color (in RAM)
      strip.show();
    }
    if (doubletime == 8)
    {
      strip.setPixelColor(c,r1,g1,b1,w1);         //  Set pixel's color (in RAM)
      strip.show();
    }
}

void doubleflashHUB(uint8_t r,uint8_t g,uint8_t b,uint8_t w,uint8_t r1,uint8_t g1,uint8_t b1,uint8_t w1)
{
    if ((millis() - lastdouble) > 100)
    {
      doubletime++;
      if (doubletime >= 14){doubletime = 0;}
      lastdouble = millis();
    }

    if (doubletime == 0)
    {
      colorWipe(r,g,b,w);         //  Set pixel's color (in RAM)
      strip.show();
    }
    if (doubletime == 1)
    {
      colorWipe(0,0,0,0);         //  Set pixel's color (in RAM)
      strip.show();
    }
    if (doubletime == 2)
    {
      colorWipe(r,g,b,w);         //  Set pixel's color (in RAM)
      strip.show();
    }
    if (doubletime == 8)
    {
      colorWipe(r1,g1,b1,w1);    //  Set pixel's color (in RAM)
      strip.show();
    }
}

/* animation for over / under volt */
void ringupdate()
{
   if ((millis() - prevringMillis) > ringspeed) 
   {
     prevringMillis = millis();
     fwd++;
     if (fwd == 4){fwd = 0;}
   }
}

void voltring(uint8_t r1,uint8_t g1,uint8_t b1,uint8_t w1,uint8_t r2,uint8_t g2,uint8_t b2,uint8_t w2){
  for(int a=0; a<4; a++) 
  {
    strip.setPixelColor(a,r1,g1,b1,w1);         //  Set pixel's color (in RAM)
    strip.setPixelColor(fwd,r2,g2,b2,w2);       //  Set pixel's color (in RAM)
    strip.show();
    fwd_prev = fwd;
  }
}

void success(){ // all green - with delay
 
  colorWipe(0,50,0,0);
 delay(1000);
  colorWipe(0,0,0,0);
 connected_update = false;
}

#endif
