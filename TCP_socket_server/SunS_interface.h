#ifndef APP_INC_SUNS_ACCESS_H_
#define APP_INC_SUNS_ACCESS_H_

#include <string.h>
#include <Wire.h>
#include "helpers.h"

namespace SunS_Access_Types {
   #pragma pack(push, 1)
    union registerDesc {
        struct {
            uint8_t STATUS;
            uint8_t WHO_AM_I;
            uint16_t AZIMUTH_ANGLE;
            uint16_t ELEVATION_ANGLE;
            int16_t TEMPERATURE_A;
            int16_t TEMPERATURE_B;
            int16_t TEMPERATURE_C;
            int16_t TEMPERATURE_D;
            int16_t TEMPERATURE_STRUCT;
            uint16_t ALS_1A_VL_RAW;
            uint16_t ALS_1B_VL_RAW;
            uint16_t ALS_1C_VL_RAW;
            uint16_t ALS_1D_VL_RAW;
            uint16_t ALS_2A_VL_RAW;
            uint16_t ALS_2B_VL_RAW;
            uint16_t ALS_2C_VL_RAW;
            uint16_t ALS_2D_VL_RAW;
            uint16_t ALS_3A_VL_RAW;
            uint16_t ALS_3B_VL_RAW;
            uint16_t ALS_3C_VL_RAW;
            uint16_t ALS_3D_VL_RAW;
            uint16_t ALS_1A_IR_RAW;
            uint16_t ALS_1B_IR_RAW;
            uint16_t ALS_1C_IR_RAW;
            uint16_t ALS_1D_IR_RAW;
            uint16_t ALS_2A_IR_RAW;
            uint16_t ALS_2B_IR_RAW;
            uint16_t ALS_2C_IR_RAW;
            uint16_t ALS_2D_IR_RAW;
            uint16_t ALS_3A_IR_RAW;
            uint16_t ALS_3B_IR_RAW;
            uint16_t ALS_3C_IR_RAW;
            uint16_t ALS_3D_IR_RAW;
            uint16_t TEMPERATURE_A_RAW;
            uint16_t TEMPERATURE_B_RAW;
            uint16_t TEMPERATURE_C_RAW;
            uint16_t TEMPERATURE_D_RAW;
            uint16_t TEMPERATURE_STRUCT_RAW;
            uint16_t ALS_STATUS;
            uint8_t ALS_1A_ID;
            uint8_t ALS_1B_ID;
            uint8_t ALS_1C_ID;
            uint8_t ALS_1D_ID;
            uint8_t ALS_2A_ID;
            uint8_t ALS_2B_ID;
            uint8_t ALS_2C_ID;
            uint8_t ALS_2D_ID;
            uint8_t ALS_3A_ID;
            uint8_t ALS_3B_ID;
            uint8_t ALS_3C_ID;
            uint8_t ALS_3D_ID;
        } registerMap;
        uint8_t registerMapArray[88];
    };
    #pragma pack(pop)
} // namespace SunS_Access_Types

class SunS_Access {
 public:
    SunS_Access(uint8_t address) {
        this->address = address;
    }

    void triggerMeasurement(uint8_t itime, uint8_t gain) {
        Wire.beginTransmission(this->address);
        delay(1);
        Wire.write(itime);
        delay(1);
        Wire.write(gain);
        delay(1);
        Wire.endTransmission();
    }

    SunS_Access_Types::registerDesc registersRead() {
        uint8_t arr[88];
        uint8_t cnt = 0;
        Wire.requestFrom(this->address, 88);
        delay(10);

        while(Wire.available()) {
            arr[cnt] = Wire.read();
            cnt++;
        }
        Serial.println(cnt);

        SunS_Access_Types::registerDesc registermap;
        memcpy(registermap.registerMapArray, arr, 88);
        return registermap;
    }

