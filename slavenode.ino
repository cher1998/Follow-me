#include <ESP8266WiFi.h>

String  i;
IPAddress staticIP33_205(192,168,43,10);
IPAddress gateway33_205(192,168,1,1);
IPAddress subnet33_205(255,255,255,0);

WiFiServer server(80);

void setup()
{
  i = "";

  Serial.begin(9600);

    delay(1000);
  WiFi.disconnect();
   WiFi.begin("ener1234","ener7416");
  WiFi.config(staticIP33_205, gateway33_205, subnet33_205);
  Serial.println((WiFi.localIP()));
  server.begin();

}


void loop()
{

    WiFiClient client = server.available();
    if (!client) { return; }
    while(!client.available()){  delay(1); }
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("");
    client.println("<!DOCTYPE HTML>");
    client.println("<html>");
    client.println(WiFi.RSSI());
    //Serial.println(WiFi.RSSI());
    client.println("</html>");
    client.stop();
    delay(1);

}
