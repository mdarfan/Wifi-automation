#include <ESP8266WiFi.h>
 
//const char* ssid = "MSB";
//const char* password = "bautomate";
 
int ledPin1 =5;  //D1
int ledPin2 =4;  //D2
int ledPin3 =0;  //D3
int ledPin4 =2;  //D4

int ledPin9 =3; //INDICATION (RX GPIO 03)

String value1 = "OFF";
String value2 = "OFF";
String value3 = "OFF";
String value4 = "OFF";
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h> 


WiFiServer server(80);
 
void setup() {
Serial.begin(115200);
delay(10);
 
 
 pinMode(ledPin1, OUTPUT);
 pinMode(ledPin2, OUTPUT);
 pinMode(ledPin3, OUTPUT);
 pinMode(ledPin4, OUTPUT);
 
 pinMode(ledPin9, OUTPUT);
        
  digitalWrite(ledPin1, LOW);
  digitalWrite(ledPin2, LOW);
  digitalWrite(ledPin3, LOW);
  digitalWrite(ledPin4, LOW);
 
  digitalWrite(ledPin9, LOW);
 
  // Connect to WiFi network
  
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  WiFiManager wifiManager;
  wifiManager.autoConnect("AutoConnectAP");
  //Serial.println(ssid);
 
  //WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("connected...yeey :)");
  digitalWrite(ledPin9, HIGH);
 
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
 
}
 
void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
 
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
 
  // Match the request
 
    
  if (request.indexOf("/LED1=ON") != -1)  {
    digitalWrite(ledPin1, HIGH);
    Serial.println("on1");
    value1 = "ON";
  }
  if (request.indexOf("/LED1=OFF") != -1)  {
    digitalWrite(ledPin1, LOW);
    value1 = "OFF";
    Serial.println("off1");
  }

   if (request.indexOf("/LED2=ON") != -1)  {
    digitalWrite(ledPin2, HIGH);
    Serial.println("on1");
    value2 ="ON";
  }
  if (request.indexOf("/LED2=OFF") != -1)  {
    digitalWrite(ledPin2, LOW);
    value2 ="OFF";
    Serial.println("off1");
  }

   if (request.indexOf("/LED3=ON") != -1)  {
    digitalWrite(ledPin3, HIGH);
    value3 = "ON";
    Serial.println("on1");
  }
  if (request.indexOf("/LED3=OFF") != -1)  {
    digitalWrite(ledPin3, LOW);
    value3 = "OFF";
    Serial.println("off1");
  }

   if (request.indexOf("/LED4=ON") != -1)  {
    digitalWrite(ledPin4, HIGH);
    value4 ="ON";
    Serial.println("on1");
  }
  if (request.indexOf("/LED4=OFF") != -1)  {
    digitalWrite(ledPin4, LOW);
    value4 ="OFF";
    Serial.println("off1");
  }

    
  
 
   // Set ledPin according to the request
   //digitalWrite(ledPin, value);
 
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
 
  
  client.println("<br><br>");
  client.println("<a href=\"/LED1=ON\"\"><button>Turn On1 </button></a>");
  client.println("&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp");
  client.println("<a href=\"/LED1=OFF\"\"><button>Turn Off 1</button></a><br />");
  client.println("<br><br>");
  client.print("Led pin1 is now: ");
 
  client.print(value1);
  


  client.println("<br><br>");
  client.println("<a href=\"/LED2=ON\"\"><button>Turn On2 </button></a>");
  client.println("&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp");
  client.println("<a href=\"/LED2=OFF\"\"><button>Turn Off 2</button></a><br />");
  client.println("<br><br>");
  client.print("Led pin2 is now: ");
 
  client.print(value2);

  client.println("<br><br>");
  client.println("<a href=\"/LED3=ON\"\"><button>Turn On3 </button></a>");
  client.println("&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp");
  client.println("<a href=\"/LED3=OFF\"\"><button>Turn Off 3</button></a><br />");
  client.println("<br><br>");
  client.print("Led pin3 is now: ");
 
  client.print(value3);

  client.println("<br><br>");
  client.println("<a href=\"/LED4=ON\"\"><button>Turn On4 </button></a>");
  client.println("&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp");
  client.println("<a href=\"/LED4=OFF\"\"><button>Turn Off 4</button></a><br />");
  client.println("<br><br>");
  client.print("Led pin4 is now: ");
 
  client.print(value4);
  
  
  

 client.println("</html>");
 
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
 
}
 
