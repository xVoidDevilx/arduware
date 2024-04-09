#include "tmag5170.hpp"

// Define register addresses with default values
const uint8_t TMAG5170::DEVICE_CONFIG = 0x00;
const uint8_t TMAG5170::SENSOR_CONFIG = 0x01;
const uint8_t TMAG5170::SYSTEM_CONFIG = 0x02;
const uint8_t TMAG5170::ALERT_CONFIG = 0x03;
const uint8_t TMAG5170::X_THRX_CONFIG = 0x04;
const uint8_t TMAG5170::Y_THRX_CONFIG = 0x05;
const uint8_t TMAG5170::Z_THRX_CONFIG = 0x06;
const uint8_t TMAG5170::T_THRX_CONFIG = 0x07;
const uint8_t TMAG5170::CONV_STATUS = 0x08;
const uint8_t TMAG5170::X_CH_RESULT = 0x09;
const uint8_t TMAG5170::Y_CH_RESULT = 0x0a;
const uint8_t TMAG5170::Z_CH_RESULT = 0x0b;
const uint8_t TMAG5170::TEMP_RESULT = 0x0c;
const uint8_t TMAG5170::AFE_STATUS = 0x0d;
const uint8_t TMAG5170::SYS_STATUS = 0x0e;
const uint8_t TMAG5170::TEST_CONFIG = 0x0f;
const uint8_t TMAG5170::OSC_MONITOR = 0x10;
const uint8_t TMAG5170::MAG_GAIN_CONFIG = 0x11;
const uint8_t TMAG5170::MAG_OFFSET_CONFIG = 0x12;
const uint8_t TMAG5170::ANGLE_RESULT = 0x13;
const uint8_t TMAG5170::MAGNITUDE_RESULT = 0x14;

TMAG5170::TMAG5170(int pin) : csPin(pin) {}

void TMAG5170::begin()
{
    pinMode(csPin, OUTPUT);
    SPI.begin();
    SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
}

void TMAG5170::disableCRC()
{
    digitalWrite(csPin, LOW);
    SPI.transfer16(0x0F00);
    SPI.transfer16(0x0407);
    digitalWrite(csPin, HIGH);
}

uint16_t TMAG5170::readFrame(uint8_t addr)
{
    // preconstruct what to send to TMAG
    uint8_t frame1 = addr | 0x80;              // set the rw bit for read
    uint16_t frame2 = 0;                       // 0s for dont cares
    uint32_t crc = frame1 << 24 | frame2 << 4; // define the frame to compute CRC over
    uint8_t frame3 = calculateCRC4(crc);       // Calculate CRC nibble for the register address

    // Select the slave device
    digitalWrite(csPin, LOW);

    // Send the register address & update the status reg bits
    uint16_t status = (uint16_t)SPI.transfer(frame1) << 4; // Set MSB to 1 to indicate a read operation
    uint16_t receivedData = SPI.transfer16(frame2);        // Read 16-bit chunks - send a switching signal for crc

    // write command and CRC nibble, set LSBs of status
    uint8_t ret = SPI.transfer(frame3 | 0x10); // get the last 8 bits from the final spi transfer

    // Deselect the slave device
    digitalWrite(csPin, HIGH);

    // separate the last 8 returned bits -> status LSBs | crc
    status |= (ret & 0xF0) >> 4; // take first 4 bits, shift down
    ret &= 0x0F;                 // crc from tmag

    crc = status << 12 | receivedData; // shift the status 12, + 16 data bits = 28 bit source

    // Check CRC nibble
    frame3 = calculateCRC4(crc);
    if (frame3 != ret)
    {
        Serial.println('CRC Failed! Fetching again...');
        return readFrame(addr) // request the data again -> this can lock up
    }
    return receivedData;
}

void TMAG5170::writeFrame(uint8_t addr, uint16_t data)
{
    // preconstruct what to send to TMAG
    uint8_t frame1 = addr & 0x7F;              // clear the rw bit for read
    uint16_t frame2 = data;                    // data to send in the 2nd stage
    uint32_t crc = frame1 << 24 | frame2 << 4; // define the frame to compute CRC over
    uint8_t frame3 = calculateCRC4(crc);       // Calculate CRC nibble for the register address

    // Select the slave device
    digitalWrite(csPin, LOW);

    // Send the register address & update the status reg bits
    uint16_t status = (uint16_t)SPI.transfer(frame1) << 4; // Set MSB to 1 to indicate a read operation
    uint16_t receivedData = SPI.transfer16(frame2);        // Read 16-bit chunks - send a switching signal for crc

    // write command and CRC nibble, set LSBs of status
    uint8_t ret = SPI.transfer(frame3 | 0x10); // get the last 8 bits from the final spi transfer

    // Deselect the slave device
    digitalWrite(csPin, HIGH);

    // separate the last 8 returned bits -> status LSBs | crc
    status |= (ret & 0xF0) >> 4; // take first 4 bits, shift down
    ret &= 0x0F;                 // crc from tmag

    crc = status << 12 | receivedData; // shift the status 12, + 16 data bits = 28 bit source

    // Check CRC nibble
    frame3 = calculateCRC4(crc);
    if (frame3 != ret)
    {
        Serial.println('CRC Failed! Writing again...');
        writeFrame(addr) // send the data again -> this can lock up
    }
}

uint8_t TMAG5170::calculateCRC4(uint32_t source)
{
    // initialize the frame with 4 padded zeros
    uint32_t paddedFrame = source & 0xFFFFFF00;
    // Initialize CRC nibble
    uint8_t frameCRC = 0x0F;

    // Iterate over each bit of the padded frame
    for (int i = 31; i >= 0; i--)
    {
        bool inv = (paddedFrame >> i) ^ (frameCRC >> 3);
        // toggle the last bit if inv
        frameCRC ^= inv;
        // shift the bits up & shift inv in
        frameCRC <<= 1;
        frameCRC |= inv;
    }

    // Return the 4-bit CRC nibble
    return frameCRC & 0x0F;
}