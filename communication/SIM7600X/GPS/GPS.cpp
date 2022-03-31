	/**
*  @filename   :   GPS.cpp
*  @brief      :   Implements for sim7600c 4g hat raspberry pi demo
*  @author     :   Kaloha from Waveshare
*
*  Copyright (C) Waveshare     April 27 2018
*  http://www.waveshare.com / http://www.waveshare.net
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documnetation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to  whom the Software is
* furished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*/
#include "../arduPi.h"
#include "../sim7x00.h"
#include "GPSloc.h"
#include <string>
#include <iostream>

// Pin definition
int POWERKEY = 6;

int8_t answer;

void reset() {
	std::cout<<"RESETTING SIM7600 MODULE"<<std::endl;
	sim7600.sendATcommand("AT+CRESET", "OK", 2000);
	//sim7600.sendATcommand("AT+CFUN=7", "OK", 2000);
	//delay(2000);
	//sim7600.sendATcommand("AT+CFUN=6", "OK", 2000);
	delay(10000);
}

void setup() {	
	sim7600.PowerOn(POWERKEY);
	answer = sim7600.sendATcommand("AT+CPIN?", "+CPIN: SIM PIN", 2000);
	if (answer == 1)
	{
		std::cout<<"~pi> INSERTING STANDARD PIN..."<<std::endl;
		std::string SIM_PIN = "0000";
		sim7600.sendATcommand(("AT+CPIN="+SIM_PIN).c_str(),"OK", 2000);
	}
	else
	{
		std::cout<<"~pi> PIN ALREADY INPLACE"<<std::endl;
	}
	answer = sim7600.sendATcommand("AT+CGPS?", "+CGPS: 1,1", 2000);
	if (answer == 0)
	{
		std::cout<<"~pi> INITIALIZING GPS SESSION"<<std::endl;
		sim7600.sendATcommand("AT+CGPS=1,1", "OK:", 2000);
	}
	else
	{
		std::cout<<"~pi> GPS SESSION INITIALIZED"<<std::endl;
	}
	std::cout<<"~pi> RECEIVING GPS DATA EVERY 2 SECONDS"<<std::endl;
	delay(3000);
}

void loop() {
}

int main() {
	reset();
	setup();
	system("sudo ../GSM/wwan0.sh");
	int signal_counter = 1;
	while (1) {
		std::cout << "" << std::endl;
		std::cout << std::string(12, '*')+"<"+std::to_string(signal_counter)+">"+std::string(12, '*') << std::endl;
		
		GPSloc GPSCurrent = GPSloc();
		GPSCurrent = sim7600.GPSPositioning();
		if (signal_counter==1)
		{
			std::string gpsquerry = "./writer.sh 1 "+std::to_string(GPSCurrent.Lat)+" "+std::to_string(GPSCurrent.Log)+" "+std::to_string(GPSCurrent.Speed);
			system(gpsquerry.c_str());
		}
		else
		{
			std::string gpsquerry = "./writer.sh 0 "+std::to_string(GPSCurrent.Lat)+" "+std::to_string(GPSCurrent.Log)+" "+std::to_string(GPSCurrent.Speed);
			system(gpsquerry.c_str());
		}
		std::cout << std::string(12, '*')+"<"+std::to_string(signal_counter)+">"+std::string(12, '*') << std::endl;
		std::cout << "" << std::endl;
		signal_counter++;
		delay(2000);
	}
	sim7600.sendATcommand("AT+CGPS=0","OK:", 3000);
	system("sudo qmicli -d /dev/cdc-wdm0 --dms-set-operating-mode='offline'");
	return (0);
}
