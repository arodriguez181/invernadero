#ifndef Act_6_h
#define Act_6_h
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "RTClib.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ArduinoJson.h>
#include "PubSubClient.h"
#include <SD.h>
#include <SPI.h>
String jsone;
String sen_json;
String jsonString;
bool bomba;
bool foco;
String fecha;
String cisterna;

String act_fecha_bomba;
String act_fecha;
bool actua_on_bomba=true;
bool actua_off_bomba=true;

String act_fecha_foco_on;
String act_fecha_foco_off;
//String act_hora_foco;
bool actua_on_foco=true;
bool actua_off_foco=true;

bool json_foco_on=true;
bool json_foco_off=true;
bool foco_on_impreso = false;
bool foco_off_impreso = false;

bool json_bmb_on=true;
bool json_bmb_off=true;
bool bmb_on_impreso = false;
bool bmb_off_impreso = false;

bool json_foco_bmb_on=true;
bool json_foco_bmb_off=true;
bool foco_bmb_on_impreso = false;
bool foco_bmb_off_impreso = false;

String fecha_on_foco = "";
String fecha_off_foco = "";
String fecha_on_bomba = "";
String fecha_off_bomba = "";

#include "RTC.h"
  DS1307_RTC myrtc;

#include "Sensores.h"
  Sensores sans;

#include "MSD.h"
  MSD MSD;

#include "JSON.h"
  json_fac myjson;

#include "Actuadores.h"
  ActividadVI ACT;

#include "MQTT.h"
  MQTT mqtt;

#include "Tasks.h"
  millis_tasks TSK;

#endif