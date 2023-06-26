#include<ESP8266WiFi.h>
#include<ESP8266HTTPClient.h>

HTTPClient http;

const char* WIFINAME = "techinika";
const char* PASS = "12345678@tech";

WiFiServer server(80);

void setup() {

  Serial.begin(115200);
  delay(10);
  Serial.println("");

  pinMode(D0,OUTPUT); // green

  pinMode(D1,OUTPUT); // yellow

  pinMode(D2,OUTPUT); // red

  
  Serial.print("Connecting To ");
  Serial.println(WIFINAME);

  // configure the output pins

  
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFINAME, PASS);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi Connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.begin();
  delay(3000);

}

 

void loop() 

{
  WiFiClient client;
  client = server.available();

  if (client == 1) {
    String request = client.readStringUntil('\n');
    client.flush();
    Serial.println(request);
    if(request.indexOf("red") != -1){
      digitalWrite(D0,1);
      digitalWrite(D1,0);
      digitalWrite(D2,0);

      Serial.println("RED ON");
    }

    if(request.indexOf("yellow") != -1){
      digitalWrite(D0,0);
      digitalWrite(D1,1);
      digitalWrite(D2,0);

      Serial.println("YELLOW ON");
    }

    if(request.indexOf("green") != -1){
      digitalWrite(D0,0);
      digitalWrite(D1,0);
      digitalWrite(D2,1);

      Serial.println("GREEN ON");
    }

    if(request.indexOf("off") != -1){
      digitalWrite(D0,0);
      digitalWrite(D1,0);
      digitalWrite(D2,0);

      Serial.println("LEDs OFF");
    }

  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("");

  client.println("<!DOCTYPE html>");
  client.println("<html>");
  client.println("<head>");
  client.println("<title>Node MCU Controlled traffic Lights</title>");
  client.println("</head>");
  client.println("<body align=\"center\">");

  client.println("<div style=\"fontSize: 30px;width: 100%;margin: 30px;display: block;\">");
  client.println("<a href=\"/red\"><button style=\"fontSize: 30px;padding: 10px 20px;background-color: red;color: while;outline:none\">RED</button></a>");
  client.println("<a href=\"/yellow\"><button style=\"fontSize: 30px;padding: 10px 20px;background-color: yellow;color: while;outline:none\">YELLOW</button></a>");
  client.println("<a href=\"/green\"><button style=\"fontSize: 30px;padding: 10px 20px;background-color: green;color: while;outline:none\">GREEN</button></a>");

  client.println("<a href=\"/off\"><button style=\"fontSize: 30px;padding: 10px 20px;background-color: gray;color: while;outline:none\">OFF</button></a>");
  client.println("</div>");

  client.println("</body>");
  client.println("</html>");

  Serial.println("Client disconnected");
  Serial.println("_____________________");
  Serial.println("                     ");
  }

}
