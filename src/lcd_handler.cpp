#include <SPI.h>

#include <TFT_eSPI.h>       // Hardware-specific library
#include "Free_Fonts.h" 

#include "logger.h"
#include "device.h"

#define DISPLAY_HIGHT   240
#define DISPLAY_WIDTH   320

//pins have update in the user setup file

#define BACKGROUND TFT_BLACK
#define BUTTON_BORDER TFT_RED
#define BUTTON_FILL TFT_ORANGE
#define BUTTON_TEXT_TFT_WHITE

extern device_t g_device;

TFT_eSPI tft = TFT_eSPI();  // Invoke custom library

void lcd_draw_home();
void lcd_draw_speed_label();
void lcd_draw_speed(float mps);


void _lcd_disp_tap_device_name(String str){


    int16_t offset_x = 75;
    int16_t offset_y = 10;
    char strBuff[100] = {0};
    int length = 0;
    
    tft.setFreeFont(FSSB12); 

    str.toCharArray(strBuff, 100);
    int nu_of_chars = str.length();

    do{

        length = tft.textWidth(strBuff);
        //if(length < (DISPLAY_WIDTH - 2*offset_x - nu_of_chars)){
        if(length < (DISPLAY_WIDTH - 2*offset_x)){
            LOG_MSG("Length = %d",length);
            break;
        }

        nu_of_chars--;
        strBuff[nu_of_chars] = 0;
        LOG_MSG("Number of Chars %d",nu_of_chars);
        logger.log(strBuff);
    }while(1);

    String disp_str = String(strBuff);
    int16_t x = (DISPLAY_WIDTH - length)/2;  
    LOG_MSG("X = %d",x);      
    tft.setTextColor(TFT_WHITE);
    tft.drawString(disp_str, x, offset_y);
}

void lcd_clear(){
    tft.fillScreen(TFT_BLACK);
}

void lcd_init(){

    pinMode(TFT_RST, OUTPUT);
    digitalWrite(TFT_RST, HIGH);
     
    tft.begin();
    tft.fillScreen(TFT_BLACK);
    tft.setRotation(1);
    tft.invertDisplay(1);
    tft.setTextSize(1);
    tft.println("");
    tft.setTextSize(2);
    tft.println("    CardTap Systems LLC");
    tft.setTextSize(1);

    tft.setSwapBytes(true);

    _lcd_disp_tap_device_name(g_device.usage_name);
    
    LOG_MSG("TFT Init Success");
}

void lcd_draw_home(){
    tft.fillScreen(BACKGROUND); // Set background color
//    lcd_draw_speed_label();
    lcd_draw_speed(2);
    delay(1000);
    tft.fillScreen(TFT_BLACK);
  tft.drawRoundRect(0, 0, 319, 240, 8, TFT_WHITE);     //Page border

  tft.fillRoundRect(60, 180, 200, 40, 8, TFT_RED);
  tft.drawRoundRect(60, 180, 200, 40, 8, TFT_WHITE);  //Game

  tft.fillRoundRect(60, 130, 200, 40, 8, TFT_RED);   //RGB led
  tft.drawRoundRect(60, 130, 200, 40, 8, TFT_WHITE);

  tft.fillRoundRect(60, 80, 200, 40, 8, TFT_RED);
  tft.drawRoundRect(60, 80, 200, 40, 8, TFT_WHITE); //Oscilloscope

  tft.setCursor(60, 20);
  tft.setTextSize(1);
    tft.setTextFont(FONT2);
  tft.setTextColor(TFT_WHITE);
  tft.print("Select an example!");
  tft.setCursor(70, 50);
  tft.setTextSize(1);
  tft.setTextColor(TFT_GREEN);
  tft.print("NotesPoint.com");
  tft.setTextColor(TFT_BLACK);
  tft.setCursor(65, 195);
  tft.print("   FlappyBird");

  tft.setCursor(105, 145);
  tft.print("RGB-Mixer");

  tft.setCursor(80, 95);
  tft.print("Oscilloscope");
}

void lcd_draw_speed_label(){
    tft.setTextColor(TFT_YELLOW);
    tft.setCursor(10,10);
    tft.setFreeFont(FSB9);
    tft.print("0,0");

}

void lcd_draw_speed(float mps){ // Speed in meters per second
    float mph = mps * 2.236936;
    tft.setTextColor(TFT_YELLOW);
    tft.setCursor(0,0);
    tft.setTextFont(FONT8);
    if (mph>=10) tft.print(mph,1); // Print the font name onto the TFT screen
    else {
        String rawString = String(mph,1);
        String mphString = "0" + rawString;
        tft.print(mphString);
    }
    tft.println();
    tft.print("4");
    tft.setTextFont(FONT6);
    tft.print("5");
}

void lcd_draw_lap_time_label(){

    tft.setTextColor(TFT_YELLOW);
    tft.setCursor(10,10);
    tft.setFreeFont(FSB9);
    tft.print("0,0");
}

void lcd_draw_lab_time(){

    tft.setTextColor(TFT_YELLOW);
    tft.setCursor(10,10);
    tft.setFreeFont(FSB9);
    tft.print("0,0");
}

void lcd_draw_countdown_label(){

    tft.setTextColor(TFT_YELLOW);
    tft.setCursor(10,10);
    tft.setFreeFont(FSB9);
    tft.print("0,0");
}

void lcd_draw_countdown(){

    tft.setTextColor(TFT_YELLOW);
    tft.setCursor(10,10);
    tft.setFreeFont(FSB9);
    tft.print("0,0");
}

void lcd_draw_power_draw_label(){

    tft.setTextColor(TFT_YELLOW);
    tft.setCursor(10,10);
    tft.setFreeFont(FSB9);
    tft.print("0,0");
}

void lcd_draw_power_draw(){

    tft.setTextColor(TFT_YELLOW);
    tft.setCursor(10,10);
    tft.setFreeFont(FSB9);
    tft.print("0,0");
}

void lcd_draw_power_used_label(){

    tft.setTextColor(TFT_YELLOW);
    tft.setCursor(10,10);
    tft.setFreeFont(FSB9);
    tft.print("0,0");
}

void lcd_draw_power_used(){
    
    tft.setTextColor(TFT_YELLOW);
    tft.setCursor(10,10);
    tft.setFreeFont(FSB9);
    tft.print("0,0");
}