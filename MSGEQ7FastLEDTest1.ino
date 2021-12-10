//setup for led strip
#include <FastLED.h>
#define NUM_LEDS    145
#define PIN         2
CRGB leds[NUM_LEDS];
//*******************************************                   
#include <MD_MSGEQ7.h>

// hardware pin definitions - change to suit circuit
#define DATA_PIN    35
#define RESET_PIN   27
#define STROBE_PIN  26

// frequency reading the IC data
#define READ_DELAY  1

MD_MSGEQ7 MSGEQ7(RESET_PIN, STROBE_PIN, DATA_PIN);
//*************************************************************
long previousMillis = 0;
long interval = 10;

#define ledBlock 20 // defines how many leds per band
#define thresh 1300 // thresh hold of when the leds will turn on
#define blockValue (4095- thresh) / ledBlock

void setup() {
  FastLED.addLeds<WS2812, PIN, RGB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setMaxPowerInVoltsAndMilliamps(5,500);
  
  MSGEQ7.begin();
  
//  Serial.begin(115200);
}

void loop() {
  // only read ever READ_DELAY milliseconds
  static long prevTime =0;

  if (millis() - prevTime >= READ_DELAY){ //checks if the read delay has passed 
    prevTime = millis();

    MSGEQ7.read(); //reads the signal from the MSGEQ7 IC

    //output
    for (int i=0; i < 7; i++){ //for each band 
      int msgValue = MSGEQ7.get(i); //gets the value from a specific band
      int ledOut = i * ledBlock; //gets the position of each block ex: 2 * 18 = 36  
//      Serial.print(msgValue);
//      Serial.print('\t');
      if (i==5) {
        outputHelper(msgValue, ledOut, ledBlock, thresh-400); //out put helper function
      }else{
      outputHelper(msgValue, ledOut, ledBlock, thresh); //out put helper function
      }
//      switch (i) {
//        case 0:
//                  if (msgValue >= 1300){
//                    leds[ledOut] = CHSV(255,255,255);
//                    FastLED.show();
//                  }else{
//                    leds[ledOut] = CHSV(0,0,0);
//                    FastLED.show();
//                  }
//        case 1:
//                  if (msgValue >= 1300){
//                    leds[ledOut] = CHSV(255,255,255);
//                    FastLED.show();
//                  }else{
//                    leds[ledOut] = CHSV(0,0,0);
//                    FastLED.show();
//                  }
//        case 2:
//                  if (msgValue >= 1300){
//                    leds[ledOut] = CHSV(255,255,255);
//                    FastLED.show();
//                  }else{
//                    leds[ledOut] = CHSV(0,0,0);
//                    FastLED.show();
//                  }
//        case 3:
//                  if (msgValue >= 1300){
//                    leds[ledOut] = CHSV(255,255,255);
//                    FastLED.show();
//                  }else{
//                    leds[ledOut] = CHSV(0,0,0);
//                    FastLED.show();
//                  }
//        case 4:
//                  if (msgValue >= 1200){
//                    leds[ledOut] = CHSV(255,255,255);
//                    FastLED.show();
//                  }else{
//                    leds[ledOut] = CHSV(0,0,0);
//                    FastLED.show();
//                  }
//        case 5:
//                  if (msgValue >= 1000){
//                    leds[ledOut] = CHSV(255,255,255);
//                    FastLED.show();
//                  }else{
//                    leds[ledOut] = CHSV(0,0,0);
//                    FastLED.show();
//                  }
//        case 6:
//                  if (msgValue >= 900){
//                    leds[ledOut] = CHSV(255,255,255);
//                    FastLED.show();
//                  }else{
//                    leds[ledOut] = CHSV(0,0,0);
//                    FastLED.show();
//                  }
//      }

    }
//    Serial.println();
    
  }   
   digitalWrite(STROBE_PIN, HIGH);
   digitalWrite(STROBE_PIN, LOW);
}


void outputHelper(int msgValue, int led ,int numLeds, int threshy){

    int value = (msgValue - threshy) / 155; //this aligns the value with the ledBlock 
                                          // value is the max number of leds that will turn on 
                                           //ex: (4200 - 1300) /155 = 18
    
    for (int i=0; i < numLeds; i++){
        if(i <= value){ // if i is less than or equal to the value the LED will turn on 
          leds[i+led] = CHSV(160,255,200);
        }else{
          leds[i+led] = CHSV(0,0,0);
        }
    }
    FastLED.show();
                
  
}
