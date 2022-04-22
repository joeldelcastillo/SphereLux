#include "Arduino.h"
#include "Server.h"
#include "Sphere.h"
#include "Helper.h"

// MainServer test(8);
Sphere light("Light");
Helper document("Helper");
MainServer accessPoint("accessPoint");
int counter = 0;
int anim = 0;
int hue = 0;
int sat = 0;
int val = 0;
int ex = 0;
int numAnim = 10;
int lastStationNum = 0;
bool isPrinted = false;
unsigned long previousMillis = 0;
const long interval = 300000;

AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
  <head>
    <title>Lux Sphere</title>
    <meta name="viewport" content="width=device-width, initial-scale=1" />
    <link rel="icon" href="data:," />
    <style>
      html {
        font-family: Arial;
        display: inline-block;
        text-align: center;
        padding: 10px;
      }
      h2 {
        font-size: 3rem;
      }
      p {
        font-size: 3rem;
      }
      body {
        margin: 0px auto;
        padding-bottom: 25px;
      }
      input[type="range"] {
        width: 80%;
        padding: 20px 0;
      }
    </style>
  </head>
  <body>
    <label for="i0">Hue</label>
    <div>
      <input type="range" id="i0" min="1" max="255" value="0" step="5" />
      <output id="o0"></output>
    </div>
    <label for="i1">Sat</label>
    <div>
      <input type="range" id="i1" min="1" max="100" value="0" step="5" />
      <output id="o1"></output>
    </div>
    <label for="i2">Val</label>
    <div>
      <input type="range" id="i2" min="1" max="100" value="0" step="5" />
      <output id="o2"></output>
    </div>
    <label for="i2">Ex</label>
    <div>
      <input type="range" id="i3" min="1" max="100" value="0" step="1" />
      <output id="o3"></output>
    </div>

    <br>

    <select id="comboA" onchange="getComboA(this)">
      <option value="">Animations</option>
      <option value="0">0</option>
      <option value="1">1</option>
      <option value="2">2</option>
      <option value="3">3</option>
      <option value="4">4</option>
      <option value="5">5</option>
      <option value="6">6</option>
      <option value="7">7</option>
      <option value="8">8</option>
      <option value="9">9</option>
    </select>

    <br>
    <br>

    <button onclick="heap()">Clear Heap</button>

    <br>
    <br>
    
    <button onclick="reset()">Reset</button>

    <script>
      let i0 = document.getElementById("i0");
      let o0 = document.getElementById("o0");
      o0.innerHTML = i0.value;
      i0.addEventListener(
        "change",

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
        "change",
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
        "change",
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
        "change",
        function () {
          var xhr = new XMLHttpRequest();
          o3.innerHTML = i3.value;
          xhr.open("GET", "/b3?ex=" + i3.value, true);
          xhr.send();
        },
        false
      );
    </script>

    <script>
      function getComboA(selectObject) {
        var value = selectObject.value;
        console.log(value);
        var xhr = new XMLHttpRequest();
        xhr.open("GET", "/ch?anim=" + value, true);
        xhr.send();
      }
    </script>

    <script>
      function heap() {
        var xhr = new XMLHttpRequest();
        alert("Estas seguro que quieres borrar el heap?")
          xhr.open("GET", "/heap", true);
          xhr.send();
        console.log("heap");
      }
    </script>

    <script>
      function reset() {
        var xhr = new XMLHttpRequest();
        alert("Estas seguro que quieres resetear?")
          xhr.open("GET", "/reset", true);
          xhr.send();
        console.log("reset");
      }
    </script>
  </body>
</html>
)rawliteral";

void onWsEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len)
{

  if (type == WS_EVT_CONNECT)
  {

    Serial.println("Websocket client connection received");
    client->text("Hello from ESP32 Server");
  }
  else if (type == WS_EVT_DISCONNECT)
  {
    Serial.println("Client disconnected");
  }
}

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

  server.on("/heap", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(200, "text/plain", String(ESP.getFreeHeap())); 
                Serial.println("Heap cleared"); });
  server.on("/reset", HTTP_GET, [](AsyncWebServerRequest *request)
            {
    request->send(200,"text/plain","ok");
    delay(1000);
    ESP.restart(); });
  // Start server

  ws.onEvent(onWsEvent);
  server.addHandler(&ws);
  server.begin();
}

void loop()
{

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval)
  {
    anim = (anim + 1) % numAnim;
    previousMillis = currentMillis;
    if (WiFi.softAPgetStationNum() == 0)
    {
      Serial.printf("Stations connected to soft-AP = %d\n", WiFi.softAPgetStationNum());
    }
  }

  counter++;
  switch (anim)
  {
  case 0:
    light.waveIntensity(counter, hue, ex);
    break; // optional
  case 1:
    light.percentageAll((counter * ex) % 100, hue);
    break; // optional
  case 2:
    light.simpleColor(hue);
    break; // optional
  case 3:
    light.danceFalf(counter * ex, 1, hue);
    //    light.percentageAll(counter%100,50);
    break; // optional
  case 4:
    light.danceFalf(counter * ex, 10, hue);
    // light.percentageAll(counter, 70);
    break; // optional
  case 5:
    light.partitionAll(counter * ex, 20, hue);
    break; // optional
  case 6:
    light.chaosAll(sat, counter * ex, hue, 100);
    break;
  case 7:
    light.busAll(sat, counter * ex, hue, 100);
    break;
  case 8:
    light.busAll(sat, -counter * ex, hue, 100);
    break;
  default:
    light.percentageAll((counter * ex) % 100, hue);
    break; // optional
  }
  if (WiFi.softAPgetStationNum() > 0 && isPrinted == false)
  {
    lastStationNum = WiFi.softAPgetStationNum();
    Serial.printf("Stations connected to soft-AP = %d\n", WiFi.softAPgetStationNum());
    isPrinted = true;
  }

  if (lastStationNum > WiFi.softAPgetStationNum() && isPrinted == true)
  {
    Serial.println("Station Disconected");
    isPrinted = false;
    ESP.getFreeHeap();
    ESP.restart();
  }
}
