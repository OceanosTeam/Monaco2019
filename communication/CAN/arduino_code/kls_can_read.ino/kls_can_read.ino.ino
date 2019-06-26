
#include <mcp2515.h>

MCP2515 mcp2515(10);
struct can_frame frame;

int speedRPM = 0;
float current = 0;
float voltage = 0;
uint16_t mot_errCode = 0; 
uint8_t controller_stat = 0;
uint8_t switch_stat = 0;

unsigned short int throttle = 0; 
int contTemp = 0;
int motTemp = 0;


void setup()
{
  Serial.begin(115200);
//  Serial.println("Initializing...");
  
  mcp2515.reset();
  mcp2515.setBitrate(CAN_250KBPS, MCP_8MHZ);

  mcp2515.setNormalMode();

//  Serial.println("RPM, Throttle, I, V, Contr. Temp., Motor Temp., Switch status, Contr. status, Err. Code");
}



void loop()
{
    delay(100);

    int errCode = mcp2515.readMessage(MCP2515::RXB1,&frame);    
    if (errCode == MCP2515::ERROR_OK) {
      

      if (frame.can_id == 2364612101){ // MESSAGE 1

        speedRPM = frame.data[1]*256 + frame.data[0];
        current = (frame.data[3]*256 + frame.data[2])/10;
        voltage = (frame.data[5]*256 + frame.data[4])/10;

        mot_errCode = frame.data[6] & ( frame.data[7] << 8 );

      } else if (frame.can_id == 2364612357){ // MESSAGE 2
        throttle = frame.data[0];
        contTemp = frame.data[1] - 40;
        motTemp = frame.data[2] - 30;

        controller_stat = frame.data[4];
        switch_stat = frame.data[5];
      }


      if (Serial.available() > 0) {
        unsigned char incomingByte = Serial.read();
//        Serial.write(incomingByte);
        if (incomingByte == 0x53){
          uint8_t message[26];
    
          memcpy(message+0, &speedRPM, sizeof(speedRPM));
          memcpy(message+4, &throttle, sizeof(throttle));
          memcpy(message+6, &current, sizeof(current));
          memcpy(message+10, &voltage, sizeof(voltage));
          memcpy(message+14, &contTemp, sizeof(contTemp));
          memcpy(message+18, &motTemp, sizeof(motTemp));
          memcpy(message+22, &mot_errCode, sizeof(mot_errCode));
          memcpy(message+24, &controller_stat, sizeof(controller_stat));
          memcpy(message+25, &switch_stat, sizeof(switch_stat));
          
//          char test[100];
//          sprintf(test, "%d", speedRPM);
//
//          String test1 = test;
//          Serial.println(test1);
    
          Serial.write(message, 26);
        }
      }
        
    } else if (errCode == MCP2515::ERROR_FAIL) {
//      Serial.println("ERROR_FAIL");
    }else if (errCode == MCP2515::ERROR_ALLTXBUSY) {
//      Serial.println("ERROR_ALLTXBUSY");
    }else if (errCode == MCP2515::ERROR_FAILINIT) {
//      Serial.println("ERROR_FAILINIT");
    }else if (errCode == MCP2515::ERROR_FAILTX) {
//      Serial.println("ERROR_FAILTX");
    }else if (errCode == MCP2515::ERROR_NOMSG) {
//      Serial.println("ERROR_NOMSG");
    }
}
