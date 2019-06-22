
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
  Serial.begin(9600);
//  Serial.println("Initializing...");
  
  mcp2515.reset();
  mcp2515.setBitrate(CAN_250KBPS, MCP_8MHZ);

  mcp2515.setNormalMode();

  Serial.println("RPM, Throttle, I, V, Contr. Temp., Motor Temp., Switch status, Contr. status, Err. Code");
}



void loop()
{
    delay(100);
//    Serial.println("Atempting to read from CAN bus"); 
    int errCode = mcp2515.readMessage(MCP2515::RXB1,&frame);    
    if (errCode == MCP2515::ERROR_OK) {
      
//        unsigned char* data = (unsigned char*)&frame;
        //Serial.println(sizeof(frame));
//        for (int i = 0; i < sizeof(frame); i++)
//            Serial.print(data[i]);
//        Serial.println("");

//        Serial.print("ID:  ");
//        Serial.println(frame.can_id);





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

      String delimiter = ", ";

      char tmp_errCode[16];
      sprintf(tmp_errCode, "%x", mot_errCode);

      char tmp_cntrStat[8];
      sprintf(tmp_cntrStat, "%x", controller_stat);

      char tmp_swStat[8];
      sprintf(tmp_swStat, "%x", switch_stat);
      
      String messageDecoded = speedRPM + delimiter + throttle + delimiter 
                              + current + delimiter + voltage + delimiter 
                              + contTemp + delimiter + motTemp + delimiter
                              + tmp_swStat + delimiter
                              + tmp_cntrStat + delimiter + tmp_errCode;
      //String messageDecoded = (String) (10*current);

      Serial.println(messageDecoded);
      
        
    } else if (errCode == MCP2515::ERROR_FAIL) {
      Serial.println("ERROR_FAIL");
    }else if (errCode == MCP2515::ERROR_ALLTXBUSY) {
      Serial.println("ERROR_ALLTXBUSY");
    }else if (errCode == MCP2515::ERROR_FAILINIT) {
      Serial.println("ERROR_FAILINIT");
    }else if (errCode == MCP2515::ERROR_FAILTX) {
      Serial.println("ERROR_FAILTX");
    }else if (errCode == MCP2515::ERROR_NOMSG) {
      Serial.println("ERROR_NOMSG");
    }
}
