#include <Arduino.h>
#include "device.h"
#include "logger.h"

device_t g_device;

/* LCD and Touch */
extern void lcd_init();
extern void lcd_draw_home();
 
extern void nvs_setup();
/* Touch Controller */
void touch_init(void);
void touch_process(void);


void setup() {  
    ledcSetup(0, 500, 8);

    ledcAttachPin(13, 0);
    ledcWrite(0, 30);

    Serial.begin(115200);
    lcd_init(); 
    nvs_setup();
    touch_init();
    delay(500);
    lcd_draw_home();
}

void loop() {

    touch_process();

    vTaskDelay(200 / portTICK_RATE_MS);

}
