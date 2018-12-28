#ifndef CPP_U8G2EMULATORCLIENT_H
#define CPP_U8G2EMULATORCLIENT_H

#include <U8g2lib.h>
#include <WiFi.h>

#define MSG_REQ 0x7B
#define MSG_ACK 0x7C
#define TIMEOUT 5

enum GlcdClientTransport : uint8_t {
    COMM_SERIAL = 0,
    COMM_WIFI = 1
};

typedef void (*u8g2_setup_cb)(u8g2_t *u8g2, const u8g2_cb_t *rotation, u8x8_msg_cb byte_cb, u8x8_msg_cb gpio_and_delay_cb);

typedef void (*u8g2_bytesend_cb)(uint8_t data);

class GlcdRemoteClient : public U8G2 {
public:
    static u8g2_bytesend_cb sendByte;

    //u8g2_bytesend_cb bytesend_cb
    GlcdRemoteClient(const u8g2_cb_t *rotation, u8g2_setup_cb setup_cb, GlcdClientTransport transport);

    bool begin(void);

    void sendBuffer(void);

    void setWifiClient(WiFiClient *client);
private:
    static WiFiClient *_client;

    static uint8_t byte_cb(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);

    static uint8_t gpio_cb(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);

    static void _byteSend_Serial(uint8_t data);

    static void _byteSend_WiFi(uint8_t data);

    GlcdClientTransport _transport;

    volatile bool _acknowledged;

    volatile bool _started;

    int _buffer_size;

    uint16_t _retries;

    void blinkLed(uint16_t interval);
    //void sendSize(int size);
};

#endif //CPP_U8G2EMULATORCLIENT_H
