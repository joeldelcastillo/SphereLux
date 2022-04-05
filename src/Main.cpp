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

// Direcciones de cada bailarin
// const char dir0[] = "/b0";
// const char dir1[] = "/b1";
// const char dir2[] = "/b2";

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
    body {max-width: 600px; margin:0px auto; padding-bottom: 25px;}
    .switch {position: relative; display: inline-block; width: 120px; height: 68px} 
    .switch input {display: none}
    .slider {position: absolute; top: 0; left: 0; right: 0; bottom: 0; background-color: #ccc; border-radius: 6px}
    .slider:before {position: absolute; content: ""; height: 52px; width: 52px; left: 8px; bottom: 8px; background-color: #fff; -webkit-transition: .4s; transition: .4s; border-radius: 3px}
    input:checked+.slider {background-color: #b30000}
    input:checked+.slider:before {-webkit-transform: translateX(52px); -ms-transform: translateX(52px); transform: translateX(52px)}
  </style>
</head>
<body>
  <h2>ESP Web Server</h2>
  <p>Audio settings:</p>

<div>
  <input type="range" id="volume" name="volume"
         min="0" max="11">
  <label for="volume">Volume</label>
</div>

<div>
  <input type="range" id="cowbell" name="cowbell" 
         min="0" max="100" value="90" step="10">
  <label for="cowbell">Cowbell</label>
</div>

<script>function toggleCheckbox(element) {
  var xhr = new XMLHttpRequest();
  if(element.checked){ xhr.open("GET", "/update?output="+element.id+"&state=1", true); }
  else { xhr.open("GET", "/update?output="+element.id+"&state=0", true); }
  xhr.send();
}
</script>
</body>
</html>
)rawliteral";

void setup()
{
  Serial.begin(115200);
  light.setPins();
  accessPoint.setAccess();
  server.on("/b0", HTTP_GET, [](AsyncWebServerRequest *request)
            {
      if (request->hasParam("anim"))
      {
        // Valor de error
        String animS = request->getParam("anim")->value();

        anim = animS.toInt();
        request->send_P(200, "text/html", index_html);
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
