#ifndef DRV8462_HPP
#define DRV8462_HPP

#include <SPI.h>

// Fault reg bit masks
#define FAULTb 7
#define SPI_ERROR 6
#define UVLO 5
#define CPUV 4
#define OCP 3
#define STL 2
#define TF 1
#define OL 0
// DIAG reg bitmasks
#define OCP_LS2_B 7
#define OCP_HS2_B 6
#define OCP_LS1_B 5
#define OCP_HS1_B 4
#define OCP_LS2_A 3
#define OCP_HS2_A 2
#define OCP_LS1_A 1
#define OCP_HS1_A 0

#define STSL 7
#define OTW 6
#define OTS 5
#define STL_LTN_OK 4
#define STALL 3
#define LRN_DONE 2
#define OL_B 1
#define OL_A 0

#define NHOME 6
#define CNT_OFLW 5
#define CNT_UFLW 4
#define NPOR 2

// CTRL reg bit masks
#define EN_OUT 7
#define SR 6
#define IDX_RST 5
#define TOFF 3
#define DECAY 0

#define DIR 7
#define STEP 6
#define SPI_DIR 5
#define SPI_STEP 4
#define MICROSTEP_MODE 0

#define CLR_FLT 7
#define LOCK 4
#define TOCP 3
#define OCP_MODE 2
#define OTSD_MODE 1
#define OTW_REP 0

#define TBLANK_TIME 6
#define STL_LRN 5
#define EN_STL 4
#define STL_REP 3
#define STL_FRQ 2
#define STEP_FRQ_TOL 0

#define RC_RIPPLE 6
#define DIS_SSC 5
#define TRQ_SCALE 4
#define STALL_TH 0

#define EN_OL 7
#define OL_MODE 6
#define OL_T 4
#define STEP_EDGE 3
#define RES_AUTO 1
#define EN_AUTO 0

#define EN_STSL 7
#define TSTSL_FALL 3

#define TSTSL_DLY 3
#define VREF_INT_EN 2

// INDEX REG BIT MASKS
#define CUR_A_SIGN 7
#define CUR_B_SIGN 7
#define CUR_A 0

// ATQ CTRL reg bit masks
#define ATQ_CNT 5
#define ATQ_LRN_CONST1 0

#define ATQ_LRN_MIN_CURRENT 3
#define ATQ_LRN_CONST2 0

#define ATQ_EN 7
#define LRN_START 6
#define ATQ_FRZ 3
#define ATQ_AVG 0
#define KD 0

#define ATQ_ERROR_TRUNCATE 4
#define ATQ_LRN_STEP 2
#define ATQ_LRN_CYCLE_SELECT 0

#define VM_SCALE 6
#define SS_SMPL_SEL 6
#define SS_PWM_FREQ 2
#define EN_SS 0

#define SS_KI_DIV_SEL 4
#define SS_KP_DIV_SEL 0

#define VM_ADC 3
class DRV8462
{
private:
    int csPin;
    // Define register addresses as static member variables
    static const uint8_t FAULT;
    static const uint8_t DIAG1;
    static const uint8_t DIAG2;
    static const uint8_t DIAG3;
    static const uint8_t CTRL1;
    static const uint8_t CTRL2;
    static const uint8_t CTRL3;
    static const uint8_t CTRL4;
    static const uint8_t CTRL5;
    static const uint8_t CTRL6;
    static const uint8_t CTRL7;
    static const uint8_t CTRL8;
    static const uint8_t CTRL9;
    static const uint8_t CTRL10;
    static const uint8_t CTRL11;
    static const uint8_t CTRL12;
    static const uint8_t CTRL13;
    static const uint8_t INDEX1;
    static const uint8_t INDEX2;
    static const uint8_t INDEX3;
    static const uint8_t INDEX4;
    static const uint8_t INDEX5;
    static const uint8_t CUSTOM_CTRL1;
    static const uint8_t CUSTOM_CTRL2;
    static const uint8_t CUSTOM_CTRL3;
    static const uint8_t CUSTOM_CTRL4;
    static const uint8_t CUSTOM_CTRL5;
    static const uint8_t CUSTOM_CTRL6;
    static const uint8_t CUSTOM_CTRL7;
    static const uint8_t CUSTOM_CTRL8;
    static const uint8_t CUSTOM_CTRL9;
    static const uint8_t ATQ_CTRL1;
    static const uint8_t ATQ_CTRL2;
    static const uint8_t ATQ_CTRL3;
    static const uint8_t ATQ_CTRL4;
    static const uint8_t ATQ_CTRL5;
    static const uint8_t ATQ_CTRL6;
    static const uint8_t ATQ_CTRL7;
    static const uint8_t ATQ_CTRL8;
    static const uint8_t ATQ_CTRL9;
    static const uint8_t ATQ_CTRL10;
    static const uint8_t ATQ_CTRL11;
    static const uint8_t ATQ_CTRL12;
    static const uint8_t ATQ_CTRL13;
    static const uint8_t ATQ_CTRL14;
    static const uint8_t ATQ_CTRL15;
    static const uint8_t ATQ_CTRL16;
    static const uint8_t ATQ_CTRL17;
    static const uint8_t ATQ_CTRL18;
    static const uint8_t SS_CTRL1;
    static const uint8_t SS_CTRL2;
    static const uint8_t SS_CTRL3;
    static const uint8_t SS_CTRL4;
    static const uint8_t SS_CTRL5;
    static const uint8_t CTRL14;

public:
    DRV8462(int CSpin);
    void begin();
    uint16_t readFrame(uint8_t addr);
    uint16_t writeFrame(uint8_t addr, uint8_t data);

    // Read - Only register methods
    uint16_t readFault();
    uint16_t readDiag1();
    uint16_t readDiag2();
    uint16_t readDiag3();

