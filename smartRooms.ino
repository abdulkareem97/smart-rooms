#include <ESP8266WiFi.h>

const char* ssid = "ZEE_BROADBAND_0157";
const char* password = "Abdul6082";
WiFiServer server(80);
int LED_PIN = 2;

void setup() {
  Serial.begin(9600);
  delay(10);

  // connect to WiFi
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  pinMode(LED_PIN, OUTPUT);

  // start the server
  server.begin();
}

void loop() {
  // wait for a client to connect
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  // read the message from the client
  while (client.connected()) {
    if (client.available()) {
      String message = client.readStringUntil('\r');
      message = message.substring(message.length()-1);
      // int val = parseInt(message)
      Serial.println(message);
      if(message.equals("1"))
      {
          digitalWrite(LED_PIN, LOW);

      }
      else if(message.equals("0")){
  digitalWrite(LED_PIN, HIGH);
      }
    }
  }

  // close the connection
  client.stop();
}

