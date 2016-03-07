//Input Buttons or Screen?
const int CapacitiveInput_ButtonPin = 10;
const int LEDLight_MoffsetPin = 11;

bool LightSwitch = false;
bool LightSwitch_Before = false;

int heldcount = 0;
int heldcount_Max = 500;
int LedBrightness = 25*50;
int LedBrightness_Max = 25*1;
int LedBrightness_Min = 25*75;

void setup() {
  pinMode(LEDLight_MoffsetPin, OUTPUT);
  pinMode(CapacitiveInput_ButtonPin, INPUT);
  
  Serial.begin(9600);
}

void loop() {
  //Capacitive Input Toggle with Hold to Dim
  if (digitalRead(CapacitiveInput_ButtonPin)) {

    //Toggle States
    if (!LightSwitch && !LightSwitch_Before) {
      LightSwitch = true;
    }
    else if (LightSwitch && LightSwitch_Before) {
      LightSwitch = false;
    }

    //Push And Hold Dim Light as Needed
    if (heldcount < heldcount_Max) heldcount++;
    else if (heldcount >= heldcount_Max) {
      if (LedBrightness < LedBrightness_Min) LedBrightness++; // Reduces Brightness
      else if (LedBrightness > LedBrightness_Max) LedBrightness--; //Increases Brightness
    }
  }
  else {
    if (LightSwitch != LightSwitch_Before) LightSwitch_Before = LightSwitch;
  }

  //LED ON and OFF Cases / Controlling the Moffset
  if (LightSwitch) {
    digitalWrite(LEDLight_MoffsetPin, LOW); //OFF
    delayMicroseconds(LedBrightness);
    digitalWrite(LEDLight_MoffsetPin, HIGH); //ON
    delay(1);
  }
  else {
    digitalWrite(LEDLight_MoffsetPin, LOW); //OFF
    delay(1);
  }
}
