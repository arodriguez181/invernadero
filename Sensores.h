 #ifndef Sensores_h
#define Sensores_h



#define HUMEDAD_PIN 33
#define TRIGGER_PIN 16 // Pin digital al que está conectado el disparador del sensor HC-SR04
#define ECHO_PIN 35    // Pin digital al que está conectado el eco del sensor HC-SR04
#define RELAY_FOCO 15  //Pin digital al que está conecta el relay enfocado al foco
#define RELAY_BAGUA 14 //Pin digital al que esta conectado el relay enfocado a la bomba de agua
#define LDR_PIN 34     // Pin analógico al que está conectado el sensor LDR


class Sensores {
  
  public:
    float humedad = 0.0;
    int distancia = 0;
    int luminosidad = 0;
    float percentage; 
    String foco = "", bombagua = "";
      
  public:
    void sensors_init();
    void leer_dht();
    void leer_ldr();
    void leer_ultrasonico();

  };


void Sensores::sensors_init() {
    //dht.begin();
    Serial.println("Sensor DHT22 inicializado");
    pinMode(TRIGGER_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    pinMode(RELAY_FOCO, OUTPUT);
    pinMode(RELAY_BAGUA, OUTPUT);
    pinMode(HUMEDAD_PIN, INPUT);
    pinMode(LDR_PIN,INPUT);
    digitalWrite(RELAY_FOCO,LOW);
    digitalWrite(RELAY_BAGUA,LOW);
    Serial.println("Sensor HC-SR04 inicializado");
    Serial.println("Sensor LDR inicializado");
}


void Sensores::leer_dht() {
  bombagua = "";
  humedad = map(analogRead(HUMEDAD_PIN),4095, 0, 0,100);
  /*Serial.print("Humedad: ");
  Serial.print(hum);
  Serial.println(" %");*/
  
  if(humedad < 55){
    digitalWrite(RELAY_BAGUA, HIGH);
    bombagua = "Activada";
    if(actua_on_bomba){
      actua_on_bomba=false;
    myrtc.get_time();
    myrtc.format_time();
    act_fecha_bomba=myrtc.tiempo;
      actua_off_bomba=true;
    }
    /*Serial.print("Bomba: ");
    Serial.println(bombagua);*/
  } else  if(humedad >= 55){
    

    digitalWrite(RELAY_BAGUA, LOW);
    bombagua = "Desactivada";
    if(actua_off_bomba){
      actua_off_bomba=false;
      myrtc.get_time();
      myrtc.format_time();
      act_fecha=myrtc.tiempo;
      actua_on_bomba=true;
    }


    /*Serial.print("Bomba: ");
    Serial.println(bombagua);*/
  } //para quien lo leea, esto lo dejo así para hacer los json's

}


void Sensores::leer_ldr() {
    foco="";
    luminosidad = analogRead(LDR_PIN);
    luminosidad = map(luminosidad, 0, 4095, 0,100);
    /*Serial.println("LDR");
    Serial.println(luminosidad);*/

    if(luminosidad >= 90 && luminosidad <=100){
      digitalWrite(RELAY_FOCO,LOW);
      foco = "Encendido";
      if(actua_on_foco){
        actua_on_foco=false;
        myrtc.get_time();
        myrtc.format_time();
        act_fecha_foco_on=myrtc.tiempo;
        actua_off_foco=true;
      }
      /*Serial.print("Foco: ");
      Serial.println(foco);*/
    } else if(luminosidad <90) {
      digitalWrite(RELAY_FOCO,HIGH);
      foco = "Apagado";
      if(actua_off_foco){
        actua_off_foco=false;
        myrtc.get_time();
        myrtc.format_time();
        act_fecha_foco_off=myrtc.tiempo;
        actua_on_foco=true;
      }
      /*Serial.print("Foco: ");
      Serial.println(foco);*/
    } //para quien lo leea, esto lo dejo así para hacer los json's
}

void Sensores::leer_ultrasonico() {
    cisterna = "";
    // Lectura del sensor HC-SR04
    digitalWrite(TRIGGER_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIGGER_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIGGER_PIN, LOW);

    long duracion = pulseIn(ECHO_PIN, HIGH);
    distancia = duracion * 0.034 / 2;
    //distancia = map(distancia, 4, 11, 100, 0);
    percentage = map( distancia, 4, 11, 100, 0);
    percentage = constrain(percentage, 0, 100); 

    cisterna= String(percentage) + "% LLENA";
    /*Serial.println("Ultrasonico");
    Serial.println(distancia);*/

    /*if(percentage == 10){
      cisterna = "10% llena";
      
    }
    if(distancia == 35){
      cisterna = "35% llena";
    
    }
    if(distancia <= 3.30){
      cisterna = "100% llena";
      
    }
    if(distancia > 8.70){
      cisterna = "Menos del 50% llena";
    
    }*/
}

#endif