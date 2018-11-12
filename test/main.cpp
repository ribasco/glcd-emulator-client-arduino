#include "U8g2EmulatorClient.h"

U8g2EmulatorClient *u8g2;

void sendByteToSerial(uint8_t data);

void drawU8G2Logo(U8G2 *u8g2, u8g2_uint_t offset = 0);

u8g2_uint_t x = 0;

void setup() {
    Serial.begin(2000000);
    //parallel: u8g2_Setup_st7920_p_128x64_f
    //spi: u8g2_Setup_st7920_s_128x64_f
    u8g2 = new U8g2EmulatorClient(U8G2_R0, u8g2_Setup_st7920_p_128x64_f, sendByteToSerial);
    u8g2->begin();
    u8g2->setFont(u8g2_font_10x20_t_arabic);
}

void loop() {
    u8g2->clearBuffer();
    drawU8G2Logo(u8g2, x++);
    u8g2->setFont(u8g2_font_5x8_tr);
    u8g2->drawStr(10, 40, "Hello YouTube");
    u8g2->sendBuffer();
    if (x > 128)
        x = 0;
}

void sendByteToSerial(uint8_t data) {
    Serial.write(data);
}

void drawU8G2Logo(U8G2 *u8g2, u8g2_uint_t offset) {
    u8g2->setFontMode(1);

    u8g2->setFontDirection(0);
    u8g2->setFont(u8g2_font_inb16_mf);
    u8g2->drawStr(0 + offset, 22, "U");

    u8g2->setFontDirection(1);
    u8g2->setFont(u8g2_font_inb19_mn);
    u8g2->drawStr(14 + offset, 8, "8");

    u8g2->setFontDirection(0);
    u8g2->setFont(u8g2_font_inb16_mf);
    u8g2->drawStr(36 + offset, 22, "g");
    u8g2->drawStr(48 + offset, 22, "\xb2");

    u8g2->drawHLine(2 + offset, 25, 34);
    u8g2->drawHLine(3 + offset, 26, 34);
    u8g2->drawVLine(32 + offset, 22, 12);
    u8g2->drawVLine(33 + offset, 23, 12);
}