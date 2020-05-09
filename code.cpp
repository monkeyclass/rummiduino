// constants won't change. Used here to set a pin number:
const int red_light_pin = 12;
const int yellow_light_pin = 11;
const int green_light_pin = 10;
const int start_button_pin = 6;
const int pause_button_pin = 5;
const int stop_button_pin = 4;
const int buzzer_pin = 9;
const long iniBlinkPeriod = 60000;
const long interval = 500; // interval at which to blink (milliseconds)
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
long blinkPeriod = iniBlinkPeriod; // the time in ms each led should blink

unsigned long previousMillis = 0; // will store last time LED was updated
unsigned long start_pressMillis = 0; // when the start button was last pressed - used for pause stop
unsigned long currentMillis = 0; // will store the current time for each time the loop begins

void setup() {
  // set the digital pin as output:
  pinMode(red_light_pin, OUTPUT);
  pinMode(yellow_light_pin, OUTPUT);
  pinMode(green_light_pin, OUTPUT);
  pinMode(start_button_pin, INPUT);
  pinMode(pause_button_pin, INPUT);
  pinMode(stop_button_pin, INPUT);
  digitalWrite(start_button_pin, HIGH);
  digitalWrite(pause_button_pin, HIGH);
  digitalWrite(stop_button_pin, HIGH);
}

void loop() {
  currentMillis = millis();
  // read the state of the pushbutton value:
  readPinStates(true, true, true);
  // check to see if it's time to blink the LED; that is, if the difference
  // between the current time and last time you blinked the LED is bigger than
  // the interval at which you want to blink the LED.

  setTimeMode(); // enter mode to set the countdown time

  startButton();

  stopButton();

  pauseButton();

  setButtonState();
  delay(50); // delay to make sure press is registred properly

  countdown();
}

void readPinStates(boolean readStart, boolean readPause, boolean readStop) {
  if (readStart) {
    start_buttonState = digitalRead(start_button_pin);
  }
  if (readPause) {
    pause_buttonState = digitalRead(pause_button_pin);
  }
  if (readStop) {
    stop_buttonState = digitalRead(stop_button_pin);
  }
}

void setTimeMode() {
  if (pause_buttonState != pause_buttonStatePrev && stop_buttonState != stop_buttonStatePrev) {
    boolean setMode = false;
    if (stop_buttonState == LOW && pause_buttonState == LOW) {
      setMode = true;
      ledSoundAll(1, 1, 1, 1); // change to use millis potentially
      delay(1000);
      ledSoundAll(0, 0, 0, 0);
    }
    while (setMode == true) {
      readPinStates(true, true, true);
      if (start_buttonState == LOW) {
        setMode = false;
      } else {
        if (blinkPeriod < iniBlinkPeriod) {
          ledSoundAll(1,0,0,0);
          if (pause_buttonState == LOW) {
            blinkPeriod = iniBlinkPeriod;
          }
          delay(200);
        } else if (blinkPeriod == iniBlinkPeriod) {
          ledSoundAll(1,1,0,0);
          if (pause_buttonState == LOW) {
            blinkPeriod*=1.5;
          } else if (stop_buttonState == LOW) {
            blinkPeriod/=2;
          }
          delay(200);
        } else {
          ledSoundAll(1,1,1,0);
          if (stop_buttonState == LOW) {
            blinkPeriod=iniBlinkPeriod;
          }
          delay(200);
        }
      }
    }
  }
}

void startButton() {
  if (start_buttonState != start_buttonStatePrev) {
    if (start_buttonState == LOW) {
      // button being pressed down
      start_pressMillis = millis();
      ledSoundAll(0, 0, 0, 0);
    } else {

    }
  }
}

void stopButton() {
  if (stop_buttonState != stop_buttonStatePrev) {
    if (stop_buttonState == LOW) {
      // button being pressed down
      start_pressMillis = 0;
      ledSoundAll(0, 0, 0, 0);
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
    if (pause_buttonState == LOW) {
      unsigned int pauseExit = 0;
      delay(50);
      while (pauseExit == 0) {
        readPinStates(true, false, false);
        if (start_buttonState == LOW) {
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

void setButtonState() {
  start_buttonStatePrev = start_buttonState;
  pause_buttonStatePrev = pause_buttonState;
  stop_buttonStatePrev = stop_buttonState;
}
void ledSoundAll(int green_state, int yellow_state, int red_state, int buzzerState) {
  digitalWrite(red_light_pin, red_state);
  digitalWrite(yellow_light_pin, yellow_state);
  digitalWrite(green_light_pin, green_state);
  if (buzzerState == 1) {
    tone(buzzer_pin, buzzerFreq);
  } else {
    noTone(buzzer_pin);
  }
}

void countdown() {
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
        ledSoundAll(1, 1, 1, 1);
        outputTone = true;
      } else {
        ledSoundAll(0, 0, 0, 0);
        outputTone = false;
      }
    } else {
      ledSoundAll(0, 0, 0, 0);
      start_pressMillis = 0;
    }
  }
}