    void printRegistersTable() {
        SunS_Access_Types::registerDesc registermap = this->registersRead();
        // i know it's painful
        Printf("Register Map of SunS\r\n");
        Printf("====================\r\n");
        Printf("STATUS = \t %u\r\n", registermap.registerMap.STATUS);
        Printf("WHO_AM_I = \t %u\r\n", registermap.registerMap.WHO_AM_I);
        Printf("AZIMUTH_ANGLE = \t %u\r\n", registermap.registerMap.AZIMUTH_ANGLE);
        Printf("ELEVATION_ANGLE = \t %u\r\n", registermap.registerMap.ELEVATION_ANGLE);
        Printf("TEMPERATURE_A = \t %d\r\n", registermap.registerMap.TEMPERATURE_A);
        Printf("TEMPERATURE_B = \t %d\r\n", registermap.registerMap.TEMPERATURE_B);
        Printf("TEMPERATURE_C = \t %d\r\n", registermap.registerMap.TEMPERATURE_C);
        Printf("TEMPERATURE_D = \t %d\r\n", registermap.registerMap.TEMPERATURE_D);
        Printf("TEMPERATURE_STRUCT = \t %d\r\n", registermap.registerMap.TEMPERATURE_STRUCT);
        Printf("ALS_1A_VL_RAW = \t %u\r\n", registermap.registerMap.ALS_1A_VL_RAW);
        Printf("ALS_1B_VL_RAW = \t %u\r\n", registermap.registerMap.ALS_1B_VL_RAW);
        Printf("ALS_1C_VL_RAW = \t %u\r\n", registermap.registerMap.ALS_1C_VL_RAW);
        Printf("ALS_1D_VL_RAW = \t %u\r\n", registermap.registerMap.ALS_1D_VL_RAW);
        Printf("ALS_2A_VL_RAW = \t %u\r\n", registermap.registerMap.ALS_2A_VL_RAW);
        Printf("ALS_2B_VL_RAW = \t %u\r\n", registermap.registerMap.ALS_2B_VL_RAW);
        Printf("ALS_2C_VL_RAW = \t %u\r\n", registermap.registerMap.ALS_2C_VL_RAW);
        Printf("ALS_2D_VL_RAW = \t %u\r\n", registermap.registerMap.ALS_2D_VL_RAW);
        Printf("ALS_3A_VL_RAW = \t %u\r\n", registermap.registerMap.ALS_3A_VL_RAW);
        Printf("ALS_3B_VL_RAW = \t %u\r\n", registermap.registerMap.ALS_3B_VL_RAW);
        Printf("ALS_3C_VL_RAW = \t %u\r\n", registermap.registerMap.ALS_3C_VL_RAW);
        Printf("ALS_3D_VL_RAW = \t %u\r\n", registermap.registerMap.ALS_3D_VL_RAW);
        Printf("ALS_1A_IR_RAW = \t %u\r\n", registermap.registerMap.ALS_1A_IR_RAW);
        Printf("ALS_1B_IR_RAW = \t %u\r\n", registermap.registerMap.ALS_1B_IR_RAW);
        Printf("ALS_1C_IR_RAW = \t %u\r\n", registermap.registerMap.ALS_1C_IR_RAW);
        Printf("ALS_1D_IR_RAW = \t %u\r\n", registermap.registerMap.ALS_1D_IR_RAW);
        Printf("ALS_2A_IR_RAW = \t %u\r\n", registermap.registerMap.ALS_2A_IR_RAW);
        Printf("ALS_2B_IR_RAW = \t %u\r\n", registermap.registerMap.ALS_2B_IR_RAW);
        Printf("ALS_2C_IR_RAW = \t %u\r\n", registermap.registerMap.ALS_2C_IR_RAW);
        Printf("ALS_2D_IR_RAW = \t %u\r\n", registermap.registerMap.ALS_2D_IR_RAW);
        Printf("ALS_3A_IR_RAW = \t %u\r\n", registermap.registerMap.ALS_3A_IR_RAW);
        Printf("ALS_3B_IR_RAW = \t %u\r\n", registermap.registerMap.ALS_3B_IR_RAW);
        Printf("ALS_3C_IR_RAW = \t %u\r\n", registermap.registerMap.ALS_3C_IR_RAW);
        Printf("ALS_3D_IR_RAW = \t %u\r\n", registermap.registerMap.ALS_3D_IR_RAW);
        Printf("TEMPERATURE_A_RAW = \t %u\r\n", registermap.registerMap.TEMPERATURE_A_RAW);
        Printf("TEMPERATURE_B_RAW = \t %u\r\n", registermap.registerMap.TEMPERATURE_B_RAW);
        Printf("TEMPERATURE_C_RAW = \t %u\r\n", registermap.registerMap.TEMPERATURE_C_RAW);
        Printf("TEMPERATURE_D_RAW = \t %u\r\n", registermap.registerMap.TEMPERATURE_D_RAW);
        Printf("TEMPERATURE_STRUCT_RAW = \t %u\r\n", registermap.registerMap.TEMPERATURE_STRUCT_RAW);
        Printf("ALS_STATUS = \t %u\r\n", registermap.registerMap.ALS_STATUS);
        Printf("ALS_1A_ID = \t %u\r\n", registermap.registerMap.ALS_1A_ID);
        Printf("ALS_1B_ID = \t %u\r\n", registermap.registerMap.ALS_1B_ID);
        Printf("ALS_1C_ID = \t %u\r\n", registermap.registerMap.ALS_1C_ID);
        Printf("ALS_1D_ID = \t %u\r\n", registermap.registerMap.ALS_1D_ID);
        Printf("ALS_2A_ID = \t %u\r\n", registermap.registerMap.ALS_2A_ID);
        Printf("ALS_2B_ID = \t %u\r\n", registermap.registerMap.ALS_2B_ID);
        Printf("ALS_2C_ID = \t %u\r\n", registermap.registerMap.ALS_2C_ID);
        Printf("ALS_2D_ID = \t %u\r\n", registermap.registerMap.ALS_2D_ID);
        Printf("ALS_3A_ID = \t %u\r\n", registermap.registerMap.ALS_3A_ID);
        Printf("ALS_3B_ID = \t %u\r\n", registermap.registerMap.ALS_3B_ID);
        Printf("ALS_3C_ID = \t %u\r\n", registermap.registerMap.ALS_3C_ID);
        Printf("ALS_3D_ID = \t %u\r\n", registermap.registerMap.ALS_3D_ID);
        Printf("====================\r\n");
    }

