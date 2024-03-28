#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoOTA.h>
#include <WiFiManager.h>




const char* ssid = "ssid for connection portal"; 
const char* password = "password for connection portal";
const char* home_assistant_url = "enter your home assistant url"; //for exemple https://your-domaine.duckdns.org/api/services/script/sonnette or http://your-serveur-ip/api/services/script/sonnette
const char* home_assistant_token = "enter your home assistant api token";
const char* arduino_ota_hotname = "enter a arduino ota hostname for remote programmation";
const char* arduino_ota_password = "enter a arduino ota password for remote programmation";

int button_state;
int button_pin = 5;

void envoie_HA();

WiFiManager wm;



void setup() {
  // put your setup code here, to run once:
  pinMode(5,OUTPUT);
  Serial.begin(9600);
  Serial.println("Booting");
  WiFi.mode(WIFI_STA);
  if(!wm.autoConnect(ssid, password)){
    Serial.println("Erreur de connexion.");
  }
  // Port defaults to 8266
  // ArduinoOTA.setPort(8266);

  // Hostname defaults to esp8266-[ChipID]
  ArduinoOTA.setHostname(arduino_ota_hotname);

  // No authentication by default
  ArduinoOTA.setPassword(arduino_ota_password);

  // Password can be set with it's md5 value as well
  // MD5(admin) = 21232f297a57a5a743894a0e4a801fc3
  // ArduinoOTA.setPasswordHash("21232f297a57a5a743894a0e4a801fc3");

  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else {  // U_FS
      type = "filesystem";
    }

    // NOTE: if updating FS this would be the place to unmount FS using FS.end()
    Serial.println("Start updating " + type);
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      Serial.println("Auth Failed");
    } else if (error == OTA_BEGIN_ERROR) {
      Serial.println("Begin Failed");
    } else if (error == OTA_CONNECT_ERROR) {
      Serial.println("Connect Failed");
    } else if (error == OTA_RECEIVE_ERROR) {
      Serial.println("Receive Failed");
    } else if (error == OTA_END_ERROR) {
      Serial.println("End Failed");
    }
  });
  ArduinoOTA.begin();
  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());


}

void loop() {
  // put your main code here, to run repeatedly:
  ArduinoOTA.handle();
  button_state = digitalRead(button_pin);
  if (button_state == HIGH){
    Serial.println("la sonnette vien de se déclancher !!");
    Serial.println(button_state);
    envoie_HA();
    delay(2500);
  }
  delay(500);
}


void envoie_HA() {
  HTTPClient client;

  client.begin(home_assistant_url);
  
  // Concaténation de "Bearer " avec home_assistant_token
  char authorizationHeader[100];
  snprintf(authorizationHeader, sizeof(authorizationHeader), "Bearer %s", home_assistant_token);

  // Utilisation de la chaîne concaténée comme en-tête "Authorization"
  client.addHeader("Authorization", authorizationHeader);
  client.addHeader("content-type", "application/json");

    

  int http_reponse = client.POST("");
  Serial.println(http_reponse);
  String payload = client.getString();
  Serial.println(payload);
  client.end();
}