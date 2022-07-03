#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char *ssid = "Room 39";
const char *pwd = "8983375797";
const char *server = "192.168.1.208";
uint16_t port = 4000;

void send_request()
{

  WiFiClient wifiClient;
  HTTPClient http;

  char buff[20], url[50];
  float temperature = 50.34;

  sprintf(buff, "temperature=%.2f", temperature);
  sprintf(url, "http://%s:%hu/temperature", server, port);
  http.begin(wifiClient, url);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  Serial.printf("URL: %s\n", url);
  int httpcode = http.POST(buff);
  Serial.printf("Status code: %d\n", httpcode);
  http.end();
}

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.flush();

  Serial.printf("Connecting to %s\n", ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pwd);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.printf("\nWifi connected\nIP: ");
  Serial.println(WiFi.localIP());

}

void loop()
{
  // put your main code here, to run repeatedly:
  send_request();
  delay(5000);
}