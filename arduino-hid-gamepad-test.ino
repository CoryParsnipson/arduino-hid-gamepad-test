#include <HID-Project.h>
#include <HID-Settings.h>

const int pinLed = 2;

const int pinDpadLeft = 3;
const int pinDpadRight = 4;
const int pinDpadUp = 5;
const int pinDpadDown = 6;

const int pinX = 7;
const int pinY = 8;
const int pinA = 9;
const int pinB = 10;

const int pinL3 = 14;
const int pinR3 = 15;

const int pinMeta = 16;

const int NUM_BUTTONS = 10;

const int pinLXAxis = A1;
const int pinLYAxis = A0;

int* idx2Pin = new int[NUM_BUTTONS];
uint32_t* pressed = new uint32_t(0);

void setup() {
  pinMode(pinLed, OUTPUT);
  
  pinMode(pinDpadLeft, INPUT_PULLUP);
  pinMode(pinDpadRight, INPUT_PULLUP);
  pinMode(pinDpadUp, INPUT_PULLUP);
  pinMode(pinDpadDown, INPUT_PULLUP);

  pinMode(pinX, INPUT_PULLUP);
  pinMode(pinY, INPUT_PULLUP);
  pinMode(pinA, INPUT_PULLUP);
  pinMode(pinB, INPUT_PULLUP);

  pinMode(pinL3, INPUT_PULLUP);
  digitalWrite(pinL3, HIGH);
  
  pinMode(pinMeta, INPUT_PULLUP);

  idx2Pin[0] = pinDpadLeft;
  idx2Pin[1] = pinDpadRight;
  idx2Pin[2] = pinDpadUp;
  idx2Pin[3] = pinDpadDown;

  idx2Pin[4] = pinX;
  idx2Pin[5] = pinY;
  idx2Pin[6] = pinA;
  idx2Pin[7] = pinB;

  idx2Pin[8] = pinL3;

  idx2Pin[9] = pinMeta;

  digitalWrite(pinLXAxis, LOW);
  digitalWrite(pinLYAxis, LOW);

  Gamepad.begin();
}

bool getPressed(int idx) {
  if (idx == 0 || idx > 32) {
    return 0;
  }
  return (*pressed >> (idx - 1)) & 0x1;
}

void setPressed(int idx, bool val) {
  if (idx == 0 || idx > 32) {
    return;
  }

  if (val) {
    *pressed |= 0x1 << (idx - 1);
  } else {
    *pressed &= ~(0x1 << (idx - 1));
  }
}

void loop() {
  for (int idx = 0; idx < NUM_BUTTONS; ++idx) {
    int button = idx + 1;
    int pinIsHigh = digitalRead(idx2Pin[idx]);

    if (pinIsHigh) {
      setPressed(button, false);
      Gamepad.release(button);
    } else {
      if (!getPressed(button)) {
        setPressed(button, true);
        Gamepad.press(button);
      }
    }

    // analog axes
    int readX = analogRead(pinLXAxis); // store in temporary variables to use in constrain()
    int readY = analogRead(pinLYAxis);

    const int XMIN = 200, XMAX = 880;
    const int YMIN = 125, YMAX = 835;

    // clamp values to observed joystick values
    readX = constrain(readX, XMIN, XMAX);
    readY = constrain(readY, YMIN, YMAX);
    
    Gamepad.xAxis(map(readX, XMIN, XMAX, -32767, 32767)); 
    Gamepad.yAxis(map(readY, YMIN, YMAX, 32767, -32767)); // flip Y axis because I have it oriented upside-down

    Gamepad.write();
  }

  digitalWrite(pinLed, *pressed == 0 ? LOW : HIGH);
}
