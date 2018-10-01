#define blue 2
#define red 3
#define yellow 4
#define yellowhigh 6
#define green 5

#define low 250
#define high 500
#define med high-((high-low)/2)
#define medrangehigh med+(((high-med)/100)*50)
#define medrangelow med-(((med-low)/100)*50)


#define relay 7
#define pumpWait 600
int wait = pumpWait;
#define pumpTime 1000

#define trigPin 9
#define echoPin 8
bool blinkred = false;
#define maxdistance 13

void setup() {

  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(blue, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(yellowhigh, OUTPUT);
  
  pinMode(relay, OUTPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  digitalWrite(relay, LOW);

  digitalWrite(trigPin, LOW);

  digitalWrite(blue, LOW);
  setLeds(false, false, false, false);
  delay(500);
  digitalWrite(blue, HIGH);
  delay(500);
  digitalWrite(red, HIGH);
  setLeds(true, false, false, false);
  delay(500);
  setLeds(false, false, true, false);
  delay(500);
  setLeds(false, true, false, false);
  delay(500);
  setLeds(false, false, false, true);
  delay(500);
  setLeds(false, false, false, false);
}

void setLed(int color, bool mode) {
  switch (mode) {
    case false:
      digitalWrite(color, LOW);
      break;
    default:
      digitalWrite(color, HIGH);
      break;
  }
}

void invertLed(int color) {
  if (digitalRead(color) == HIGH) {
    digitalWrite(color, LOW);
  } else {
    digitalWrite(color, HIGH);
  }
}

void setLeds(bool redm, bool greenm, bool yellowm, bool yellowhighm) {
  if (blinkred) {
    invertLed(red);
  } else {
    setLed(red, redm);
  }
  setLed(green, greenm);
  setLed(yellow, yellowm);
  setLed(yellowhigh, yellowhighm);
}

void pumpIt() {
  if (wait != 0) {
    wait = wait - 1;
    return;
  }
  if (blinkred) {
    return;
  }
  wait = pumpWait;
  Serial.println("pumpin");
  digitalWrite(relay, HIGH);
  delay(500);
  digitalWrite(relay, LOW);
}

long measure_distance() {
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  return pulseIn(echoPin, HIGH)*0.034/2;
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  // print out the value you read:
  Serial.print("Humidity: ");
  Serial.println(sensorValue);
  long distance = measure_distance();
  Serial.print("Distance: ");
  Serial.println(distance);
  if (distance > maxdistance) {
    blinkred = true;
  } else {
    blinkred = false;
  }

  if (sensorValue > med) {
    if (sensorValue > high) {
      setLeds(true, false, true, false);
      pumpIt();
    } else {
      if (sensorValue > medrangehigh) {
        setLeds(false, false, true, false);
        pumpIt();
      } else {
        setLeds(false, true, true, false);
      }
    }
  } else {
    if (sensorValue < low) {
      setLeds(true, false, false, true);
    } else {
      if (sensorValue < medrangelow) {
        setLeds(false, false, false, true);
      } else {
        setLeds(false, true, false, true);
      }
    }
  }
  invertLed(blue);
  delay(1000);        // delay in between reads for stability
}

