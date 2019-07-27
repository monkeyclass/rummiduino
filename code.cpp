// constants won't change. Used here to set a pin number:
const int red_light_pin = 11;
const int yellow_light_pin = 10;
const int green_light_pin = 9;
const int start_button_pin = 7;
const int pause_button_pin = 6;
const int stop_button_pin = 5;
const int buzzer_pin = 8;
const long interval = 500; // interval at which to blink (milliseconds)
const long blinkPeriod = 9000; // the time in ms each led should blink
const long beepPeriod = 5000; // the time in ms that beeper will continue
const int buzzerFreq = 1000; // the frequenzy of the buzzer

// Variables will change:
int ledState = LOW; // ledState used to set the LED
int start_buttonState = LOW;
int start_buttonStatePrev = LOW;
int pause_buttonState = LOW;
int pause_buttonStatePrev = LOW;
int stop_buttonState = LOW;
int stop_buttonStatePrev = LOW;
boolean outputTone = false;

unsigned long previousMillis = 0; // will store last time LED was updated
unsigned long start_pressMillis = 0; // when the start button was last pressed - used for pause stop
unsigned long currentMillis = 0;

void setup() {
  // set the digital pin as output:
  pinMode(red_light_pin, OUTPUT);
  pinMode(yellow_light_pin, OUTPUT);
  pinMode(green_light_pin, OUTPUT);
  pinMode(start_button_pin, INPUT);
  pinMode(pause_button_pin, INPUT);
  pinMode(stop_button_pin, INPUT);
}

void loop() {
  currentMillis = millis();
  // read the state of the pushbutton value:
  start_buttonState = digitalRead(start_button_pin);
  pause_buttonState = digitalRead(pause_button_pin);
  stop_buttonState = digitalRead(stop_button_pin);
  // check to see if it's time to blink the LED; that is, if the difference
  // between the current time and last time you blinked the LED is bigger than
  // the interval at which you want to blink the LED.
  startButton();

  stopButton();

  pauseButton();

  start_buttonStatePrev = start_buttonState;
  pause_buttonStatePrev = pause_buttonState;
  stop_buttonStatePrev = stop_buttonState;
  delay(50);
  if (currentMillis - previousMillis >= interval &&
    start_pressMillis > 0) {
    if (currentMillis - start_pressMillis <= blinkPeriod) {
      // save the last time you blinked the LED
      previousMillis = currentMillis;
      // if the LED is off turn it on and vice-versa:
      if (ledState == LOW) {
        ledState = HIGH;
      } else {
        ledState = LOW;
      }
      // set the LED with the ledState of the variable:
      if (currentMillis - start_pressMillis <= blinkPeriod / 3) {
        digitalWrite(green_light_pin, ledState);
      } else if (currentMillis - start_pressMillis <= blinkPeriod / 3 * 2) {
        digitalWrite(yellow_light_pin, ledState);
        digitalWrite(green_light_pin, HIGH);
      } else if (currentMillis - start_pressMillis <= blinkPeriod) {
        digitalWrite(red_light_pin, ledState);
        digitalWrite(yellow_light_pin, HIGH);
      }
    } else if (currentMillis - start_pressMillis <= blinkPeriod + beepPeriod &&
      currentMillis - start_pressMillis >= blinkPeriod) {
      previousMillis = currentMillis;
      if (outputTone == false) {
        ledSoundAll(1);
        outputTone = true;
      } else {
        ledSoundAll(0);
        outputTone = false;
      }
    } else {
      ledSoundAll(0);
      start_pressMillis = 0;
    }
  }
}

void startButton() {
  if (start_buttonState != start_buttonStatePrev) {
    if (start_buttonState == HIGH) {
      // button being pressed down
      start_pressMillis = millis();
      ledSoundAll(0);
    } else {

    }
  }
}

void stopButton() {
  if (stop_buttonState != stop_buttonStatePrev) {
    if (stop_buttonState == HIGH) {
      // button being pressed down
      start_pressMillis = 0;
      ledSoundAll(0);
    } else {

    }
  }
}

void pauseButton() {
  if (pause_buttonState != pause_buttonStatePrev &&
    start_pressMillis > 0 &&
    currentMillis - start_pressMillis <= blinkPeriod) {
    unsigned long pause_startMillis = millis();
    unsigned long pause_stopMillis = 0;
    if (pause_buttonState == HIGH) {
      unsigned int pauseExit = 0;
      delay(50);
      while (pauseExit == 0) {
        start_buttonState = digitalRead(start_button_pin);
        if (start_buttonState == HIGH) {
          pauseExit = 1;
          pause_stopMillis = millis();
          unsigned long pause_Duration = pause_stopMillis - pause_startMillis;
          start_pressMillis += pause_Duration;
        }
        delay(50);
      }
    } else {

    }
  }
}

void ledSoundAll(int state) {
  digitalWrite(red_light_pin, state);
  digitalWrite(yellow_light_pin, state);
  digitalWrite(green_light_pin, state);
  if (state == 1) {
    tone(buzzer_pin, buzzerFreq);
  } else {
    noTone(buzzer_pin);
  }
}