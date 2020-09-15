#define day 10000
#define potPin A0 // analog pin used to connect the potentiometer
#define valvePin 2
#define delaytime 1000

int threshold = 900;
unsigned int time_calibration = 0;
unsigned long next_reading = 0;
boolean valve_state = false;


void setup() {
  int i = 1;
  
  pinMode(potPin, INPUT);
  pinMode(valvePin, OUTPUT);
  Serial.begin(9600); // open a serial connection to your computer

  // Serial.println("Waiting for time calibration:");

  // while(i == 1){
  //   Serial.print("available");
  //   Serial.println(Serial.available());
  //   while(Serial.available() > 0) {
  //     time_calibration += (Serial.read() - '0') * i;
  //     //i *= 10;
  //     Serial.print("Read");
  //     Serial.println(time_calibration);
  //   }
  // }

  // Serial.println(time_calibration);

  // delay(100);
}

void loop() {
  unsigned long time = millis();
  Serial.println(time);

  if(time > next_reading){
    do{ // measures soil humidity until the valve is closed
      valve_state = TakeReading();
      delay(delaytime);
    }while(valve_state);

    next_reading += day;  // next reading will happen in a day
    Serial.println("next_reading");
    Serial.println(next_reading);
  }
  delay(delaytime);
}

boolean TakeReading() 
{ // takes a reading of the sensor and turns the valve on or off
  int reading;

  reading = analogRead(potPin);
  Serial.println(reading);

  if(reading > threshold){
    digitalWrite(valvePin, HIGH);
    return false;
  }
  else{
    digitalWrite(valvePin, LOW);
    return true;
  }
}
