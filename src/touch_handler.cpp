
#include <Arduino.h>
#include "device.h"
#include "ArduinoNvs.h"

// 33,32 Analog input
// 2, 15 digital only
#define PIN_TOUCH_Y1     (33) //Y1
#define PIN_TOUCH_Y2     (15) //Y2
#define PIN_TOUCH_X1     (32) //X1
#define PIN_TOUCH_X2     (2) //X2

extern device_t g_device;
    
static long last_checked_touch = 0;

static int Y = 0;
static int X = 0;

static int Y_MIN_CALIBRATE = 0;
static int Y_MAX_CALIBRATE = 0;
static int X_MIN_CALIBRATE = 0;
static int X_MAX_CALIBRATE = 0;

extern void lcd_draw_point(int x, int y);
void touch_init();
bool touch_process();

void touch_init(){
    Y_MIN_CALIBRATE = NVS.getInt("Y_MIN_CALIBRATE");
    Y_MAX_CALIBRATE = NVS.getInt("Y_MAX_CALIBRATE");
    X_MIN_CALIBRATE = NVS.getInt("X_MIN_CALIBRATE");
    X_MAX_CALIBRATE = NVS.getInt("X_MAX_CALIBRATE");
    analogSetCycles(8);
}
/*
bool touch_process(){
    
    if (millis() - last_checked_touch > (TOUCH_CHECK_INTERVAL)){

        pinMode(PIN_TOUCH_Y1, INPUT);
        pinMode(PIN_TOUCH_Y2, INPUT_PULLDOWN);
        pinMode(PIN_TOUCH_X1, OUTPUT);
        digitalWrite(PIN_TOUCH_X1, HIGH);
        pinMode(PIN_TOUCH_X2, OUTPUT);
        digitalWrite(PIN_TOUCH_X2, LOW);
        Y = (analogRead(PIN_TOUCH_Y1));

        pinMode(PIN_TOUCH_X1, INPUT);
        pinMode(PIN_TOUCH_X2, INPUT_PULLDOWN);
        pinMode(PIN_TOUCH_Y1, OUTPUT);
        digitalWrite(PIN_TOUCH_Y1, HIGH);
        pinMode(PIN_TOUCH_Y2, OUTPUT);
        digitalWrite(PIN_TOUCH_Y2, LOW);
        X = (analogRead(PIN_TOUCH_X1));
//        Serial.print(X_MIN_CALIBRATE); Serial.print(", "); Serial.print(X_MAX_CALIBRATE);Serial.print(", "); Serial.print(Y_MIN_CALIBRATE); Serial.print(", "); Serial.println(Y_MAX_CALIBRATE);
//        Serial.print("Touch: "); Serial.print(X); Serial.print(", "); Serial.println(Y);

        Y = map(Y,Y_MIN_CALIBRATE,Y_MAX_CALIBRATE,240,0);
        X = map(X,X_MIN_CALIBRATE,X_MAX_CALIBRATE,0,320);
        if (X <= 0){
            last_checked_touch = millis();
            return false;
        } 
        lcd_draw_point(X,Y);
        Serial.print("Touch: "); Serial.print(X); Serial.print(", "); Serial.println(Y);
        
        last_checked_touch = millis();
        
        return true;
    }
    return false;
}
*/

bool touch_process(){
    if (millis() - last_checked_touch > (TOUCH_CHECK_INTERVAL)){

        pinMode(PIN_TOUCH_Y1, INPUT);
        pinMode(PIN_TOUCH_Y2, INPUT_PULLDOWN);
        pinMode(PIN_TOUCH_X1, OUTPUT);
        digitalWrite(PIN_TOUCH_X1, HIGH);
        pinMode(PIN_TOUCH_X2, OUTPUT);
        digitalWrite(PIN_TOUCH_X2, LOW);
        Y = (analogRead(PIN_TOUCH_Y1));

        pinMode(PIN_TOUCH_X1, INPUT);
        pinMode(PIN_TOUCH_X2, INPUT_PULLDOWN);
        pinMode(PIN_TOUCH_Y1, OUTPUT);
        digitalWrite(PIN_TOUCH_Y1, HIGH);
        pinMode(PIN_TOUCH_Y2, OUTPUT);
        digitalWrite(PIN_TOUCH_Y2, LOW);
        X = (analogRead(PIN_TOUCH_X1));
        Serial.print(X_MIN_CALIBRATE); Serial.print(", "); Serial.print(X_MAX_CALIBRATE);Serial.print(", "); Serial.print(Y_MIN_CALIBRATE); Serial.print(", "); Serial.println(Y_MAX_CALIBRATE);
        Serial.print("Touch: "); Serial.print(X); Serial.print(", "); Serial.println(Y);

        Y = map(Y,Y_MIN_CALIBRATE,Y_MAX_CALIBRATE,240,0);
        X = map(X,X_MIN_CALIBRATE,X_MAX_CALIBRATE,0,320);
        if (X <= 0){
            last_checked_touch = millis();
            return false;
        } 
        Serial.print("Touch: "); Serial.print(X); Serial.print(", "); Serial.println(Y);
        
        last_checked_touch = millis();
        
        return true;
    }
    return false;
}