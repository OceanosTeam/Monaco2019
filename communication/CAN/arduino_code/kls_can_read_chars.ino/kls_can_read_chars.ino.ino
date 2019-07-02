
#include <mcp2515.h>

MCP2515 mcp2515(10);
struct can_frame frame;


int speedRPM;
float current;
float voltage;
uint16_t mot_errCode; 
uint8_t controller_stat;
uint8_t switch_stat;

unsigned short int throttle; 
int contTemp;
int motTemp;


void setup()
{
  Serial.begin(9600);
//  Serial.println("Initializing...");
  
  mcp2515.reset();
  mcp2515.setBitrate(CAN_250KBPS, MCP_8MHZ);

  mcp2515.setNormalMode();

//  Serial.println("RPM, Throttle, I, V, Contr. Temp., Motor Temp., Switch status, Contr. status, Err. Code");


  speedRPM = 1;
  current = 2;
  voltage = 57;
  mot_errCode = 4;
  controller_stat = 5;
  switch_stat = 6;
  throttle = 7;
  contTemp = 8;
  motTemp = 9;
}



void loop()
{
    delay(100);

    int errCode = mcp2515.readMessage(MCP2515::RXB1,&frame);    
    delay(10);
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



    if (Serial.available() > 0) {
        unsigned char incomingByte = Serial.read();
//        Serial.write(incomingByte);
        if (incomingByte == 0x53){
           String message;

           String delim = ", ";

           char tmp_motErr[4];
           sprintf(tmp_motErr, "%x", mot_errCode);
           char tmp_cntrStat[4];
           sprintf(tmp_cntrStat, "%x", controller_stat);
           char tmp_swStat[4];
           sprintf(tmp_swStat, "%x", switch_stat);

           message = speedRPM + delim + throttle + delim
                     + current + delim + voltage + delim
                     + contTemp + delim + motTemp + delim
                     + tmp_motErr + delim + tmp_cntrStat + delim + tmp_swStat;
    
          Serial.println(message);
        }
    }
}
