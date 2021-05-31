#include <WiFi.h>

const char* WIFI_NAME= "your wifi name";  
const char* WIFI_PASSWORD = "your wifi password";  
WiFiServer server(80);

String header;

String LED1 = "off";
String LED2 = "off";
String LED3 = "off";

const int GPIO_PIN_NUMBER_21 = 21;
const int GPIO_PIN_NUMBER_22 = 22;
const int GPIO_PIN_NUMBER_23 = 23;

void setup() {
  Serial.begin(115200);
  pinMode(GPIO_PIN_NUMBER_21, OUTPUT);
  pinMode(GPIO_PIN_NUMBER_22, OUTPUT);
  pinMode(GPIO_PIN_NUMBER_23, OUTPUT);

  digitalWrite(GPIO_PIN_NUMBER_21, LOW);
  digitalWrite(GPIO_PIN_NUMBER_22, LOW);
  digitalWrite(GPIO_PIN_NUMBER_23, LOW);



  Serial.print("Connecting to ");
  Serial.println(WIFI_NAME);
  WiFi.begin(WIFI_NAME, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
  delay(1000);
  Serial.print("Trying to connect to Wifi Network");
  }
  Serial.println("");
  Serial.println("Successfully connected to WiFi network");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop(){
  WiFiClient client = server.available();   
  if (client) {                            
    Serial.println("New Client is requesting web page");          
    String current_data_line = "";               
    while (client.connected()) {            
      if (client.available()) {             
        char new_byte = client.read();             
        Serial.write(new_byte);                    
        header += new_byte;
        if (new_byte == '\n') {                    
         
          if (current_data_line.length() == 0) 
          {
            
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

                if (header.indexOf("LED1=ON") != -1) 
            {
              Serial.println("GPIO21 LED is ON");
              LED1 = "on";
              digitalWrite(GPIO_PIN_NUMBER_21, HIGH);
            }
            if(header.indexOf("LED1=OFF") != -1) {
              Serial.println("GPIO21 LED is OFF");
              LED1 = "off";
              digitalWrite(GPIO_PIN_NUMBER_21, LOW);
            }
            
            
            if (header.indexOf("LED1=ON") != -1) 
            {
              Serial.println("GPIO22 LED is ON");
              LED2 = "on";
              digitalWrite(GPIO_PIN_NUMBER_22, HIGH);
            } 
            if (header.indexOf("LED1=OFF") != -1) 
            {
              Serial.println("GPIO22 LED is OFF");
              LED2 = "off";
              digitalWrite(GPIO_PIN_NUMBER_22, LOW);
            } 
            if (header.indexOf("LED3=ON") != -1)
            {
              Serial.println("GPIO23 LED is ON");
              LED3 = "on";
              digitalWrite(GPIO_PIN_NUMBER_23, HIGH);
            }
            if (header.indexOf("LED3=OFF") != -1) 
            {
              Serial.println("GPIO23 LED is OFF");
              LED3 = "off";
              digitalWrite(GPIO_PIN_NUMBER_23, LOW);
            }
        
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #4CAF50; border: 2px solid #4CAF50;; color: white; padding: 15px 32px; text-align: center; text-decoration: none; display: inline-block; font-size: 16px; margin: 4px 2px; cursor: pointer; }");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");            
            // Web Page Heading
            client.println("</style></head>");
            client.println("<body><center><h1>ESP32 server to control led </h1></center>");
            client.println("<center><h2>Tutorial esp32 led </h2></center>" );
            client.println("<center><h2>Press on button to turn on led and off button to turn off LED</h3></center>");
            client.println("<form><center>");
            client.println("<p> LED pertama adalah" + LED1 + "</p>");
            // If the PIN_NUMBER_22State is off, it displays the ON button      
             client.println("<center> <button class=\"button\" name=\"LED0\" value=\"ON\" type=\"submit\">LED0 ON</button>") ;
             client.println("<button class=\"button\" name=\"LED0\" value=\"OFF\" type=\"submit\">LED0 OFF</button><br><br>");
             client.println("<p>LED ke 2 adalah " + LED2 + "</p>");
             client.println("<button class=\"button\" name=\"LED1\" value=\"ON\" type=\"submit\">LED1 ON</button>");
             client.println("<button class=\"button\" name=\"LED1\" value=\"OFF\" type=\"submit\">LED1 OFF</button> <br><br>");
             client.println("<p>LED ke 3 adalah  " + LED3 + "</p>");
             client.println ("<button class=\"button\" name=\"LED2\" value=\"ON\" type=\"submit\">LED2 ON</button>");
             client.println ("<button class=\"button\" name=\"LED2\" value=\"OFF\" type=\"submit\">LED2 OFF</button></center>");
            client.println("</center></form></body></html>");
            client.println();
            break;
          } 
          else 
          { 
            current_data_line = "";
          }
        } 
        else if (new_byte != '\r') 
        {  
          current_data_line += new_byte;     
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