    void printRegistersLine() {
        SunS_Access_Types::registerDesc registermap = this->registersRead();

        Printf("%u;", registermap.registerMap.STATUS);
        Printf("%u;", registermap.registerMap.WHO_AM_I);
        Printf("%u;", registermap.registerMap.AZIMUTH_ANGLE);
        Printf("%u;", registermap.registerMap.ELEVATION_ANGLE);
        Printf("%d;", registermap.registerMap.TEMPERATURE_A);
        Printf("%d;", registermap.registerMap.TEMPERATURE_B);
        Printf("%d;", registermap.registerMap.TEMPERATURE_C);
        Printf("%d;", registermap.registerMap.TEMPERATURE_D);
        Printf("%d;", registermap.registerMap.TEMPERATURE_STRUCT);
        Printf("%u;", registermap.registerMap.ALS_1A_VL_RAW);
        Printf("%u;", registermap.registerMap.ALS_1B_VL_RAW);
        Printf("%u;", registermap.registerMap.ALS_1C_VL_RAW);
        Printf("%u;", registermap.registerMap.ALS_1D_VL_RAW);
        Printf("%u;", registermap.registerMap.ALS_2A_VL_RAW);
        Printf("%u;", registermap.registerMap.ALS_2B_VL_RAW);
        Printf("%u;", registermap.registerMap.ALS_2C_VL_RAW);
        Printf("%u;", registermap.registerMap.ALS_2D_VL_RAW);
        Printf("%u;", registermap.registerMap.ALS_3A_VL_RAW);
        Printf("%u;", registermap.registerMap.ALS_3B_VL_RAW);
        Printf("%u;", registermap.registerMap.ALS_3C_VL_RAW);
        Printf("%u;", registermap.registerMap.ALS_3D_VL_RAW);
        Printf("%u;", registermap.registerMap.ALS_1A_IR_RAW);
        Printf("%u;", registermap.registerMap.ALS_1B_IR_RAW);
        Printf("%u;", registermap.registerMap.ALS_1C_IR_RAW);
        Printf("%u;", registermap.registerMap.ALS_1D_IR_RAW);
        Printf("%u;", registermap.registerMap.ALS_2A_IR_RAW);
        Printf("%u;", registermap.registerMap.ALS_2B_IR_RAW);
        Printf("%u;", registermap.registerMap.ALS_2C_IR_RAW);
        Printf("%u;", registermap.registerMap.ALS_2D_IR_RAW);
        Printf("%u;", registermap.registerMap.ALS_3A_IR_RAW);
        Printf("%u;", registermap.registerMap.ALS_3B_IR_RAW);
        Printf("%u;", registermap.registerMap.ALS_3C_IR_RAW);
        Printf("%u;", registermap.registerMap.ALS_3D_IR_RAW);
        Printf("%u;", registermap.registerMap.TEMPERATURE_A_RAW);
        Printf("%u;", registermap.registerMap.TEMPERATURE_B_RAW);
        Printf("%u;", registermap.registerMap.TEMPERATURE_C_RAW);
        Printf("%u;", registermap.registerMap.TEMPERATURE_D_RAW);
        Printf("%u;", registermap.registerMap.TEMPERATURE_STRUCT_RAW);
        Printf("%u;", registermap.registerMap.ALS_STATUS);
        Printf("%u;", registermap.registerMap.ALS_1A_ID);
        Printf("%u;", registermap.registerMap.ALS_1B_ID);
        Printf("%u;", registermap.registerMap.ALS_1C_ID);
        Printf("%u;", registermap.registerMap.ALS_1D_ID);
        Printf("%u;", registermap.registerMap.ALS_2A_ID);
        Printf("%u;", registermap.registerMap.ALS_2B_ID);
        Printf("%u;", registermap.registerMap.ALS_2C_ID);
        Printf("%u;", registermap.registerMap.ALS_2D_ID);
        Printf("%u;", registermap.registerMap.ALS_3A_ID);
        Printf("%u;", registermap.registerMap.ALS_3B_ID);
        Printf("%u;", registermap.registerMap.ALS_3C_ID);
        Printf("%u", registermap.registerMap.ALS_3D_ID);
        Printf("\r\n");
    }

