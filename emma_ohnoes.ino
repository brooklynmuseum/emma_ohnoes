#include <Bridge.h>
#include <Temboo.h>
#include "TembooAccount.h" // Contains Temboo account info, you'll need your own

int blueLed = 13;
int redLed = 9;
int brightness = 0; // Start out LED with no brightness
int fadeAmount = 5; // Points to fade the LED by
// Replace our url with your website to check if it's up
String targetUrl = "http://www.brooklynmuseum.org/healthcheck.php";

void setup() {
  // For debugging, wait until the serial console is connected.
  //Serial.begin(9600);
  //delay(4000);
  //while(!Serial);
  Bridge.begin();
  pinMode(blueLed, OUTPUT);
  pinMode(redLed, OUTPUT);
}

void loop() {
  TembooChoreo GetChoreo;
  // Invoke the Temboo client
  GetChoreo.begin();
  // Set Temboo account credentials
  GetChoreo.setAccountName(TEMBOO_ACCOUNT);
  GetChoreo.setAppKeyName(TEMBOO_APP_KEY_NAME);
  GetChoreo.setAppKey(TEMBOO_APP_KEY);
  // Custom user agent for less confusing logs
  GetChoreo.addInput("RequestHeaders", "{\n    \"User-Agent\": \"Emma Ohnoes (Arduino Yún/Temboo)\"\n}");
  // Replace our healthcheck.php url with your website to check if it's up
  GetChoreo.addInput("URL", targetUrl);
  // Plain GET request
  GetChoreo.setChoreo("/Library/Utilities/HTTP/Get");
  // Run the Choreo, save return code. 0 is ok, 223 means non-200 status from healthcheck
  int returnCode = GetChoreo.run();

  // AWSPOCALYPSE!
  if (returnCode == 223) {
    // switch off white light
    digitalWrite(blueLed, LOW);
    pulseRedLed();
  }
  else { // Emma O's in his heaven. All's right in the world.
    while(GetChoreo.available()) {
      //char c = GetChoreo.read();
      //Serial.print(c);
      
      // turn off red led in case it was on
      analogWrite(redLed, 0);
      // turn on white light to indicate Temboo's working at least
      digitalWrite(blueLed, HIGH);
    }
  }
  
  GetChoreo.close();
  //Serial.println("Pinging healthcheck again...");
  delay(60000); // wait a minute seconds between GET calls
}

void pulseRedLed() {
  // turn on and pulse red light
  while (brightness <= 255) {
    analogWrite(redLed, brightness);
    // change the brightness for next time through the loop:
    brightness = brightness + fadeAmount;
    // reverse the direction of the fading at the ends of the fade:
    if (brightness == 0 || brightness == 255) {
      fadeAmount = -fadeAmount ;
    }
    // wait for 30 milliseconds to see the dimming effect    
    delay(30);
  }
}
