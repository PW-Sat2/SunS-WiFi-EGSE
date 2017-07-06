#ifndef APP_INC_SUNS_ACCESS_H_
#define APP_INC_SUNS_ACCESS_H_

#include <string.h>
#include <Wire.h>
#include "helpers.h"

namespace SunS_Access_Types {
   #pragma pack(push, 1)
    union registerDesc {
        struct {
            uint8_t WHO_AM_I;
            uint16_t STATUS_ACK;
            uint16_t STATUS_PRESENCE;
            uint16_t STATUS_ADC_VALID;

            uint16_t ALS_1A_VL;
            uint16_t ALS_1B_VL;
            uint16_t ALS_1C_VL;
            uint16_t ALS_1D_VL;
            
            uint16_t ALS_2A_VL;
            uint16_t ALS_2B_VL;
            uint16_t ALS_2C_VL;
            uint16_t ALS_2D_VL;
            
            uint16_t ALS_3A_VL;
            uint16_t ALS_3B_VL;
            uint16_t ALS_3C_VL;
            uint16_t ALS_3D_VL;

            uint16_t TEMPERATURE_STRUCT;
            uint16_t TEMPERATURE_A;
            uint16_t TEMPERATURE_B;
            uint16_t TEMPERATURE_C;
            uint16_t TEMPERATURE_D;

            uint16_t ALS_1A_IR;
            uint16_t ALS_1B_IR;
            uint16_t ALS_1C_IR;
            uint16_t ALS_1D_IR;

            uint16_t ALS_2A_IR;
            uint16_t ALS_2B_IR;
            uint16_t ALS_2C_IR;
            uint16_t ALS_2D_IR;
            
            uint16_t ALS_3A_IR;
            uint16_t ALS_3B_IR;
            uint16_t ALS_3C_IR;
            uint16_t ALS_3D_IR;

            uint8_t GAIN;
            uint8_t ITIME;
        } registerMap;
        uint8_t registerMapArray[67];
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
        Wire.write(0x80);
        //delay(1);
        Wire.write(gain);
        //delay(1);
        Wire.write(itime);
        //delay(1);
        Wire.endTransmission();
    }

    SunS_Access_Types::registerDesc registersRead() {
        uint8_t arr[67];
        uint8_t cnt = 0;
        
        Wire.beginTransmission(this->address);
        Wire.write(0x00);
        Wire.endTransmission();
        
        Wire.requestFrom(this->address, 67);

        while(Wire.available()) {
            arr[cnt] = Wire.read();
            cnt++;
        }
        Serial.println(cnt);

        SunS_Access_Types::registerDesc registermap;
        memcpy(registermap.registerMapArray, arr, 67);
        return registermap;
    }

