#define moistPin A0         // analog pin used to connect the moist sensor
#define lightPin A1         // analog pin used to connect the photoresistor
#define valvePin 2          // digital pin used to connect the valve

#define moistLevel 900     // moisture level to open the valve      (NEED TO ADJUST)
#define lightLevel 200     // light level for it to take readings   (NEED TO ADJUST)

#define delaytime 1000      // delay between cicles (ms)

boolean valve_state = false;

void setup() {
  int i = 1;
  
  // configure pins
  pinMode(moistPin, INPUT);
  pinMode(lightPin, INPUT);
  pinMode(valvePin, OUTPUT);
  digitalWrite(valvePin, HIGH); // closes valve

  Serial.begin(9600); // open a serial connection to your computer for debug purposes
}

void loop() {
  int light = analogRead(lightPin);

  Serial.print("light: ");
  Serial.println(light);

  if(light < lightLevel){ // is dark
    do{ // measures soil humidity until the valve is closed
      valve_state = TakeReading();
      delay(delaytime);
    }while(valve_state);
  }

  delay(delaytime);
}

boolean TakeReading() 
{ // takes a reading of the sensor and turns the valve on or off
  int moist = analogRead(moistPin);

  Serial.print("moist: ");
  Serial.println(moist);

  if(moist > moistLevel){
    digitalWrite(valvePin, HIGH); // closes valve
    return false;
  }
  else{
    digitalWrite(valvePin, LOW);  // opens valve
    return true;
  }
}
