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

void DRV8462::begin(bool EN_DIR, bool EN_STEP, uint8_t uStepMode)
{
    begin(); // Call the normal begin method to perform common initialization

    // config for the SPI ctrl setup
    configSPICtrl(EN_DIR, EN_STEP, uStepMode);
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

// read method implementations
uint16_t DRV8462::readFault()
{
    return readFrame(FAULT);
}
uint16_t DRV8462::readDiag1()
{
    return readFrame(DIAG1);
}
uint16_t DRV8462::readDiag2()
{
    return readFrame(DIAG2);
}
uint16_t DRV8462::readDiag3()
{
    return readFrame(DIAG3);
}

uint16_t DRV8462::readIndex1()
{
    return readFrame(INDEX1);
}
uint16_t DRV8462::readIndex2()
{
    return readFrame(INDEX2);
}
uint16_t DRV8462::readIndex3()
{
    return readFrame(INDEX3);
}
uint16_t DRV8462::readIndex4()
{
    return readFrame(INDEX4);
}
uint16_t DRV8462::readIndex5()
{
    return readFrame(INDEX5);
}
uint16_t DRV8462::readATQCTRL1()
{
    return readFrame(ATQ_CTRL1);
}

// write method implementations
uint16_t DRV8462::writeCTRL1(uint8_t data)
{
    return writeFrame(CTRL1, data);
}
uint16_t DRV8462::writeCTRL2(uint8_t data)
{
    return writeframe(CTRL2, data);
}
uint16_t DRV8462::writeCTRL3(uint8_t data)
{
    return writeFrame(CTRL3, data);
}
uint16_t DRV8462::writeCTRL4(uint8_t data)
{
    return writeFrame(CTRL4, data);
}
uint16_t DRV8462::writeCTRL5(uint8_t data)
{
    return writeFrame(CTRL5, data);
}
uint16_t DRV8462::writeCTRL6(uint8_t data)
{
    return writeFrame(CTRL6, data);
}
uint16_t DRV8462::writeCTRL7(uint8_t data)
{
    return writeFrame(CTRL7, data);
}
uint16_t DRV8462::writeCTRL8(uint8_t data)
{
    return writeFrame(CTRL8, data);
}
uint16_t DRV8462::writeCTRL9(uint8_t data)
{
    return writeFrame(CTRL9, data);
}
uint16_t DRV8462::writeCTRL10(uint8_t data)
{
    return writeFrame(CTRL10, data);
}
uint16_t DRV8462::writeCTRL11(uint8_t data)
{
    return writeFrame(CTRL11, data);
}
uint16_t DRV8462::writeCTRL12(uint8_t data)
{
    return writeFrame(CTRL12, data);
}
uint16_t DRV8462::writeCTRL13(uint8_t data)
{
    return writeFrame(CTRL13, data);
}

uint16_t DRV8462::writeCustomCTRL1(uint8_t data)
{
    return writeFrame(CUSTOM_CTRL1, data);
}
uint16_t DRV8462::writeCustomCTRL2(uint8_t data)
{
    return writeFrame(CUSTOM_CTRL2, data);
}
uint16_t DRV8462::writeCustomCTRL3(uint8_t data)
{
    return writeFrame(CUSTOM_CTRL3, data);
}
uint16_t DRV8462::writeCustomCTRL4(uint8_t data)
{
    return writeFrame(CUSTOM_CTRL4, data);
}
uint16_t DRV8462::writeCustomCTRL5(uint8_t data)
{
    return writeFrame(CUSTOM_CTRL5, data);
}
uint16_t DRV8462::writeCustomCTRL6(uint8_t data)
{
    return writeFrame(CUSTOM_CTRL6, data);
}
uint16_t DRV8462::writeCustomCTRL7(uint8_t data)
{
    return writeFrame(CUSTOM_CTRL7, data);
}
uint16_t DRV8462::writeCustomCTRL8(uint8_t data)
{
    return writeFrame(CUSTOM_CTRL8, data);
}
uint16_t DRV8462::writeCustomCTRL9(uint8_t data)
{
    return writeFrame(CUSTOM_CTRL9, data);
}

uint16_t DRV8462::writeATQCTRL2(uint8_t data)
{
    return writeFrame(ATQ_CTRL2, data);
}
uint16_t DRV8462::writeATQCTRL3(uint8_t data)
{
    return writeFrame(ATQ_CTRL3, data);
}
uint16_t DRV8462::writeATQCTRL4(uint8_t data)
{
    return writeFrame(ATQ_CTRL4, data);
}
uint16_t DRV8462::writeATQCTRL5(uint8_t data)
{
    return writeFrame(ATQ_CTRL5, data);
}
uint16_t DRV8462::writeATQCTRL6(uint8_t data)
{
    return writeFrame(ATQ_CTRL6, data);
}
uint16_t DRV8462::writeATQCTRL7(uint8_t data)
{
    return writeFrame(ATQ_CTRL7, data);
}
uint16_t DRV8462::writeATQCTRL8(uint8_t data)
{
    return writeFrame(ATQ_CTRL8, data);
}
uint16_t DRV8462::writeATQCTRL9(uint8_t data)
{
    return writeFrame(ATQ_CTRL9, data);
}
uint16_t DRV8462::writeATQCTRL10(uint8_t data)
{
    return writeFrame(ATQ_CTRL10, data);
}
uint16_t DRV8462::writeATQCTRL11(uint8_t data)
{
    return writeFrame(ATQ_CTRL11, data);
}
uint16_t DRV8462::writeATQCTRL12(uint8_t data)
{
    return writeFrame(ATQ_CTRL12, data);
}
uint16_t DRV8462::writeATQCTRL13(uint8_t data)
{
    return writeFrame(ATQ_CTRL13, data);
}
uint16_t DRV8462::writeATQCTRL14(uint8_t data)
{
    return writeFrame(ATQ_CTRL14, data);
}
uint16_t DRV8462::writeATQCTRL15(uint8_t data)
{
    return writeFrame(ATQ_CTRL15, data);
}
uint16_t DRV8462::writeATQCTRL16(uint8_t data)
{
    return writeFrame(ATQ_CTRL16, data);
}
uint16_t DRV8462::writeATQCTRL17(uint8_t data)
{
    return writeFrame(ATQ_CTRL17, data);
}
uint16_t DRV8462::writeATQCTRL18(uint8_t data)
{
    return writeFrame(ATQ_CTRL18, data);
}

uint16_t DRV8462::writeSSCTRL1(uint8_t data)
{
    return writeFrame(SS_CTRL1, data);
}
uint16_t DRV8462::writeSSCTRL2(uint8_t data)
{
    return writeFrame(SS_CTRL2, data);
}
uint16_t DRV8462::writeSSCTRL3(uint8_t data)
{
    return writeFrame(SS_CTRL3, data);
}
uint16_t DRV8462::writeSSCTRL4(uint8_t data)
{
    return writeFrame(SS_CTRL4, data);
}
uint16_t DRV8462::writeSSCTRL5(uint8_t data)
{
    return writeFrame(SS_CTRL5, data);
}

// read register variants of the RW registers
uint16_t DRV8462::readCTRL1()
{
    return readFrame(CTRL1);
}
uint16_t DRV8462::readCTRL2()
{
    return readFrame(CTRL2);
}
uint16_t DRV8462::readCTRL3()
{
    return readFrame(CTRL3);
}
uint16_t DRV8462::readCTRL4()
{
    return readFrame(CTRL4);
}
uint16_t DRV8462::readCTRL5()
{
    return readFrame(CTRL5);
}
uint16_t DRV8462::readCTRL6()
{
    return readFrame(CTRL6);
}
uint16_t DRV8462::readCTRL7()
{
    return readFrame(CTRL7);
}
uint16_t DRV8462::readCTRL8()
{
    return readFrame(CTRL8);
}
uint16_t DRV8462::readCTRL9()
{
    return readFrame(CTRL9);
}
uint16_t DRV8462::readCTRL10()
{
    return readFrame(CTRL10);
}
uint16_t DRV8462::readCTRL11()
{
    return readFrame(CTRL11);
}
uint16_t DRV8462::readCTRL12()
{
    return readFrame(CTRL12);
}
uint16_t DRV8462::readCTRL13()
{
    return readFrame(CTRL13);
}
uint16_t DRV8462::readCTRL14()
{
    return readFrame(CTRL14);
}

uint16_t DRV8462::readCustomCTRL1()
{
    return readFrame(CUSTOM_CTRL1);
}
uint16_t DRV8462::readCustomCTRL2()
{
    return readFrame(CUSTOM_CTRL2);
}
uint16_t DRV8462::readCustomCTRL3()
{
    return readFrame(CUSTOM_CTRL3);
}
uint16_t DRV8462::readCustomCTRL4()
{
    return readFrame(CUSTOM_CTRL4);
}
uint16_t DRV8462::readCustomCTRL5()
{
    return readFrame(CUSTOM_CTRL5);
}
uint16_t DRV8462::readCustomCTRL6()
{
    return readFrame(CUSTOM_CTRL6);
}
uint16_t DRV8462::readCustomCTRL7()
{
    return readFrame(CUSTOM_CTRL7);
}
uint16_t DRV8462::readCustomCTRL8()
{
    return readFrame(CUSTOM_CTRL8);
}
uint16_t DRV8462::readCustomCTRL9()
{
    return readFrame(CUSTOM_CTRL9);
}

uint16_t DRV8462::readATQCTRL2()
{
    return readFrame(ATQ_CTRL2);
}
uint16_t DRV8462::readATQCTRL3()
{
    return readFrame(ATQ_CTRL3);
}
uint16_t DRV8462::readATQCTRL4()
{
    return readFrame(ATQ_CTRL4);
}
uint16_t DRV8462::readATQCTRL5()
{
    return readFrame(ATQ_CTRL5);
}
uint16_t DRV8462::readATQCTRL6()
{
    return readFrame(ATQ_CTRL6);
}
uint16_t DRV8462::readATQCTRL7()
{
    return readFrame(ATQ_CTRL7);
}
uint16_t DRV8462::readATQCTRL8()
{
    return readFrame(ATQ_CTRL8);
}
uint16_t DRV8462::readATQCTRL9()
{
    return readFrame(ATQ_CTRL9);
}
uint16_t DRV8462::readATQCTRL10()
{
    return readFrame(ATQ_CTRL10);
}
uint16_t DRV8462::readATQCTRL11()
{
    return readFrame(ATQ_CTRL11);
}
uint16_t DRV8462::readATQCTRL12()
{
    return readFrame(ATQ_CTRL12);
}
uint16_t DRV8462::readATQCTRL13()
{
    return readFrame(ATQ_CTRL13);
}
uint16_t DRV8462::readATQCTRL14()
{
    return readFrame(ATQ_CTRL14);
}
uint16_t DRV8462::readATQCTRL15()
{
    return readFrame(ATQ_CTRL15);
}
uint16_t DRV8462::readATQCTRL16()
{
    return readFrame(ATQ_CTRL16);
}
uint16_t DRV8462::readATQCTRL17()
{
    return readFrame(ATQ_CTRL17);
}
uint16_t DRV8462::readATQCTRL18()
{
    return readFrame(ATQ_CTRL18);
}

uint16_t DRV8462::readSSCTRL1()
{
    return readFrame(SS_CTRL1);
}
uint16_t DRV8462::readSSCTRL2()
{
    return readFrame(SS_CTRL2);
}
uint16_t DRV8462::readSSCTRL3()
{
    return readFrame(SS_CTRL3);
}
uint16_t DRV8462::readSSCTRL4()
{
    return readFrame(SS_CTRL4);
}
uint16_t DRV8462::readSSCTRL5()
{
    return readFrame(SS_CTRL5);
}

// High - Level API calls for device configurations
void DRV8462::configOutputs(bool en)
{
    uint16_t frame = readCTRL1();
    uint8_t data = (uint8_t)frame & 0x00FF & (en << EN_OUT);
    writeCTRL1(data);
}
void DRV8462::configDecay(uint8_t)
{
}
void DRV8462::configSPICtrl(bool enDIR, bool enSTEP, uint8_t uStepMode)
{
    // configure the DRV for SPI controls
    uint8_t command = (enDIR << SPI_DIR) | (enSTEP << SPI_STEP) | (uStepMode & 0xF);
    writeCTRL2(command);
}
void DRV8462::toggleDir()
{
    // read current reg value
    uint16_t frame = readCTRL2();
    frame ^= (1 << DIR);                   // toggles the direction bit
    writeCTRL2((uint8_t)(frame & 0x00FF)); // rewrite the data into control 2 with bit flipped
}
void DRV8462::change_uStepMode(uint8_t uStepMode)
{
    uint16_t frame = readCTRL3();
    uint8_t command = (uint8_t)frame & 0xFF & uStepMode;
    writeCTRL3(command);
}
void DRV8462::clearFaults()
{
    uint16_t frame = readCTRL3();
    uint8_t data = (uint8_t)frame & 0xFF & (1 << CLR_FLT);
    writeCTRL3(data);
}
void DRV8462::toggleOCPMode()
{
}
void DRV8462::toggleOTSDMode()
{
}
void DRV8462::toggleSettingsLock()
{
    uint16_t frame = readCTRL3();
    uint8_t data = (uint8_t)(frame >> LOCK) & 0x7;

    switch (data)
    {
    case 0b011:
        data = (uint8_t)frame & 0xff | (0b110 < LOCK);
        break;
    case 0b110:
        data = (uint8_t)frame & 0xff | (0b011 < LOCK);
        break;
    }
    writeCTRL3(data); // lock the current settings
} // must write 011 or 110

void DRV8462::configStallLearn(bool)
{
}
void DRV8462::configStallDetect(bool x)
{
}
void DRV8462::setStallThresh(uint16_t x)
{
}
void DRV8462::configOpenLoadDetect(bool x)
{
}
void DRV8462::config_uStepResolution(uint8_t x)
{
}
void DRV8462::configAuto_uStep(bool x)
{
}
void DRV8462::configHoldingCurrent(uint8_t)
{
}
void DRV8462::configRunningCurrent(uint8_t)
{
}
void DRV8462::toggleStandstillPowerMode()
{
}
void DRV8462::toggleVreference()
{
}
void DRV8462::configCustom_ustep(bool x)
{
}
void DRV8462::configAutoTorque(bool en)
{
    // read current register value
    uint16_t frame = readATQCTRL10();
    uint8_t data = (uint8_t)frame & 0x00FF & (en << ATQ_EN); // clear|set the ATQ en bit, keep rest of reg contents
    writeATQCTRL10(data);
}
void DRV8462::configAutoTorqueLearning(bool en)
{
    // read current register value
    uint16_t frame = readATQCTRL10();
    uint8_t data = (uint8_t)frame & 0x00FF & (en << LRN_START); // clear|set the ATQ en bit, keep rest of reg contents
    writeATQCTRL10(data);
}
void DRV8462::readMotorCurrent()
{
}
void DRV8462::configSilentStep(bool)
{
}
void DRV8462::setSilentDecayFreq(uint8_t)
{
}
void DRV8462::setSilentStepFreq(uint8_t)
{
}