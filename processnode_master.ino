#include <ESP8266WiFi.h>
#include<ESP8266HTTPClient.h>

String  i;
String j;
long rssi_slave;int mag;int rssi_avg;int magn;int mago;int magdiff;
IPAddress staticIP33_205(192,168,43,6);
IPAddress gateway33_205(192,168,1,1);
IPAddress subnet33_205(255,255,255,0);

WiFiServer server(80);
String httpurl;
String TheHiddenAnswerOfClient;
HTTPClient http;

String SendWithAnswer(String IPcache, String monmessagecache) {
httpurl = "http://";
httpurl+=IPcache;
httpurl+="/";
httpurl+=monmessagecache;
http.begin(httpurl);
http.GET();
TheHiddenAnswerOfClient = (http.getString());
http.end();
return TheHiddenAnswerOfClient;
}

void setup()
{
  i = "";j=" ";
  rssi_slave=0;rssi_avg=0;mago=0;magn=0;magdiff=0;
  Serial.begin(9600);
    delay(100);
  WiFi.disconnect();
   WiFi.begin("ener1234","ener7416");
  WiFi.config(staticIP33_205, gateway33_205, subnet33_205);
  //Serial.println((WiFi.localIP()));
  server.begin();
  pinMode(5,OUTPUT);
  pinMode(4,OUTPUT);
  
}


void loop()
{
    //to get orientation
    WiFiClient client = server.available();
    if (!client) { return; }
    while(!client.available()){  delay(1); }
    //Serial.println((client.remoteIP()));
    i = (client.readString());
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("");
    client.println("<!DOCTYPE HTML>");
    client.println("<html>");
    client.println(".");
    client.println("</html>");
    //Serial.println(i.length());
    //Serial.println(i);
    i.remove(0,211);
    mag=i.toInt();
    client.stop();
    // to get rssi of other nodemcu
    j = (SendWithAnswer("192.168.43.10"," "));
    j.remove(0, 25);
    j.remove(j.length()-11,11);
    rssi_slave = j.toInt();
    Serial.println(rssi_slave);
    rssi_avg=(WiFi.RSSI()+rssi_slave)/2;
    //rssi_avg and mag worked fine
    Serial.println(rssi_avg);
    Serial.println(mag);
    if(mag<0){
      mag=360+mag;
    }
    mago=magn;
    magn=mag;
    magdiff=mago-magn;
    if(abs(magdiff)<200){
    
    //Serial.println(magdiff);
    if (abs(magdiff)>20){ 
    if (magdiff<0){
         digitalWrite(5,HIGH);
         digitalWrite(4,LOW);
         delay((magdiff+10)*10*-1);
         digitalWrite(5,LOW);
         Serial.println("left");
    }
    else{
      digitalWrite(5,LOW);
      digitalWrite(4,HIGH);
      delay((magdiff+10)*10);
      digitalWrite(4,LOW);
      Serial.println("right");
    }
    }}
    if(rssi_avg<-45)
    {digitalWrite(5,HIGH);
    digitalWrite(4,HIGH);
    delay((rssi_avg+45)*35*-1);
    digitalWrite(5,LOW);
    digitalWrite(4,LOW);
    Serial.println("straight");
    }
}
