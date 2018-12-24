#include <GlcdRemoteClient.h>

void drawU8G2Logo(u8g2_uint_t offset = 0);

u8g2_uint_t x = 0;

uint8_t state = 0;

//Args: U8g2 Display Rotation/U8g2 Constructor/Data transport method (COMM_SERIAL or COMM_WIFI)
//Note: Use FULL BUFFER constructors ONLY (ending with _f)
GlcdRemoteClient u8g2(U8G2_R0, u8g2_Setup_st7920_p_128x64_f, COMM_SERIAL);

const int ledPin =  13;

unsigned long previousMillis = 0;

const long interval = 500;

uint8_t ledState = LOW;

void setup() {
    pinMode(ledPin, OUTPUT);
    //Initialize Serial (We use 2000000 baud rate for maximum performance)
    Serial.begin(2000000);
    //Call begin: this method will send a request to the host (simulator) and will block until it receives the acknowledgement
    u8g2.begin();
    u8g2.setFont(u8g2_font_10x20_t_arabic);
}

void loop() {
    u8g2.clearBuffer();
    drawU8G2Logo(0);
    u8g2.setFont(u8g2_font_5x8_tr);
    u8g2.drawStr(0, 40, "Hello from Arduino");
    u8g2.sendBuffer();
    if (x > 128)
        x = 0;

    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
        // save the last time you blinked the LED
        previousMillis = currentMillis;

        // if the LED is off turn it on and vice-versa:
        if (ledState == LOW) {
            ledState = HIGH;
        } else {
            ledState = LOW;
        }
        // set the LED with the ledState of the variable:
        digitalWrite(ledPin, ledState);
    }
}

void drawU8G2Logo(u8g2_uint_t offset) {
    u8g2.setFontMode(1);

    u8g2.setFontDirection(0);
    u8g2.setFont(u8g2_font_inb16_mf);
    u8g2.drawStr(0 + offset, 22, "U");

    u8g2.setFontDirection(1);
    u8g2.setFont(u8g2_font_inb19_mn);
    u8g2.drawStr(14 + offset, 8, "8");

    u8g2.setFontDirection(0);
    u8g2.setFont(u8g2_font_inb16_mf);
    u8g2.drawStr(36 + offset, 22, "g");
    u8g2.drawStr(48 + offset, 22, "\xb2");

    u8g2.drawHLine(2 + offset, 25, 34);
    u8g2.drawHLine(3 + offset, 26, 34);
    u8g2.drawVLine(32 + offset, 22, 12);
    u8g2.drawVLine(33 + offset, 23, 12);
}