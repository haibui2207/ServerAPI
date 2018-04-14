#include <Adafruit_NeoPixel.h>
#include <SSD1306.h>

/*  
  Why I define GPIO of OLED in here?
  Because only ONE way to connect with them.  
  So I define it in here. 
  
    |--------------------------|
    |      |   SDA   |   SCL   |  
    |OLED  |-------------------|
    |      |    4    |    5    |   
    |--------------------------|
*/

#define OLED_SDA 4 //SDA of OLED
#define OLED_SCL 5 //RST of OLED

SSD1306  display(0x3c, OLED_SDA, OLED_SCL);

void setupOled();
void startOled(int x , int y , String text);                        //Display string on OLED screen
void startOled(int x1 , int y1 , String text1 , int x2 , int y2 , String text2 ); //Display string on OLED screen

/************************************************SETUP OLED************************************************/
void setupOled(){
  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);
  display.drawString(35, 25, "WELCOME"); 
  display.display();                           
}

/************************************************START OLED************************************************/
void startOled(int x , int y , String text){
  display.clear();
  display.drawString(x, y, text); 
  display.display();                           
}
void startOled(int x1 , int y1 , String text1 , int x2 , int y2 , String text2 ){
  display.clear();
  display.drawString(x1, y1, text1); 
  display.drawString(x2, y2, text2); 
  display.display();                           
}
