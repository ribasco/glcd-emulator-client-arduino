#ifndef CPP_U8G2EMULATORCLIENT_H
#define CPP_U8G2EMULATORCLIENT_H

#include <U8g2lib.h>

#define MSG_START 0xFE
#define MSG_DC_0 0xE0
#define MSG_DC_1 0xE8
#define MSG_BYTE_SEND 0xEC
#define GLCD_SIZE_104x64
#define GLCD_SIZE_128x128
#define GLCD_SIZE_128x32
#define GLCD_SIZE_128x64 u8g2_Setup_st7920_p_128x64_f
#define GLCD_SIZE_128x96
#define GLCD_SIZE_136x32
#define GLCD_SIZE_136x64
#define GLCD_SIZE_160x104
#define GLCD_SIZE_160x128
#define GLCD_SIZE_160x160
#define GLCD_SIZE_160x80
#define GLCD_SIZE_176x104
#define GLCD_SIZE_176x72
#define GLCD_SIZE_192x32
#define GLCD_SIZE_192x64
#define GLCD_SIZE_200x200
#define GLCD_SIZE_240x120
#define GLCD_SIZE_240x128
#define GLCD_SIZE_240x160
#define GLCD_SIZE_240x64
#define GLCD_SIZE_256x128
#define GLCD_SIZE_256x160
#define GLCD_SIZE_256x32
#define GLCD_SIZE_256x64
#define GLCD_SIZE_296x128
#define GLCD_SIZE_320x240
#define GLCD_SIZE_32x8
#define GLCD_SIZE_384x136
#define GLCD_SIZE_384x240
#define GLCD_SIZE_400x240
#define GLCD_SIZE_48x64
#define GLCD_SIZE_64x128
#define GLCD_SIZE_64x32
#define GLCD_SIZE_64x48
#define GLCD_SIZE_64x8
#define GLCD_SIZE_72x40
#define GLCD_SIZE_88x48
#define GLCD_SIZE_8x8
#define GLCD_SIZE_96x16
#define GLCD_SIZE_96x72
#define GLCD_SIZE_96x96

void COMM_SERIAL(uint8_t data);

void COMM_WIFI(uint8_t data);

typedef void (*u8g2_setup_cb)(u8g2_t *u8g2, const u8g2_cb_t *rotation, u8x8_msg_cb byte_cb, u8x8_msg_cb gpio_and_delay_cb);

typedef void (*u8g2_bytesend_cb)(uint8_t data);

class GlcdEmulatorClient : public U8G2 {
public:
    static u8g2_bytesend_cb bytecb;

    GlcdEmulatorClient(const u8g2_cb_t *rotation, u8g2_setup_cb setup_cb, u8g2_bytesend_cb bytesend_cb);

    void sendBuffer(void);

private:
    static uint8_t byte_cb(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);

    static uint8_t gpio_cb(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);
};

#endif //CPP_U8G2EMULATORCLIENT_H
