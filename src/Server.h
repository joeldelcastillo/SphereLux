#ifndef MainServer_H
#define MainServer_H

#include <Arduino.h>
#include "WiFi.h"
#include "ESPAsyncWebServer.h"

class MainServer
{

private:
  const char *ssid = "ESP32";
  const char *password = "123456789";
  const String severName1 = "http://192.168.4.1/counter";
  String serverName = "";
  float artistas[5][4] = {
      {0.0, 0.0, 0.0, 0.0},
      {0.0, 0.0, 0.0, 0.0},
      {0.0, 0.0, 0.0, 0.0},
      {0.0, 0.0, 0.0, 0.0},
      {0.0, 0.0, 0.0, 0.0}};

  int pin;

public:
  // Setup pin LED and call init()
  MainServer(String serverName)
  {
    this->serverName = serverName;
  }

  void setAccess()
  {
    // Setting the ESP as an access point
    Serial.print("Setting AP (Access Point)…");
    // Remove the password parameter, if you want the AP (Access Point) to be open
    WiFi.softAP(ssid, password);

    IPAddress IP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(IP);
  }

  float getArtista(int artista, int var)
  {
    return artistas[artista][var];
  }

  void printArtista(int artista)
  {
    Serial.print("Artista: ");
    Serial.print(artista);
    for (int j = 0; j < 3; j++)
    {
      Serial.print("    ");
      Serial.print(getArtista(artista, j));
    }
    Serial.println();
  }

  float printArtistas()
  {
    for (int i = 0; i < 5; i++)
    {
      Serial.print("Artista: ");
      Serial.print(i);
      for (int j = 0; j < 3; j++)
      {
        Serial.print("    ");
        Serial.print(getArtista(i, j));
      }
      Serial.println();
    }
    Serial.println();
  }
};

#endif
