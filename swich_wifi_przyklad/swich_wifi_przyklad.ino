
#include <ESP8266WiFi.h>
#include <Ticker.h>
#include <Math.h>

 const char* ssid = "0000000"; //nazwa ssid sieci
const char* password = "000000"; //haslo

#define przekaznik 5

WiFiServer server(80);

char kolor[] = "black";




void setup() {
 Serial.begin(115200);
  delay(10);
  pinMode(przekaznik, OUTPUT);
  digitalWrite(przekaznik, HIGH);

  //Laczenie z siecia wifi
  Serial.println();
  Serial.println();
  Serial.print("Laczenie z: ");
  Serial.println(ssid);
 
  IPAddress ip(000, 000, 0, 000); //preferowany adres IP
  IPAddress gateway(000, 000, 0, 0); // wpisać swoje 
  IPAddress subnet(000, 000, 000, 0); 
  WiFi.config(ip, gateway, subnet);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi polaczone");



// Start serwera
  server.begin();
  Serial.println("Serwer uruchomiony"); 

 

}
 

void loop() {
   while (WiFi.status() == WL_CONNECTED){
   
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 String request = client.readStringUntil('\r');
  client.flush();

 //wlaczenie zasialania piekarnika
 if (request.indexOf("/turnOn") > 0)  
  {
    digitalWrite(przekaznik, LOW); //działa
   }
  if (request.indexOf("/turnOff") > 0)  //nie działa
  {
   digitalWrite(przekaznik, HIGH);
  }
   //Zwroc odpowiedz
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<head>");
  client.println("<meta name='apple-mobile-web-app-capable' content='yes' />");
  client.println("<meta name='apple-mobile-web-app-status-bar-style' content='black-translucent' />");
  client.println("</head>");
  client.println("<body bgcolor = \"#FFCC66\">"); 
  client.println("<hr/><hr>");
  client.println("<h4><center>Switch</center></h4>");
  client.println("<hr/><hr>");
  client.println("<br><br>");
  client.println("<center>");
  client.print("<font color= ");
  client.print(kolor);
  client.println(" >");
  client.println("Zasilanie");
  client.print("</font>");
  client.println("<a href=\"/turnOn\"\"><button>Wlacz </button></a>");
  client.println("<a href=\"/turnOff\"\"><button>Wylacz </button></a><br />");  
  client.println("<hr/><hr>");
  client.println("</center>");   
  client.println("<br><br>");
  client.println("</html>"); 
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
 }
 
//setup(); //ponowne laczenie z siecia wifi w przypadku rozlaczenia
 
}
