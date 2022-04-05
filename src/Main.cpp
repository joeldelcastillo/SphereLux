#include "Arduino.h"
#include "MainServer.h"
#include "Sphere.h"

// MainServer test(8);
Sphere light;
MainServer accessPoint("accessPoint");
int counter = 0;
int anim = 0;
int numAnim = 6;
unsigned long previousMillis = 0;
const long interval = 300000;

AsyncWebServer server(80);

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <title>ESP Web Server</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="icon" href="data:,">
  <style>
    html {font-family: Arial; display: inline-block; text-align: center;}
    h2 {font-size: 3.0rem;}
    p {font-size: 3.0rem;}
    body {margin:0px auto; padding-bottom: 25px;}
  </style>
</head>
  <body>
    <div>
      <input
        type="range"
        id="cowbell"
        name="cowbell"
        min="0"
        max="100"
        value="90"
        step="5"
      />
      <output></output>
      <label for="cowbell">Cowbell</label>
    </div>
    <script>
      let i = document.querySelector("input"),
        o = document.querySelector("output");

      o.innerHTML = i.value;

      // use 'change' instead to see the difference in response
      i.addEventListener(
        "input",
        function () {
          var xhr = new XMLHttpRequest();
          o.innerHTML = i.value;
          xhr.open("GET", "/b0?anim=" + i.value, true);
          xhr.send();
        },
        false
      );
      
    </script>
  </body>
</html>
)rawliteral";

void setup()
{
  Serial.begin(9600);
  light.setPins();
  accessPoint.setAccess();

  server.on("/lux", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(200, "text/html", index_html); });

  server.on("/b0", HTTP_GET, [](AsyncWebServerRequest *request)
            {
      if (request->hasParam("anim"))
      {
        // Valor de error
        String animS = request->getParam("anim")->value();
        anim = animS.toInt();
        Serial.println(anim);
        request->send_P(200, "text/html", "bien bro");
      } });

  // Start server
  server.begin();
}

void loop()
{

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval)
  {
    anim = (anim + 1) % numAnim;
    previousMillis = currentMillis;
  }

  counter++;
  switch (anim)
  {
  case 0:
    light.waveIntensity(counter, 220);
    break; // optional
  case 1:
    light.rainbow(counter);
    break; // optional
  case 2:
    light.simpleColor(counter);
    break; // optional
  case 3:
    light.danceFalf(counter * 20, 0, 180);
    //    light.percentageAll(counter%100,50);
    break; // optional
  case 4:
    light.danceFalf(counter, 10, 50);
    // light.percentageAll(counter, 70);
    break; // optional
  case 5:
    light.partitionAll(counter, 20, 100);
    break; // optional
  default:
    light.percentageAll(counter % 100, 50);
    break; // optional
  }
}