    void printRegistersTable() {
        SunS_Access_Types::registerDesc registermap = this->registersRead();
        // i know it's painful
        Printf("Register Map of SunS\r\n");
        Printf("====================\r\n");
        Printf("WHO_AM_I = \t %u\r\n", registermap.registerMap.WHO_AM_I);
        Printf("STATUS_ACK = \t %u\r\n", registermap.registerMap.STATUS_ACK);
        Printf("STATUS_PRESENCE = \t %u\r\n", registermap.registerMap.STATUS_PRESENCE);
        Printf("STATUS_ADC_VALID = \t %d\r\n", registermap.registerMap.STATUS_ADC_VALID);
        Printf("ALS_1A_VL = \t %d\r\n", registermap.registerMap.ALS_1A_VL);
        Printf("ALS_1B_VL = \t %d\r\n", registermap.registerMap.ALS_1B_VL);
        Printf("ALS_1C_VL = \t %d\r\n", registermap.registerMap.ALS_1C_VL);
        Printf("ALS_1D_VL = \t %d\r\n", registermap.registerMap.ALS_1D_VL);
        
        Printf("ALS_2A_VL = \t %u\r\n", registermap.registerMap.ALS_2A_VL);
        Printf("ALS_2B_VL = \t %u\r\n", registermap.registerMap.ALS_2B_VL);
        Printf("ALS_2C_VL = \t %u\r\n", registermap.registerMap.ALS_2C_VL);
        Printf("ALS_2D_VL = \t %u\r\n", registermap.registerMap.ALS_2D_VL);
        
        Printf("ALS_3A_VL = \t %u\r\n", registermap.registerMap.ALS_3A_VL);
        Printf("ALS_3B_VL = \t %u\r\n", registermap.registerMap.ALS_3B_VL);
        Printf("ALS_3C_VL = \t %u\r\n", registermap.registerMap.ALS_3C_VL);
        Printf("ALS_3D_VL = \t %u\r\n", registermap.registerMap.ALS_3D_VL);
                
        Printf("TEMPERATURE_STRUCT = \t %u\r\n", registermap.registerMap.TEMPERATURE_STRUCT);
        Printf("TEMPERATURE_A = \t %u\r\n", registermap.registerMap.TEMPERATURE_A);
        Printf("TEMPERATURE_B = \t %u\r\n", registermap.registerMap.TEMPERATURE_B);
        Printf("TEMPERATURE_C = \t %u\r\n", registermap.registerMap.TEMPERATURE_C);
        Printf("TEMPERATURE_D = \t %u\r\n", registermap.registerMap.TEMPERATURE_D);
        
        Printf("ALS_1A_IR = \t %u\r\n", registermap.registerMap.ALS_1A_IR);
        Printf("ALS_1B_IR = \t %u\r\n", registermap.registerMap.ALS_1B_IR);
        Printf("ALS_1C_IR = \t %u\r\n", registermap.registerMap.ALS_1C_IR);
        Printf("ALS_1D_IR = \t %u\r\n", registermap.registerMap.ALS_1D_IR);
        
        Printf("ALS_2A_IR = \t %u\r\n", registermap.registerMap.ALS_2A_IR);
        Printf("ALS_2B_IR = \t %u\r\n", registermap.registerMap.ALS_2B_IR);        
        Printf("ALS_2C_IR = \t %u\r\n", registermap.registerMap.ALS_2C_IR);
        Printf("ALS_2D_IR = \t %u\r\n", registermap.registerMap.ALS_2D_IR);

        Printf("ALS_3A_IR = \t %u\r\n", registermap.registerMap.ALS_3A_IR);
        Printf("ALS_3B_IR = \t %u\r\n", registermap.registerMap.ALS_3B_IR);        
        Printf("ALS_3C_IR = \t %u\r\n", registermap.registerMap.ALS_3C_IR);
        Printf("ALS_3D_IR = \t %u\r\n", registermap.registerMap.ALS_3D_IR);
        
        Printf("GAIN = \t %u\r\n", registermap.registerMap.GAIN);
        Printf("ITIME = \t %u\r\n", registermap.registerMap.ITIME);
        Printf("====================\r\n");
    }

    void printRegistersLineTCP() {
        SunS_Access_Types::registerDesc registermap = this->registersRead();
        TCPPrintf("%u;%u;%u;%u;%u;%u;%u;%u;%u;%u;%u;%u;%u;%u;%u;%u;%u;%u;%u;%u;%u;%u;%u;%u;%u;%u;%u;%u;%u;%u;%u;%u;%u;%u;%u;%u;\r\n",
                  registermap.registerMap.WHO_AM_I,
                  registermap.registerMap.STATUS_ACK, registermap.registerMap.STATUS_PRESENCE, registermap.registerMap.STATUS_ADC_VALID,
                  
                  registermap.registerMap.ALS_1A_VL, registermap.registerMap.ALS_1B_VL, registermap.registerMap.ALS_1C_VL, registermap.registerMap.ALS_1D_VL,
                  registermap.registerMap.ALS_2A_VL, registermap.registerMap.ALS_2B_VL, registermap.registerMap.ALS_2C_VL, registermap.registerMap.ALS_2D_VL,
                  registermap.registerMap.ALS_3A_VL, registermap.registerMap.ALS_3B_VL, registermap.registerMap.ALS_3C_VL, registermap.registerMap.ALS_3D_VL,

                  registermap.registerMap.TEMPERATURE_STRUCT, registermap.registerMap.TEMPERATURE_A, registermap.registerMap.TEMPERATURE_B, registermap.registerMap.TEMPERATURE_C, registermap.registerMap.TEMPERATURE_D,

                  registermap.registerMap.ALS_1A_IR, registermap.registerMap.ALS_1B_IR, registermap.registerMap.ALS_1C_IR, registermap.registerMap.ALS_1D_IR,
                  registermap.registerMap.ALS_2A_IR, registermap.registerMap.ALS_2B_IR, registermap.registerMap.ALS_2C_IR, registermap.registerMap.ALS_2D_IR,
                  registermap.registerMap.ALS_3A_IR, registermap.registerMap.ALS_3B_IR, registermap.registerMap.ALS_3C_IR, registermap.registerMap.ALS_3D_IR,
                  
                  registermap.registerMap.GAIN, registermap.registerMap.ITIME);
    }

 private:
    uint8_t address;
};

#endif  // APP_INC_SUNS_ACCESS_H_
