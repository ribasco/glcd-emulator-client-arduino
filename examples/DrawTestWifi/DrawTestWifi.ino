#include <GlcdEmulatorClient.h>
#include <WiFi.h>

#define GLCDEMU_HOST "192.168.1.24"
#define GLCDEMU_PORT 3380

const char* ssid     = "<WIFI SSID>";
const char* password = "<WIFI PASSWORD>";
const char* host = "<EMULATOR HOST IP>";

void drawU8G2Logo(u8g2_uint_t offset = 0);

u8g2_uint_t x = 0;

//Note: You can also use the u8g2 c contructor instead of GLCD_SIZE_128x64 (e.g. u8g2_Setup_st7920_p_128x64_f)
//Just remember that you can only use FULL-BUFFER constructors, methods that ends with '*_f'
GlcdEmulatorClient u8g2(U8G2_R0, GLCD_SIZE_128x64, COMM_WIFI);

void setup() {
    Serial.begin(115200);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    u8g2.begin();
    u8g2.setFont(u8g2_font_10x20_t_arabic);
}

void loop() {
    delay(5000);

    Serial.print("connecting to ");
    Serial.println(host);

    u8g2.clearBuffer();
    drawU8G2Logo(x++);
    u8g2.setFont(u8g2_font_5x8_tr);
    u8g2.drawStr(10, 40, "Hello from Arduino");
    u8g2.sendBuffer();
    if (x > 128)
        x = 0;
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