//atmega32u4
#include <Keyboard.h>
#include "TimerOne.h"


//length of the level before valid - reflect the measurement period
static const byte samplerate = 5; // ms
static const byte lpLIMIT = 20 / samplerate;
static const byte hpLIMIT = 40 / samplerate;

volatile byte highpulse =0; //count nsi period high
volatile unsigned int lowpulse = 0; //count nsi period low
volatile byte iwvcnt =0; //counts impulse
byte iwv_old = 0; //temp var

static const byte NSApin = 9;  // NSA switch is low when the dail disk is moved
static const byte NSIpin = 10; // NSI when rotating back, nsi generates the impulses

unsigned short nsa_low_cnt =0;
unsigned short nsa_high_cnt =0;
boolean t1_started = false;


void nsi_cnt_ISR() { //called every ms
	
	
	if (!(digitalRead(NSApin))) { //just for safety ensure NSA is closed

		if (!digitalRead(NSIpin)) {
			if (lowpulse++ > lpLIMIT) {
				highpulse = 0; //reset the last high pulse
			}
		}
		else {
			if (highpulse++ > hpLIMIT) {
				if (lowpulse > lpLIMIT) iwvcnt++;
				lowpulse=0; //state changed to high, waiting for the next falling slope
			}
		}
	}
	
}

void setup()
{
	pinMode(NSApin, INPUT);  // Set the button as an input
	digitalWrite(NSApin, HIGH);  // Pull the button high
	pinMode(NSIpin, INPUT);  // Set the button as an input
	digitalWrite(NSIpin, HIGH);  // Pull the button high

	Serial.begin(115200); //This pipes to the serial monitor
	Serial.println("Hallo World");

	Timer1.initialize(1000*samplerate); // in us
	Timer1.attachInterrupt(nsi_cnt_ISR);
	Timer1.stop();
	
}


void loop()
{

	if (!(digitalRead(NSApin))) {

		if (iwvcnt > iwv_old) {
			iwv_old = iwvcnt;
			//Serial.print(iwv_old);
			if (iwv_old > 1) {
				delay(5); //seems necessary , otherwise overrun the USB??
				//delete the previous digit, this results to the count up effect
				Keyboard.write(KEY_BACKSPACE);
				delay(5);
			};
			Keyboard.write((iwv_old%10) + '0');
		};

		if (nsa_low_cnt > 10) {
			//we have long enough a low signal
			if (!t1_started) {
				Timer1.restart(); //we start to count
				t1_started = true;
				//Serial.println("timer started");
			};
		} else nsa_low_cnt++;
		
		} else {
		nsa_low_cnt =0; // we are high -> reset
		if (nsa_high_cnt > 10) { //debounce
			if (t1_started) { //disc rotated to end
				Timer1.stop();
				//Serial.println(" timer stopped");
				t1_started = false;
				iwvcnt = 0;
				iwv_old = 0;
			}
		
		} else nsa_high_cnt++;
	}
}

void sendcmd() {

	Keyboard.write(KEY_LEFT_GUI);
	delay(10);
	writestring("Skzpe");
	//Keyboard.write(KEY_RETURN);
	
}

void writestring (String s) {

	for (int i=0; i < s.length(); i++) {
	//Serial.print(s.charAt(i));
	Keyboard.write(s.charAt(i));
	delay(5);
	}
}