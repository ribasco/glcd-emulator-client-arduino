#include "GlcdEmulatorClient.h"

u8g2_bytesend_cb GlcdEmulatorClient::sendByte = nullptr;
WiFiClient *GlcdEmulatorClient::_client = nullptr;

GlcdEmulatorClient::GlcdEmulatorClient(const u8g2_cb_t *rotation, u8g2_setup_cb setup_cb, GlcdClientTransport transport) {
    if (transport == GlcdClientTransport::COMM_SERIAL) {
        GlcdEmulatorClient::sendByte = GlcdEmulatorClient::_byteSend_Serial;
    } else if (transport == GlcdClientTransport::COMM_WIFI) {
        GlcdEmulatorClient::sendByte = GlcdEmulatorClient::_byteSend_WiFi;
    }
    setup_cb(&u8g2, rotation, byte_cb, gpio_cb);
}

uint8_t GlcdEmulatorClient::byte_cb(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr) {
    switch (msg) {
        case U8X8_MSG_BYTE_SET_DC: {
            if (arg_int == 0) {
                sendByte(MSG_DC_0);
            } else if (arg_int == 1) {
                sendByte(MSG_DC_1);
            }
            break;
        }
        case U8X8_MSG_BYTE_SEND: {
            uint8_t value;
            uint8_t size = arg_int;
            auto *data = (uint8_t *) arg_ptr;
            sendByte(MSG_BYTE_SEND);
            sendByte(size);
            while (size > 0) {
                value = *data;
                data++;
                size--;
                sendByte(value);
            }
            break;
        }
        default:
            return 0;
    }
    return 1;
}

uint8_t GlcdEmulatorClient::gpio_cb(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr) {
    return 1;
}

void GlcdEmulatorClient::sendBuffer() {
    uint8_t startByte = MSG_START;
    sendByte(startByte);
    U8G2::sendBuffer();
}

void GlcdEmulatorClient::_byteSend_WiFi(uint8_t data) {
    if (_client != nullptr && _client->connected()) {
        _client->write(data);
    }
}

void GlcdEmulatorClient::_byteSend_Serial(uint8_t data) {
    Serial.write(data);
}

void GlcdEmulatorClient::setWifiClient(WiFiClient *client) {
    _client = client;
}
