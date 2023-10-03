#include <common.h>
#include <FirebaseFS.h>
#include <Utils.h>

/*
  Rui Santos
  Complete project details at our blog.
    - ESP32: https://RandomNerdTutorials.com/esp32-firebase-realtime-database/
    - ESP8266: https://RandomNerdTutorials.com/esp8266-nodemcu-firebase-realtime-database/
  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files.
  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
  Based in the RTDB Basic Example by Firebase-ESP-Client library by mobizt
  https://github.com/mobizt/Firebase-ESP-Client/blob/main/examples/RTDB/Basic/Basic.ino
*/


#include <ESP8266WiFi.h>
#include <Firebase_ESP_Client.h>

//Provide the token generation process info.
#include "addons/TokenHelper.h"
//Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

// Insert your network credentials
#define WIFI_SSID "CodeMI5"
#define WIFI_PASSWORD "inioluwa900"

// Insert Firebase project API Key

#define API_KEY "AIzaSyDHbS4XElfWhNto8zaQeTOueESWbDcfH5k"

// Insert RTDB URLefine the RTDB URL */
#define DATABASE_URL "saflyapp-default-rtdb.firebaseio.com" 

//Define Firebase Data object
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

int intValue;
bool signupOK = false;

//const int buttonPin = D2;    // Pin connected to the button
const int relayPin = 5;     // Pin connected to the relay
const int moisturePin = A0;  // Pin connected to the moisture sensor

//bool isButtonPressed = false;

FirebaseData firebaseData;

void setup() {
  Serial.begin(115200);

//  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW); // Turn off the relay initially

  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
 /* Assign the api key (required) */
  config.api_key = API_KEY;

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;

  /* Sign up */
  if (Firebase.signUp(&config, &auth, "", "")){
    Serial.println("ok");
   signupOK = true;
  }
  else{
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }

  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h
  
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

}

void loop() {
  // Read the button state
//  bool buttonState = digitalRead(buttonPin);

  // Check if the button is pressed
//  if (buttonState == LOW && !isButtonPressed) {
//    isButtonPressed = true;
//    Serial.println("Button pressed");
//
//    // Toggle the relay state
//    digitalWrite(relayPin, !digitalRead(relayPin));
//  }

  // Check if the button is released
//  if (buttonState == HIGH && isButtonPressed) {
//    isButtonPressed = false;
//  }

  // Read moisture sensor value
  int moistureValue = analogRead(moisturePin);

  // Map the moisture value to a range of 0-100
  int moisturePercentage = map(moistureValue, 0, 1023, 100, 0);

  if (moisturePercentage <= 40) {
      digitalWrite(relayPin, digitalRead(relayPin));
  }
  if (moisturePercentage >= 40) {
      digitalWrite(relayPin, !digitalRead(relayPin));
  } 

  
  // Send moisture value to Firebase
//  if (Firebase.RTDB.setInt(&fbdo, "moistureValue", moisturePercentage)) {
//    Serial.println("Moisture value sent to Firebase");
//  } else {
//    Serial.println("Firebase connection failed");
//  }

  delay(100); // Add a small delay for stability
}
