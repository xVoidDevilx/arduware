#ifndef DRV8462_HPP
#define DRV8462_HPP

#include <SPI.h>

// Stop crc command
#define KILLCRC (0xf000407)
// Device Config field masks
#define CONV_AVG (0x07 << 12)
#define MAG_TEMPCO (0x03 << 8)
#define OP_MODE (0x07 << 4)
#define T_CH_EN (0x01 << 3)
#define T_RATE (0x01 << 2)
#define T_HLT_EN (0x01 << 1)
// SENSOR_CONF field masks
#define ANGLE_EN (0x03 << 14)
#define SLEEPTIME (0x0f << 10)
#define MAG_CH_EN (0x0f << 6)
#define Z_RANGE (0x03 << 4)
#define Y_RANGE (0x03 << 2)
#define X_RANGE (0x03)
// System_Conf field masks
#define DIAG_SEL (0x03 << 12)
#define TRIGGER_MODE (0x03 << 9)
#define DATA_TYPE (0x07 << 6)
#define DIAG_EN (0x01 << 5)
#define Z_HLT_EN (0x01 << 2)
#define Y_HLT_EN (0x01 << 1)
#define X_HLT_EN (0x01)
// Alert_Conf field masks
#define ALERT_LATCH (0x01 << 13)
#define ALERT_MODE (0x01 << 12)
#define STATUS_ALRT (0x01 << 11)
#define RSLT_ALRT (0x01 << 8)
#define THRX_COUNT (0x03 << 4)
#define T_THRX_ALRT (0x01 << 3)
#define Z_THRX_ALRT (0x01 << 2)
#define Y_THRX_ALRT (0x01 << 1)
#define X_THRX_ALRT (0x01)
// X_THRX_CONF field masks
#define X_HI_THRESHOLD (0xff << 8)
#define X_LO_THRESHOLD (0xff)
// Y_THRX_CONF field masks
#define Y_HI_THRESHOLD (0xff << 8)
#define Y_LO_THRESHOLD (0xff)
// Z_THRX_CONF field masks
#define Z_HI_THRESHOLD (0xff << 8)
#define Z_LO_THRESHOLD (0xff)
// T_THRX_CONF field masks
#define T_HI_THRESHOLD (0xff << 8)
#define T_LO_THRESHOLD (0xff)
// CONV_STATUS field masks
#define RDY (0x01 << 13)
#define A (0x01 << 12)
#define T (0x01 << 11)
#define Z (0x01 << 10)
#define Y (0x01 << 9)
#define X (0x01 << 8)
#define SET_COUNT (0x07 << 4)
#define ALRT_STATUS (0x03)
// AFE_STATUS field masks
#define CFG_RESET (0x01 << 15)
#define SENS_STAT (0x01 << 12)
#define TEMP_STAT (0x01 << 11)
#define ZHS_STAT (0x01 << 10)
#define YHS_STAT (0x01 << 9)
#define XHS_STAT (0x01 << 8)
#define TRIM_STAT (0x01 << 1)
#define LDO_STAT (0x01)
// SYS_STATUS field masks
#define ALRT_LVL (0x01 << 15)
#define ALRT_DRV (0x01 << 14)
#define SDO_DRV (0x01 << 13)
#define CRC_STAT (0x01 << 12)
#define FRAME_STAT (0x01 << 11)
#define OPERATING_STAT (0x07 << 8)
#define VCC_OV (0x01 << 5)
#define VCC_UV (0x01 << 4)
#define TEMP_THX (0x01 << 3)
#define ZCH_THX (0x01 << 2)
#define YCH_THX (0x01 << 1)
#define XCH_THX (0x01)
// TEST_CONFIG field Masks
#define VER (0x03 << 4)
#define CRC_DIS (0x01 << 2)
#define OSC_CNT_CTL (0x03)
// MAG_GAIN_CONFIG field masks
#define GAIN_SELECTION (0x03 << 14)
#define GAIN_VALUE (0x7FF)
// MAG_OFFSET_CONFIG field masks
#define OFFSET_SELECTION (0x03 << 14)
#define OFFSET_VALUE_1 (0x7F << 7)
#define OFFSET_VALUE_2 (0x7F)

class DRV8462
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
    DRV8462(int CSpin);
    void begin();
    uint16_t readFrame(uint8_t addr);
    void writeFrame(uint8_t addr, uint16_t data);
    uint8_t calculateCRC4(uint32_t source);
};

#endif // DRV8462_HPP
