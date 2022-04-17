#include "Arduino.h"
#include "Server.h"
#include "Sphere.h"
#include "Helper.h"

// MainServer test(8);
Sphere light("Light");
Helper document("Helper");
MainServer accessPoint("accessPoint");
int counter = 0;
int anim = 9;
int hue = 40;
int sat = 100;
int val = 0;
int ex = 1;
int numAnim = 10;
unsigned long previousMillis = 0;
const long interval = 300000;

AsyncWebServer server(80);

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <title>Lux Sphere</title>
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
      <input type="range" id="i0" min="0" max="255" value="0" step="5" />
      <output id="o0"></output>
      <label for="i0">Hue</label>
    </div>
    <div>
      <input type="range" id="i1" min="0" max="100" value="0" step="5" />
      <output id="o1"></output>
      <label for="i1">Sat</label>
    </div>
    <div>
      <input type="range" id="i2" min="0" max="100" value="0" step="5" />
      <output id="o2"></output>
      <label for="i2">Val</label>
    </div>
    <div>
      <input type="range" id="i3" min="0" max="100" value="0" step="1" />
      <output id="o3"></output>
      <label for="i2">Ex</label>
    </div>
    <script>
      let i0 = document.getElementById("i0");
      let o0 = document.getElementById("o0");
      o0.innerHTML = i0.value;
      i0.addEventListener(
        "input",

        function () {
          var xhr = new XMLHttpRequest();
          o0.innerHTML = i0.value;
          xhr.open("GET", "/b0?hue=" + i0.value, true);
          xhr.send();
        },
        false
      );
    </script>

    <script>
      let i1 = document.getElementById("i1");
      let o1 = document.getElementById("o1");
      o1.innerHTML = i1.value;
      i1.addEventListener(
        "input",
        function () {
          var xhr = new XMLHttpRequest();
          o1.innerHTML = i1.value;
          xhr.open("GET", "/b1?sat=" + i1.value, true);
          xhr.send();
        },
        false
      );
    </script>

    <script>
      let i2 = document.getElementById("i2");
      let o2 = document.getElementById("o2");
      o2.innerHTML = i2.value;
      i2.addEventListener(
        "input",
        function () {
          var xhr = new XMLHttpRequest();
          o2.innerHTML = i2.value;
          xhr.open("GET", "/b2?val=" + i2.value, true);
          xhr.send();
        },
        false
      );
    </script>

    <script>
      let i3 = document.getElementById("i3");
      let o3 = document.getElementById("o3");
      o3.innerHTML = i3.value;
      i3.addEventListener(
        "input",
        function () {
          var xhr = new XMLHttpRequest();
          o3.innerHTML = i3.value;
          xhr.open("GET", "/b3?ex=" + i3.value, true);
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

  server.on("/ch", HTTP_GET, [](AsyncWebServerRequest *request)
            {
              String animS = request->getParam("anim")->value();
              anim = animS.toInt();
              Serial.println(anim);
              request->send_P(200, "text/plain", "bien bro"); });

  server.on("/b0", HTTP_GET, [](AsyncWebServerRequest *request)
            {
              String hueS = request->getParam("hue")->value();
              hue = hueS.toInt();
              Serial.println(hue);
              request->send_P(200, "text/plain", "bien bro"); });

  server.on("/b1", HTTP_GET, [](AsyncWebServerRequest *request)
            {
              String satS = request->getParam("sat")->value();
              sat = satS.toInt();
              Serial.println(sat);
              request->send_P(200, "text/plain", "bien bro"); });

  server.on("/b2", HTTP_GET, [](AsyncWebServerRequest *request)
            {
              String valS = request->getParam("val")->value();
              val = valS.toInt();
              Serial.println(val);
              request->send_P(200, "text/plain", "bien bro"); });

  server.on("/b3", HTTP_GET, [](AsyncWebServerRequest *request)
            {
              String exS = request->getParam("ex")->value();
              ex = exS.toInt();
              Serial.println(ex);
              request->send_P(200, "text/plain", "bien bro"); });
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
    light.waveIntensity(counter, hue, ex);
    break; // optional
  case 1:
    light.rainbow(counter);
    break; // optional
  case 2:
    light.simpleColor(counter);
    break; // optional
  case 3:
    light.danceFalf(counter * ex, 0, hue);
    //    light.percentageAll(counter%100,50);
    break; // optional
  case 4:
    light.danceFalf(counter  * ex, 10, hue);
    // light.percentageAll(counter, 70);
    break; // optional
  case 5:
    light.partitionAll(counter* ex, 4, hue);
    break; // optional
    case 6:
    light.chaosAll(sat,counter* ex,hue,100);
    break;
  case 7:
    light.busAll(15,counter* ex,hue,100);
    break;
  case 8:
    light.busAll(sat,-counter* ex,hue,100);
    break;
  case 9:
 
    light.exp(counter,hue);
    break;
  default:
    light.percentageAll((counter * ex) % 100, hue);
    break; // optional
  }
}