    uint16_t readIndex1();
    uint16_t readIndex2();
    uint16_t readIndex3();
    uint16_t readIndex4();
    uint16_t readIndex5();
    uint16_t readATQCTRL1();

    // Read - Write register Methods
    uint16_t writeCTRL1(uint8_t);
    uint16_t writeCTRL2(uint8_t);
    uint16_t writeCTRL3(uint8_t);
    uint16_t writeCTRL4(uint8_t);
    uint16_t writeCTRL5(uint8_t);
    uint16_t writeCTRL6(uint8_t);
    uint16_t writeCTRL7(uint8_t);
    uint16_t writeCTRL8(uint8_t);
    uint16_t writeCTRL9(uint8_t);
    uint16_t writeCTRL10(uint8_t);
    uint16_t writeCTRL11(uint8_t);
    uint16_t writeCTRL12(uint8_t);
    uint16_t writeCTRL13(uint8_t);

    uint16_t writeCustomCTRL1(uint8_t);
    uint16_t writeCustomCTRL2(uint8_t);
    uint16_t writeCustomCTRL3(uint8_t);
    uint16_t writeCustomCTRL4(uint8_t);
    uint16_t writeCustomCTRL5(uint8_t);
    uint16_t writeCustomCTRL6(uint8_t);
    uint16_t writeCustomCTRL7(uint8_t);
    uint16_t writeCustomCTRL8(uint8_t);
    uint16_t writeCustomCTRL9(uint8_t);

    uint16_t writeATQCTRL2(uint8_t);
    uint16_t writeATQCTRL3(uint8_t);
    uint16_t writeATQCTRL4(uint8_t);
    uint16_t writeATQCTRL5(uint8_t);
    uint16_t writeATQCTRL6(uint8_t);
    uint16_t writeATQCTRL7(uint8_t);
    uint16_t writeATQCTRL8(uint8_t);
    uint16_t writeATQCTRL9(uint8_t);
    uint16_t writeATQCTRL10(uint8_t);
    uint16_t writeATQCTRL11(uint8_t);
    uint16_t writeATQCTRL12(uint8_t);
    uint16_t writeATQCTRL13(uint8_t);
    uint16_t writeATQCTRL14(uint8_t);
    uint16_t writeATQCTRL15(uint8_t);
    uint16_t writeATQCTRL16(uint8_t);
    uint16_t writeATQCTRL17(uint8_t);
    uint16_t writeATQCTRL18(uint8_t);

    uint16_t writeSSCTRL1(uint8_t);
    uint16_t writeSSCTRL2(uint8_t);
    uint16_t writeSSCTRL3(uint8_t);
    uint16_t writeSSCTRL4(uint8_t);
    uint16_t writeSSCTRL5(uint8_t);

    // Read variants of the RW registers
    uint16_t readCTRL1();
    uint16_t readCTRL2();
    uint16_t readCTRL3();
    uint16_t readCTRL4();
    uint16_t readCTRL5();
    uint16_t readCTRL6();
    uint16_t readCTRL7();
    uint16_t readCTRL8();
    uint16_t readCTRL9();
    uint16_t readCTRL10();
    uint16_t readCTRL11();
    uint16_t readCTRL12();
    uint16_t readCTRL13();
    uint16_t readCTRL14();

    uint16_t readCustomCTRL1();
    uint16_t readCustomCTRL2();
    uint16_t readCustomCTRL3();
    uint16_t readCustomCTRL4();
    uint16_t readCustomCTRL5();
    uint16_t readCustomCTRL6();
    uint16_t readCustomCTRL7();
    uint16_t readCustomCTRL8();
    uint16_t readCustomCTRL9();

    uint16_t readATQCTRL2();
    uint16_t readATQCTRL3();
    uint16_t readATQCTRL4();
    uint16_t readATQCTRL5();
    uint16_t readATQCTRL6();
    uint16_t readATQCTRL7();
    uint16_t readATQCTRL8();
    uint16_t readATQCTRL9();
    uint16_t readATQCTRL10();
    uint16_t readATQCTRL11();
    uint16_t readATQCTRL12();
    uint16_t readATQCTRL13();
    uint16_t readATQCTRL14();
    uint16_t readATQCTRL15();
    uint16_t readATQCTRL16();
    uint16_t readATQCTRL17();
    uint16_t readATQCTRL18();

    uint16_t readSSCTRL1();
    uint16_t readSSCTRL2();
    uint16_t readSSCTRL3();
    uint16_t readSSCTRL4();
    uint16_t readSSCTRL5();

    /*
    High - Level API methods for Device Configurations
    Remember to Call read, store the reg value, |= to new value to avoid
    overwritten values
    */
    void configAutoTorque(bool);
    void configOutputs(bool);
    void configDecay(uint8_t);

    void toggleDir();
    void change_uStep(uint8_t);
    void clearFaults();
    void toggleOCPMode();
    void toggleOTSDMode();
    void toggleSettingsLock(); // must write 011 or 110

    void configStallLearn(bool);
    void configStallDetect(bool);

    void setStallThresh(uint16_t);

    void configOpenLoadDetect(bool);

    void config_uStepResolution(uint8_t);
    void configAuto_uStep(bool);

    void configHoldingCurrent(uint8_t);
    void configRunningCurrent(uint8_t);

    void toggleStandstillPowerMode();
    void toggleVreference();

    void configCustom_ustep(bool);

    void configAutoTorque(bool);
    void enableAutoTorqueLearning();
    void readMotorCurrent();

    void configSilentStep(bool);
    void setSilentDecayFreq(uint8_t);

    void setSilentStepFreq(uint8_t);
};

#endif // DRV8462_HPP
