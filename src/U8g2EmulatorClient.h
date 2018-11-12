//
// Created by raffy on 9/12/2018.
//

#ifndef CPP_U8G2EMULATORCLIENT_H
#define CPP_U8G2EMULATORCLIENT_H

#include <U8g2lib.h>

#define MSG_START 0xFE
#define MSG_DC_0 0xE0
#define MSG_DC_1 0xE8
#define MSG_BYTE_SEND 0xEC

typedef void (*u8g2_setup_cb)(u8g2_t *u8g2, const u8g2_cb_t *rotation, u8x8_msg_cb byte_cb, u8x8_msg_cb gpio_and_delay_cb);

typedef void (*u8g2_bytesend_cb)(uint8_t data);

class U8g2EmulatorClient : public U8G2 {
public:
    static u8g2_bytesend_cb bytecb;

    U8g2EmulatorClient(const u8g2_cb_t *rotation, u8g2_setup_cb setup_cb, u8g2_bytesend_cb bytesend_cb);

    void sendBuffer(void);

private:
    static uint8_t byte_cb(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);

    static uint8_t gpio_cb(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);
};

#endif //CPP_U8G2EMULATORCLIENT_H