    void printRegistersLineTCP() {
        SunS_Access_Types::registerDesc registermap = this->registersRead();
        TCPPrintf("%u;%u;%u;%u;%d;%d;%d;%d;%d;%u;%u;%u;%u;%u;%u;%u;%u;%u;%u;%u;%u;%u;%u;%u;%u;%u;%u;%u;%u;%u;%u;%u;%u;%u;%u;%u;%u;%u;%u;%u;%u;%u;%u;%u;%u;%u;%u;%u;%u;%u;%u;\r\n", registermap.registerMap.STATUS, registermap.registerMap.WHO_AM_I, registermap.registerMap.AZIMUTH_ANGLE, registermap.registerMap.ELEVATION_ANGLE, registermap.registerMap.TEMPERATURE_A, registermap.registerMap.TEMPERATURE_B, registermap.registerMap.TEMPERATURE_C, registermap.registerMap.TEMPERATURE_D, registermap.registerMap.TEMPERATURE_STRUCT, registermap.registerMap.ALS_1A_VL_RAW, registermap.registerMap.ALS_1B_VL_RAW, registermap.registerMap.ALS_1C_VL_RAW, registermap.registerMap.ALS_1D_VL_RAW, registermap.registerMap.ALS_2A_VL_RAW, registermap.registerMap.ALS_2B_VL_RAW, registermap.registerMap.ALS_2C_VL_RAW, registermap.registerMap.ALS_2D_VL_RAW, registermap.registerMap.ALS_3A_VL_RAW, registermap.registerMap.ALS_3B_VL_RAW, registermap.registerMap.ALS_3C_VL_RAW, registermap.registerMap.ALS_3D_VL_RAW, registermap.registerMap.ALS_1A_IR_RAW, registermap.registerMap.ALS_1B_IR_RAW, registermap.registerMap.ALS_1C_IR_RAW, registermap.registerMap.ALS_1D_IR_RAW, registermap.registerMap.ALS_2A_IR_RAW, registermap.registerMap.ALS_2B_IR_RAW, registermap.registerMap.ALS_2C_IR_RAW, registermap.registerMap.ALS_2D_IR_RAW, registermap.registerMap.ALS_3A_IR_RAW, registermap.registerMap.ALS_3B_IR_RAW, registermap.registerMap.ALS_3C_IR_RAW, registermap.registerMap.ALS_3D_IR_RAW, registermap.registerMap.TEMPERATURE_A_RAW, registermap.registerMap.TEMPERATURE_B_RAW, registermap.registerMap.TEMPERATURE_C_RAW, registermap.registerMap.TEMPERATURE_D_RAW, registermap.registerMap.TEMPERATURE_STRUCT_RAW, registermap.registerMap.ALS_STATUS, registermap.registerMap.ALS_1A_ID, registermap.registerMap.ALS_1B_ID, registermap.registerMap.ALS_1C_ID, registermap.registerMap.ALS_1D_ID, registermap.registerMap.ALS_2A_ID, registermap.registerMap.ALS_2B_ID, registermap.registerMap.ALS_2C_ID, registermap.registerMap.ALS_2D_ID, registermap.registerMap.ALS_3A_ID, registermap.registerMap.ALS_3B_ID, registermap.registerMap.ALS_3C_ID, registermap.registerMap.ALS_3D_ID);
    }

 private:
    uint8_t address;
};

#endif  // APP_INC_SUNS_ACCESS_H_
