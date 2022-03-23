#include <UrlEncode.h>

void setup()
{
    Serial.begin(115200);
    String encoded = urlEncode("Hello, this string should be \% encoded.");
    Serial.println(encoded);
    // -> Hello%2C%20this%20string%20should%20be%20%25%20encoded.
  
    String decoded = urlDecode(encoded);
    Serial.println(edeoded); 
    // -> Hello, this string should be % encoded.
}

void loop() {}
