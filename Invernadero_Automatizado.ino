 #include "Act_6.h"


void setup() {
  Serial.begin(115200);
  myrtc.RTC_init ();
  sans.sensors_init();
  MSD.MicroSD_init();
  ACT.lcd_init ();
  ACT.oled_init();
  mqtt.setup_WiFi ();
  mqtt.set_MQTT_server ();
  mqtt.set_MQTT_callback ();
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
   
}

void loop() {
  // put your main code here, to run repeatedly:
  //myrtc.get_time();
  //myrtc.show_time();
  TSK.actualizar_tareas();
  TSK.tarea_rtc();
  TSK.mostrar_json();
  TSK.sensores();
  TSK.sd_json();
  TSK.tarea_MQTT();
  delay(1000); // this speeds up the simulation
}
