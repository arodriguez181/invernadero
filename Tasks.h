#ifndef Tasks_h
#define Tasks_h
/*****************************************************************************************
*      DESCRIPCIÓN DE LA LIBRERÍA: El objetivo de esta librería es generar tiempos de    *
*       espera de ejecución sin la implementación de la función "delay()".               *
******************************************************************************************/

#define TIEMPO_RTC 1000
#define M_JSON 5000
#define O_SENSORES 2000
#define SD_JSON 10000
#define TIEMPOMQTT  5000

class millis_tasks {

  public:
    uint64_t tiempo_anterior_lcd = 0,
             tiempo_anterior_m_json = 0,
             tiempo_anterior_sensores = 0,
             tiempo_anterior_sd_json = 0,
             tiempo_anterior_mqtt = 0,
             tiempo_actual = 0;
    
  public:
    void tarea_rtc (void);
    void actualizar_tareas (void);
    void mostrar_json (void);
    void sensores (void);
    void sd_json (void);
    void tarea_MQTT ( void );
};

/*~~~~~~~~~~~~~~~~~~~~~~~~ tarea1 - Función que se ejecuta cada TIEMPO1( 1 SEGUNDO) ~~~~~~~~~~~~~~~~~~~~~~~~ */
void millis_tasks :: tarea_rtc ( void ) {
  if ( ( tiempo_actual - tiempo_anterior_lcd ) >= TIEMPO_RTC ){
    //myjson.make_json();
    ACT.show_sensors();
    ACT.show_time();
    
    tiempo_anterior_lcd = tiempo_actual;
  }
}

void millis_tasks :: mostrar_json ( void ) {
  if ( ( tiempo_actual - tiempo_anterior_m_json ) >= M_JSON ){
    //Serial.println("Leyendo MicroSD...");
    //MSD.ReadFile();
    myjson.sans_json();
    tiempo_anterior_m_json = tiempo_actual;
  }
}

void millis_tasks :: sd_json ( void ) {
  if ( ( tiempo_actual - tiempo_anterior_sd_json ) >= SD_JSON ){
    Serial.println("Guardando en MicroSD...");
    MSD.SaveFile();
    tiempo_anterior_sd_json = tiempo_actual;
  }
}

void millis_tasks :: sensores ( void ) {
  if ( ( tiempo_actual - tiempo_anterior_sensores ) >= O_SENSORES ){
    sans.leer_dht();
    sans.leer_ldr();
    sans.leer_ultrasonico();
    myjson.sans_json();  //crea el json de sensores
    tiempo_anterior_sensores = tiempo_actual;
  }
}

void millis_tasks::tarea_MQTT(void) {
    if ((tiempo_actual - tiempo_anterior_mqtt) >= TIEMPOMQTT) {
        String ldr, foco, humedad, bomba_agua, s_ultrasonic, cisterna, hora, fecha,fecha_act_bomba,fecha_desact_bomba,fecha_act_foco,fecha_desact_foco;
        myjson.get_json_values(ldr, foco, humedad, bomba_agua, s_ultrasonic, cisterna, hora, fecha,fecha_act_bomba,fecha_desact_bomba,fecha_act_foco,fecha_desact_foco);
        mqtt.reconnect_MQTT();
        mqtt.publish_MQTT(sen_json);
        mqtt.publishValue("/LDR", ldr);
        mqtt.publishValue("/Foco", foco);
        mqtt.publishValue("/Humedad", humedad);
        mqtt.publishValue("/Bomba_agua", bomba_agua);
        mqtt.publishValue("/S_ultrasonic", s_ultrasonic);
        mqtt.publishValue("/Cisterna", cisterna);
        mqtt.publishValue("/Vista/Hora", hora);
        mqtt.publishValue("/Vista/Fecha", fecha);
        mqtt.publishValue("/Relay/Foco_hora_A", act_fecha_foco_on);
        mqtt.publishValue("/Relay/Foco_hora_D", fecha_desact_foco);
        mqtt.publishValue("/Relay/Bomba_hora_A", fecha_act_bomba);
        mqtt.publishValue("/Relay/Bomba_hora_D", fecha_desact_bomba);
        
        
        
        tiempo_anterior_mqtt = tiempo_actual;
    }
}


/*~~~~~~~~~~~~~~~~~~~~~~~~ actualizar_tareas - Función que actualiza el contador de "millis()" ~~~~~~~~~~~~~~~~~~~~~~~~ */
void millis_tasks :: actualizar_tareas ( void ) {
  tiempo_actual = millis( );
}

#endif