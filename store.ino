//libraries
#if defined(ESP32)
  #include <WiFi.h>
#elif defined(ESP8266)
  #include <ESP8266WiFi.h>
#endif
#include <Firebase_ESP_Client.h>

//network credentials
#define WIFI_SSID "REPLACE_WITH_YOUR_SSID"
#define WIFI_PASSWORD "REPLACE_WITH_YOUR_PASSWORD"

//token generation process info
#include "addons/TokenHelper.h"

//RTDB payload printing info and other helper functions
#include "addons/RTDBHelper.h"

// Defines the Digital Pin of the "On Board LED".
#define On_Board_LED 2

// Insert Firebase project API Key & Database URL
#define API_KEY "REPLACE_WITH_YOUR_FIREBASE_PROJECT_API_KEY"
#define DATABASE_URL "https://location-db-8a93a-default-rtdb.asia-southeast1.firebasedatabase.app/" 

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;
const long sendDataIntervalMillis = 10000; //Sends/stores data to firebase database every 10 seconds.

bool signupOK = false;
float store_random_Float_Val;
int store_random_Int_Val;

void setup() {
  Serial.begin(115200);
  Serial.println();

  pinMode(On_Board_LED, OUTPUT);

  //Connecting the WiFi on the ESP32 to the WiFi Router/Hotspot
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.println("---------------Connection");
  Serial.print("Connecting to : ");
  Serial.println(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    digitalWrite(On_Board_LED, HIGH);
    delay(250);
    digitalWrite(On_Board_LED, LOW);
    delay(250);
  }
  digitalWrite(On_Board_LED, LOW);
  Serial.println();
  Serial.print("Successfully connected to : ");
  Serial.println(WIFI_SSID);
  //Serial.print("IP : ");
  //Serial.println(WiFi.localIP());
  Serial.println("---------------");

  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;

  Serial.println();
  Serial.println("---------------Sign up");
  Serial.print("Sign up new user... ");
  if (Firebase.signUp(&config, &auth, "", "")){
    Serial.println("ok");
    signupOK = true;
  }
  else{
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }
  Serial.println("---------------");
  
  // Assign the callback function for the long running token generation task.
  config.token_status_callback = tokenStatusCallback; //--> see addons/TokenHelper.h
  
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void loop() {
  if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > sendDataIntervalMillis || sendDataPrevMillis == 0)){
    sendDataPrevMillis = millis();

    //---------------------------------------- Generate random values.
    int randNumber = random(15, 40);
    float f = (float)randNumber / 1.01;
    int i = (int(f*100));
    store_random_Float_Val = float(i) / 100;
    store_random_Int_Val = random(10, 99);
    Serial.println();
    Serial.println("---------------Random Value");
    Serial.print("Random Float_Val : ");
    Serial.println(store_random_Float_Val);
    Serial.print("Random Int_Val   : ");
    Serial.println(store_random_Int_Val);
    Serial.println("---------------");

    //Send/store data to the firebase database
    Serial.println();
    Serial.println("---------------Store Data");
    digitalWrite(On_Board_LED, HIGH);
    
    // Write an Int number on the database path test/random_Float_Val.
    if (Firebase.RTDB.setFloat(&fbdo, "Test/random_Float_Val", store_random_Float_Val)) {
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }
    
    // Write an Float number on the database path test/random_Int_Val.
    if (Firebase.RTDB.setInt(&fbdo, "Test/random_Int_Val", store_random_Int_Val)) {
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }
    
    digitalWrite(On_Board_LED, LOW);
    Serial.println("---------------");
  }
}