#include <SPI.h>
#include <MFRC522.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <ESP32Servo.h>  // Servo library for ESP32
#include <BluetoothSerial.h>  // Bluetooth library for ESP32

#define SS_PIN 21
#define RST_PIN 22
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create an MFRC522 instance.

#define LCD_DC 4
#define LCD_CS 15
#define LCD_RST 2
Adafruit_PCD8544 display = Adafruit_PCD8544(LCD_DC, LCD_CS, LCD_RST);

Servo myservo;  // Create a Servo instance

int intrari = 1;
const int greenLED = 16;  // Pin for the green LED
const int redLED = 17;    // Pin for the red LED

BluetoothSerial SerialBT;  // Bluetooth instance

void setup() {
  Serial.begin(9600);   // Initialize serial communication
  SerialBT.begin("ESP32_BT");  // Initialize Bluetooth with the name "ESP32_BT"
  
  SPI.begin();          // Initialize the SPI bus
  mfrc522.PCD_Init();   // Initialize MFRC522
  Serial.println("Scan card");
  
  display.begin();
  display.setContrast(57);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(0, 20);
  display.println("Scan card");
  display.display();    // Display what is in the buffer

  myservo.attach(13);  // Attach servo to pin 13
  myservo.write(0);    // Set servo to initial position

  pinMode(greenLED, OUTPUT);  // Set green LED pin as output
  pinMode(redLED, OUTPUT);    // Set red LED pin as output

  digitalWrite(greenLED, LOW);  // Turn off green LED at startup
  digitalWrite(redLED, LOW);    // Turn off red LED at startup
}

void loop() {
  // Check if a new card is present
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return;
  }
  // Select one of the cards
  if (!mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  String content = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message: ");
  content.toUpperCase();

  display.clearDisplay();
  display.setCursor(25, 20);

  if (content.substring(1) == "60 65 12 14") { // change the UID here for the card(s) you want to grant access to
    if (intrari == 1) { 
      intrari = 0;
      display.println("ACCESS");
      Serial.println("Access granted");
      SerialBT.println("Access granted Ivan");  // Send message via Bluetooth
      myservo.write(180);  // Move servo to 180 degrees

      digitalWrite(greenLED, HIGH);  // Turn on green LED
      digitalWrite(redLED, LOW);     // Turn off red LED
    } else {
      intrari = 1;
      display.println("CLOSING");
      Serial.println("Closing");
      SerialBT.println("Closing Ivan");  // Send message via Bluetooth
      myservo.write(0);  // Move servo to 0 degrees

      digitalWrite(greenLED, LOW);  // Turn off green LED
      digitalWrite(redLED, HIGH);   // Turn on red LED
    }
  } 
  else if (content.substring(1) == "A6 5C 50 03") { // change the UID here for the card(s) you want to grant access to
    if (intrari == 1) { 
      intrari = 0;
      display.println("ACCESS");
      Serial.println("Access granted");
      SerialBT.println("Access granted Diana");  // Send message via Bluetooth
      myservo.write(180);  // Move servo to 180 degrees

      digitalWrite(greenLED, HIGH);  // Turn on green LED
      digitalWrite(redLED, LOW);     // Turn off red LED
    } else {
      intrari = 1;
      display.println("CLOSING");
      Serial.println("Closing");
      SerialBT.println("Closing Diana");  // Send message via Bluetooth
      myservo.write(0);  // Move servo to 0 degrees

      digitalWrite(greenLED, LOW);  // Turn off green LED
      digitalWrite(redLED, HIGH);   // Turn on red LED
    }
  } 
  else {
    display.println("WRONG");
    Serial.println("Access denied");
    SerialBT.println("Access denied");  // Send message via Bluetooth

    digitalWrite(greenLED, LOW);  // Turn off green LED
    digitalWrite(redLED, LOW);    // Turn off red LED
  }

  display.display();    // Display what is in the buffer
  delay(2000);

  // Return to the "Scan card" message
  display.clearDisplay();
  display.setCursor(0, 20);
  display.println("Scan card");
  display.display();
}