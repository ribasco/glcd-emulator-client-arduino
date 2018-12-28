#include "GlcdRemoteClient.h"

u8g2_bytesend_cb GlcdRemoteClient::sendByte = nullptr;
WiFiClient *GlcdRemoteClient::_client = nullptr;

GlcdRemoteClient::GlcdRemoteClient(const u8g2_cb_t *rotation, u8g2_setup_cb setup_cb, GlcdClientTransport transport) : _transport(transport), _acknowledged(false), _started(false) {
    if (transport == GlcdClientTransport::COMM_SERIAL) {
        GlcdRemoteClient::sendByte = GlcdRemoteClient::_byteSend_Serial;
    } else if (transport == GlcdClientTransport::COMM_WIFI) {
        GlcdRemoteClient::sendByte = GlcdRemoteClient::_byteSend_WiFi;
    }
    setup_cb(&u8g2, rotation, byte_cb, gpio_cb);
    this->_buffer_size = 8 * (getBufferTileHeight() * getBufferTileWidth());
}

uint8_t GlcdRemoteClient::byte_cb(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr) {
    return 1;
}

uint8_t GlcdRemoteClient::gpio_cb(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr) {
    return 1;
}

bool GlcdRemoteClient::begin() {
    bool initialized = U8G2::begin();
    if (initialized && (_transport == GlcdClientTransport::COMM_SERIAL)) {
        while (!_acknowledged) {
            //Send request to the host
            Serial.write(MSG_REQ);
            Serial.flush();

            if (Serial.available() > 0) {
                int ack = Serial.read();
                if (ack == MSG_ACK) {
                    _acknowledged = true;
                }
            }

            //Pulse the system led to indicate handshake activity
            blinkLed(50);
            blinkLed(50);
            delay(800);
        }
        _started = true;
    }
    return initialized;
}

void GlcdRemoteClient::sendBuffer() {
    if (!this->_started)
        return;
    U8G2::sendBuffer();
    uint8_t *data = U8G2::getBufferPtr();
    //data++;
    uint8_t value = *data;
    int size = this->_buffer_size;
    while (size > 0) {
        sendByte(value);
        data++;
        value = *data;
        size--;
    }
}

void GlcdRemoteClient::_byteSend_WiFi(uint8_t data) {
    if (_client != nullptr && _client->connected()) {
        _client->write(data);
    }
}

void GlcdRemoteClient::_byteSend_Serial(uint8_t data) {
    Serial.write(data);
}

void GlcdRemoteClient::setWifiClient(WiFiClient *client) {
    _client = client;
}

void GlcdRemoteClient::blinkLed(uint16_t interval) {
    digitalWrite(13, HIGH);
    delay(interval);
    digitalWrite(13, LOW);
    delay(interval);
}


/*
void GlcdRemoteClient::sendSize(int size) {
    sendByte(static_cast<uint8_t>((size >> 24) & 0xFF));
    sendByte(static_cast<uint8_t>((size >> 16) & 0xFF));
    sendByte(static_cast<uint8_t>((size >> 8) & 0xFF));
    sendByte(static_cast<uint8_t>(size & 0xFF));
}*/
