/*Arduino Whitsle Detector Switch Program 

 * Detects the whistles from pin 8 and toggles pin 13

 * Dated: 31-5-2019

 * Website: www.circuitdigest.com&nbsp;

 */



#include <FreqMeasure.h>//https://github.com/PaulStoffregen/FreqMeasure


void setup() {

  Serial.begin(9600);

  FreqMeasure.begin(); //Measures on pin 8 by default 

  pinMode(LED_BUILTIN, OUTPUT);

}


double sum=0;

int count=0;

bool state = false; 

float frequency;

int continuity =0;


void loop() {

  if (FreqMeasure.available()) {

    // average several reading together

    sum = sum + FreqMeasure.read();

    count = count + 1;

    if (count > 100) {

      frequency = FreqMeasure.countToFrequency(sum / count);

      Serial.println(frequency); 

      sum = 0;

      count = 0;

    }

  }



    if (frequency>289 && frequency<1050)

    { continuity++; Serial.print("Continuity -> "); Serial.println(continuity); frequency=0;}



    if (continuity >=3 && state==false)

      {state = true; continuity=0; Serial.println("Light Turned ON"); delay(1000);}


    if (continuity >=3 && state==true)

      {state = false; continuity=0; Serial.println("Light Turned OFF"); delay(1000);}


    digitalWrite(LED_BUILTIN, state);

}
