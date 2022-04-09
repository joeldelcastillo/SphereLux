#include "Arduino.h"
#include "Server.h"
#include "Sphere.h"
#include "Helper.h"

// MainServer test(8);
Sphere light("Light");
Helper document("Helper");
MainServer accessPoint("accessPoint");
int counter = 0;
int anim = 7;
int hue = 0;
int sat = 0;
int val = 0;
int ex = 0;
int numAnim = 10;
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
      <input type="range" id="i0" min="0" max="255" value="0" step="5" />
      <output id="o0"></output>
      <label for="">Hue</label>
    </div>
    <div>
      <input type="range" id="i1" min="0" max="255" value="0" step="5" />
      <output id="o1"></output>
      <label for="">Sat</label>
    </div>
    <div>
      <input type="range" id="i2" min="0" max="255" value="0" step="5" />
      <output id="o2"></output>
      <label for="">Val</label>
    </div>
    <div>
      <input type="range" id="i3" min="0" max="100" value="0" step="5" />
      <output id="o3"></output>
      <label for="">Ex</label>
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
      let i1 = document.querySelector("i1");
      let o1 = document.querySelector("o1");
      o1.innerHTML = i1.value;
      i1.addEventListener(
        "input",
        function () {
          var xhr = new XMLHttpRequest();
          o1.innerHTML = i1.value;
          xhr.open("GET", "/b0?sat=" + i1.value, true);
          xhr.send();
        },
        false
      );
    </script>

    <script>
      let i2 = document.querySelector("i2");
      let o2 = document.querySelector("o2");
      o2.innerHTML = i2.value;
      i2.addEventListener(
        "input",
        function () {
          var xhr = new XMLHttpRequest();
          o2.innerHTML = i2.value;
          xhr.open("GET", "/b0?val=" + i2.value, true);
          xhr.send();
        },
        false
      );
    </script>

    <script>
      let i3 = document.querySelector("i2");
      let o3 = document.querySelector("o2");
      o3.innerHTML = i3.value;
      i3.addEventListener(
        "input",
        function () {
          var xhr = new XMLHttpRequest();
          o3.innerHTML = i3.value;
          xhr.open("GET", "/b0?ex=" + i3.value, true);
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
              }

              else if (request->hasParam("hue"))
              {
                // Valor de error
                String hueS = request->getParam("hue")->value();
                hue = hueS.toInt();
                Serial.println(hue);
                request->send_P(200, "text/html", "bien bro");
              }

              else if (request->hasParam("sat"))
              {
                // Valor de error
                String satS = request->getParam("sat")->value();
                sat = satS.toInt();
                Serial.println(sat);
                request->send_P(200, "text/html", "bien bro");
              }

              else if (request->hasParam("ex"))
              {
                // Valor de error
                String exS = request->getParam("ex")->value();
                ex = exS.toInt();
                Serial.println(hue);
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
    light.waveIntensity(counter, hue);
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
    case 6:
    light.chaosAll(5,counter,40,100);
    break;
    case 7:
    light.busAll(5,counter,60,100);
    break;
  default:
    light.percentageAll(counter % 100, 50);
    break; // optional
  }
}
