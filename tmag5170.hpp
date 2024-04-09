#ifndef TMAG5170_HPP
#define TMAG5170_HPP

#include <SPI.h>

class TMAG5170
{
private:
    int csPin;
    // Define register addresses as static member variables
    static const uint8_t DEVICE_CONFIG;
    static const uint8_t SENSOR_CONFIG;
    static const uint8_t SYSTEM_CONFIG;
    static const uint8_t ALERT_CONFIG;
    static const uint8_t X_THRX_CONFIG;
    static const uint8_t Y_THRX_CONFIG;
    static const uint8_t Z_THRX_CONFIG;
    static const uint8_t T_THRX_CONFIG;
    static const uint8_t CONV_STATUS;
    static const uint8_t X_CH_RESULT;
    static const uint8_t Y_CH_RESULT;
    static const uint8_t Z_CH_RESULT;
    static const uint8_t TEMP_RESULT;
    static const uint8_t AFE_STATUS;
    static const uint8_t SYS_STATUS;
    static const uint8_t TEST_CONFIG;
    static const uint8_t OSC_MONITOR;
    static const uint8_t MAG_GAIN_CONFIG;
    static const uint8_t MAG_OFFSET_CONFIG;
    static const uint8_t ANGLE_RESULT;
    static const uint8_t MAGNITUDE_RESULT;

public:
    TMAG5170(int pin);
    void begin();
    void disableCRC();
    uint16_t readFrame(uint8_t addr);
    void writeFrame(uint8_t addr, uint16_t data);
    uint8_t calculateCRC4(uint32_t source);
};

#endif // TMAG5170_HPP
