#include <WiFi.h>
#include <GlcdEmulatorClient.h>

#define GLCDEMU_HOST "<IP ADDRESS>"
#define GLCDEMU_PORT 3580

const char* ssid     = "<SSID>";
const char* password = "<PASSWORD>";

void drawU8G2Logo(u8g2_uint_t offset = 0);

u8g2_uint_t x = 0;

// Initialize the client library
WiFiClient client;

//Note: You can also use the u8g2 c contructor instead of GLCD_SIZE_128x64 (e.g. u8g2_Setup_st7920_p_128x64_f)
//Just remember that you can only use FULL-BUFFER constructors, methods that ends with '*_f'
GlcdEmulatorClient u8g2(U8G2_R0, GLCD_SIZE_128x64, COMM_WIFI);

bool _connected = false;

void setup() {
  Serial.begin(115200);

  u8g2.setWifiClient(&client);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  Serial.println("Connecting to emulator host...");
  Serial.print("Host: ");
  Serial.println(GLCDEMU_HOST);
  Serial.print("Port: ");
  Serial.println(GLCDEMU_PORT);

  //client.setNoDelay(true);
  //client.setTimeout(10);

  while(!client.connect(GLCDEMU_HOST, GLCDEMU_PORT)) {
    Serial.println("Retrying connection to host");
    delay(1000);
  }

  u8g2.begin();
  u8g2.setFont(u8g2_font_10x20_t_arabic);
}

void loop() {
  if (!client.connected() && !client.connect(GLCDEMU_HOST, GLCDEMU_PORT)) {
    Serial.println("Not connected...retrying connection");
    delay(1000);
    return;
  }
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