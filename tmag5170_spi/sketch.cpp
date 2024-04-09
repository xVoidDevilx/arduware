#include "tmag5170.hpp"

// Define the chip select pin for the TMAG5170 sensor
const int CS_tmag = 10;

// Create a TMAG5170 object with the chip select pin
TMAG5170 tmag(CS_tmag);

void setup()
{
    Serial.begin(9600);

    // Initialize TMAG5170
    tmag.begin();
    // Test the comms with TMAG
    Serial.print("TMAG Init Code: ");
    Serial.println(tmag.readFrame(0x0f));
    delay(5000);
    // enable x-z angle calc
    tmag.writeFrame(0x01, 0xfd40);
    // SYS CONFIG with HLT en
    tmag.writeFrame(0x02, 0x1001);
    // config alert to act as a switch
    tmag.writeFrame(0x03, 0x1001);
    // config switch thresh x
    tmag.writeFrame(0x04, 0xaB0);
    // read the AFE status & print
    Serial.print("Status reg: ");
    Serial.println(tmag.readFrame(0x0D));

    // configure the TMAG to average for best SNR, active cont mode
    tmag.writeFrame(0x00, 0x5020);
}

void loop()
{
    delay(500);
    Serial.print("X Channel: ");
    Serial.print(tmag.readFrame(0x09));
    Serial.print(" Y Channel: ");
    Serial.print(tmag.readFrame(0x0A));
    Serial.print(" Z Channel: ");
    Serial.println(tmag.readFrame(0x0B));

    Serial.print("Alert Status: ");
    Serial.println(tmag.readFrame(0xE) & 1 << 14);
}
