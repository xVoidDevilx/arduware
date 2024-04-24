#include "DRV8462.hpp"

// Define register addresses as static member variables
const uint8_t DRV8462::FAULT = 0x00;
const uint8_t DRV8462::DIAG1 = 0x01;
const uint8_t DRV8462::DIAG2 = 0x02;
const uint8_t DRV8462::DIAG3 = 0x03;
const uint8_t DRV8462::CTRL1 = 0x04;
const uint8_t DRV8462::CTRL2 = 0x05;
const uint8_t DRV8462::CTRL3 = 0x06;
const uint8_t DRV8462::CTRL4 = 0x07;
const uint8_t DRV8462::CTRL5 = 0x08;
const uint8_t DRV8462::CTRL6 = 0x09;
const uint8_t DRV8462::CTRL7 = 0x0A;
const uint8_t DRV8462::CTRL8 = 0x0B;
const uint8_t DRV8462::CTRL9 = 0x0C;
const uint8_t DRV8462::CTRL10 = 0x0D;
const uint8_t DRV8462::CTRL11 = 0x0E;
const uint8_t DRV8462::CTRL12 = 0x0F;
const uint8_t DRV8462::CTRL13 = 0x10;
const uint8_t DRV8462::INDEX1 = 0x11;
const uint8_t DRV8462::INDEX2 = 0x12;
const uint8_t DRV8462::INDEX3 = 0x13;
const uint8_t DRV8462::INDEX4 = 0x14;
const uint8_t DRV8462::INDEX5 = 0x15;
const uint8_t DRV8462::CUSTOM_CTRL1 = 0x16;
const uint8_t DRV8462::CUSTOM_CTRL2 = 0x17;
const uint8_t DRV8462::CUSTOM_CTRL3 = 0x18;
const uint8_t DRV8462::CUSTOM_CTRL4 = 0x19;
const uint8_t DRV8462::CUSTOM_CTRL5 = 0x1A;
const uint8_t DRV8462::CUSTOM_CTRL6 = 0x1B;
const uint8_t DRV8462::CUSTOM_CTRL7 = 0x1C;
const uint8_t DRV8462::CUSTOM_CTRL8 = 0x1D;
const uint8_t DRV8462::CUSTOM_CTRL9 = 0x1E;
const uint8_t DRV8462::ATQ_CTRL1 = 0x1F;
const uint8_t DRV8462::ATQ_CTRL2 = 0x20;
const uint8_t DRV8462::ATQ_CTRL3 = 0x21;
const uint8_t DRV8462::ATQ_CTRL4 = 0x22;
const uint8_t DRV8462::ATQ_CTRL5 = 0x23;
const uint8_t DRV8462::ATQ_CTRL6 = 0x24;
const uint8_t DRV8462::ATQ_CTRL7 = 0x25;
const uint8_t DRV8462::ATQ_CTRL8 = 0x26;
const uint8_t DRV8462::ATQ_CTRL9 = 0x27;
const uint8_t DRV8462::ATQ_CTRL10 = 0x28;
const uint8_t DRV8462::ATQ_CTRL11 = 0x29;
const uint8_t DRV8462::ATQ_CTRL12 = 0x2A;
const uint8_t DRV8462::ATQ_CTRL13 = 0x2B;
const uint8_t DRV8462::ATQ_CTRL14 = 0x2C;
const uint8_t DRV8462::ATQ_CTRL15 = 0x2D;
const uint8_t DRV8462::ATQ_CTRL16 = 0x2E;
const uint8_t DRV8462::ATQ_CTRL17 = 0x2F;
const uint8_t DRV8462::ATQ_CTRL18 = 0x30;
const uint8_t DRV8462::SS_CTRL1 = 0x31;
const uint8_t DRV8462::SS_CTRL2 = 0x32;
const uint8_t DRV8462::SS_CTRL3 = 0x33;
const uint8_t DRV8462::SS_CTRL4 = 0x34;
const uint8_t DRV8462::SS_CTRL5 = 0x35;
const uint8_t DRV8462::CTRL14 = 0x3C;

DRV8462::DRV8462(int CSpin) : csPin(CSpin) {}

void DRV8462::begin()
{
    // Initialize SPI communication
    SPI.begin();
    // Set CS pin as OUTPUT
    pinMode(csPin, OUTPUT);
    // Initialize CS pin to HIGH (inactive)
    digitalWrite(csPin, HIGH);
}

uint16_t DRV8462::readFrame(uint8_t addr)
{
    /*
    @purpose: read a frame from the DRV8462 and return the
    status & report from ADDR
    */
    uint16_t frame = 0;
    // Start SPI communication
    digitalWrite(csPin, LOW);
    // Send register address with MSB set to 1 for read operation
    uint8_t status = SPI.transfer(addr & 0x7F); // 7F => 0111 1111 0 first, RW=1, then addr
    // Receive data from the register
    uint8_t report = SPI.transfer(0x00);
    // End SPI communication
    digitalWrite(csPin, HIGH);

    // format the frame to be returned
    frame = (status << 8) | (report << 0);
    return frame;
}

uint16_t DRV8462::writeFrame(uint8_t addr, uint8_t data)
{
    /*
    @purpose: Write a frame of data to the DRV8462, return the status and report
    from the write operations
    */
    uint16_t frame = 0;
    uint8_t status = 0, report = 0;
    // Start SPI communication
    digitalWrite(csPin, LOW);
    // Send register address with MSB set to 0 for write operation
    status = SPI.transfer(addr & 0x3F); // 3F => 0011 1111 : 0 first, RW = 0, then addr
    // Send data to write to the register
    report = SPI.transfer(data);
    // End SPI communication
    digitalWrite(csPin, HIGH);
    frame = (status << 8) | (report << 0);
}