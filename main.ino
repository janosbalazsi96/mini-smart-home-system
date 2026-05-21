#include <LiquidCrystal.h>

// LCD
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Szenzorok
int ldrPin = A0;
int tempPin = A1;

// LED-ek
int lightLed = 8;
int fanLed = 7;

// GOMB
int buttonPin = 6;

// Állapotok
bool manualMode = false;
bool lightState = false;

void setup() {

  pinMode(lightLed, OUTPUT);
  pinMode(fanLed, OUTPUT);

  // Gomb
  pinMode(buttonPin, INPUT_PULLUP);

  Serial.begin(9600);

  // LCD indítás
  lcd.begin(16, 2);

  lcd.print("Smart Home");
  delay(2000);

  lcd.clear();
}

void loop() {

  // ===== GOMB KEZELÉS =====

  if(digitalRead(buttonPin) == LOW)
  {
    manualMode = !manualMode;

    // Manuális módban kapcsolja a lámpát
    if(manualMode)
    {
      lightState = !lightState;
    }

    delay(300);
  }

  // ===== FÉNYÉRZÉKELŐ =====

  int lightValue = analogRead(ldrPin);

  // AUTO mód
  if(!manualMode)
  {
    if(lightValue < 500)
    {
      lightState = true;
    }
    else
    {
      lightState = false;
    }
  }

  // LED vezérlés
  digitalWrite(lightLed, lightState);

  // ===== HŐMÉRSÉKLET =====

  int tempValue = analogRead(tempPin);

  float voltage = tempValue * 5.0 / 1023.0;
  float temperature = (voltage - 0.5) * 100;

  bool fanState = false;

  if(temperature > 25)
  {
    digitalWrite(fanLed, HIGH);
    fanState = true;
  }
  else
  {
    digitalWrite(fanLed, LOW);
    fanState = false;
  }

  // ===== LCD KIÍRÁS =====

  lcd.setCursor(0, 0);

  lcd.print("T:");
  lcd.print(temperature);
  lcd.print("C ");

  lcd.setCursor(0, 1);

  lcd.print("L:");

  if(lightState)
  {
    lcd.print("ON ");
  }
  else
  {
    lcd.print("OFF");
  }

  lcd.print(" F:");

  if(fanState)
  {
    lcd.print("ON ");
  }
  else
  {
    lcd.print("OFF");
  }

  delay(500);
}
