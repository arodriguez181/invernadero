#ifndef JSON.h
#define JSON.h


class json_fac {
  public:
    void make_json (void);
    void sans_json (void);
    String show_jsons (void);
    void get_json_values (String &,String &,String &,String &,String &,String &,String &,String &,String &,String &,String &,String &);
};

void json_fac :: make_json (void) {
  DynamicJsonDocument doc( 1024 );  
    myrtc.get_time();
    myrtc.nombre_F();  
    fecha=myrtc.fecha;
    myrtc.format_time();
    myrtc.format_date();   
    doc[ "Hora" ] = myrtc.tiempo;
    doc[ "Fecha" ] = myrtc.fecha;
 serializeJsonPretty(doc,jsone);
}

void json_fac :: sans_json (void) {
  DynamicJsonDocument sen(1024);
    myrtc.get_time();
    myrtc.nombre_F();  
    fecha=myrtc.fecha;
    myrtc.format_time();
    myrtc.format_date();   
    sen[ "Hora" ] = myrtc.tiempo;
    sen[ "Fecha" ] = myrtc.fecha;
    sen["LDR"] = sans.luminosidad;
    sen["Foco"] = sans.foco;
    if (json_foco_bmb_on) {
        if (act_fecha_foco_on.length() > 0 && !foco_bmb_on_impreso) {
            JsonObject foco_state = sen.createNestedObject("Actualizaciones_de_Foco");
            foco_state["Se_activo"] = act_fecha_foco_on;
           
            foco_bmb_on_impreso = true;
            foco_bmb_off_impreso = false;
            fecha_on_foco = act_fecha_foco_on;
            act_fecha_foco_on = "";
        }
        json_foco_bmb_on = false;
        json_foco_bmb_off = true;
    }
    if (json_foco_bmb_off) {
        if (act_fecha_foco_off.length() > 0 && !foco_bmb_off_impreso) {
            JsonObject foco_state = sen.createNestedObject("Actualizaciones_de_Foco");
            foco_state["Se_desactivo"] = act_fecha_foco_off;
           
            foco_bmb_off_impreso = true;
            foco_bmb_on_impreso = false;
            fecha_off_foco = act_fecha_foco_off;
            act_fecha_foco_off = "";
        }
        json_foco_bmb_off= false;
        json_foco_bmb_on = true;
    }
    sen["Humedad"] = sans.humedad;
    sen["Bomba_agua"] = sans.bombagua;
    if (json_foco_bmb_on) {
        if (act_fecha_bomba.length() > 0 && !foco_bmb_on_impreso) {
            JsonObject bmb_state = sen.createNestedObject("Actualizaciones_de_Bomba");
            bmb_state["Se_Activo"] = act_fecha_bomba;
            foco_bmb_on_impreso = true;
            foco_bmb_off_impreso = false;
            fecha_on_bomba = act_fecha_bomba;
            act_fecha_bomba = "";
        }
        json_foco_bmb_on = false;
        json_foco_bmb_off = true;
    }
    if (json_foco_bmb_off) {
        if (act_fecha.length() > 0 && !foco_bmb_off_impreso) {
            JsonObject bmb_state = sen.createNestedObject("Actualizaciones_de_Bomba");
            bmb_state["Se_Desactivo"] = act_fecha;
            foco_bmb_off_impreso = true;
            foco_bmb_on_impreso= false;
            fecha_off_bomba = act_fecha;
            act_fecha = "";
        }
       json_foco_bmb_off = false;
        json_foco_bmb_on = true;
    }
    sen["S_ultrasonic"] = sans.distancia;
    sen["Cisterna"] = cisterna;
  serializeJsonPretty(sen,sen_json);
  Serial.println(sen_json);
}




String json_fac :: show_jsons (void) {
  DynamicJsonDocument jun( 1024 );
    jun["LDR"] = sans.luminosidad;
    jun["Foco"] = sans.foco;
  //Cuando el foco esta encendido
    if(json_foco_on){
      
    if(act_fecha_foco_on.length()>0 && !foco_on_impreso ){
      JsonObject foco_state = jun.createNestedObject("Actualizaciones_de_Foco");
        foco_state["Se_activo"]=act_fecha_foco_on;
        foco_on_impreso=true;
        foco_off_impreso=false;
        act_fecha_foco_on="";
      
      }  
      json_foco_on=false;
      json_foco_off=true;
      
      }
//Cuando se apaga el foco
       if(json_foco_off){
        
        if(act_fecha_foco_off.length()>0 && !foco_off_impreso){
          JsonObject foco_state = jun.createNestedObject("Actualizaciones_de_Foco");
            foco_state["Se_desactivo"]=act_fecha_foco_off;
              foco_off_impreso=true;
              foco_on_impreso=false;
             act_fecha_foco_off="";
        }
        json_foco_off=false;
        json_foco_on=true;
      }
       // foco_state["Hora_de_desactivacion"]=act_fecha_foco_off;
  
    
    jun["Humedad"] = sans.humedad;
    
    jun["Bomba_agua"] = sans.bombagua;
    
    //Cuando se enciende la bomba
    if(json_bmb_on){

      if(act_fecha_bomba.length()>0 && !bmb_on_impreso){
        JsonObject bmb_state = jun.createNestedObject("Actualizaciones_de_Bomba");
          bmb_state["Se_Activo"]=act_fecha_bomba;
            bmb_on_impreso=true;
            bmb_off_impreso=false;
            act_fecha_bomba="";
      }
        json_bmb_on=false;
        json_bmb_off=true;
    }
    //Cuando se apaga la bomba
    if(json_bmb_off){

      if(act_fecha.length()>0 && !bmb_off_impreso){
        JsonObject bmb_state = jun.createNestedObject("Actualizaciones_de_Bomba");
        bmb_state["Se_Desactivo"]=act_fecha;
        bmb_off_impreso=true;
        bmb_on_impreso=false;
        act_fecha="";
      }
      json_bmb_off=false;
      json_bmb_on=true;
    }


    jun["S_ultrasonic"] = sans.distancia;
    jun["Cisterna"] = cisterna;
    JsonObject dato =  jun.createNestedObject("Vista");
      dato[ "Hora" ] = myrtc.tiempo;
      dato[ "Fecha" ] = myrtc.fecha;
  serializeJsonPretty(jun,jsonString);
  return jsonString;
}


void json_fac::get_json_values(String &ldr, String &foco, String &humedad, String &bomba_agua, String &s_ultrasonic, String &cisterna, String &hora, String &fecha, String &fecha_act_bomba, String &fecha_desact_bomba, String &fecha_act_foco, String &fecha_desact_foco) {
    ldr = String(sans.luminosidad);
    foco = sans.foco;
    humedad = String(sans.humedad);
    bomba_agua = sans.bombagua;
    s_ultrasonic = String(sans.distancia);
    cisterna = cisterna;
    hora = myrtc.tiempo;
    fecha = myrtc.fecha;

    if (json_bmb_on && fecha_on_bomba.length() > 0) {
        fecha_act_bomba = fecha_on_bomba;
    } else {
        fecha_act_bomba = "";
    }

    // Obtener fecha de desactivación de la bomba
    if (json_bmb_off && fecha_off_bomba.length() > 0) {
        fecha_desact_bomba = fecha_off_bomba;
    } else {
        fecha_desact_bomba = "";
    }

    // Obtener fecha de activación del foco
    if (json_foco_on && fecha_on_foco.length() > 0) {
        fecha_act_foco = fecha_on_foco;
    } else {
        fecha_act_foco = "";
    }

    // Obtener fecha de desactivación del foco
    if (json_foco_off && fecha_off_foco.length() > 0) {
        fecha_desact_foco = fecha_off_foco;
    } else {
        fecha_desact_foco = "";
    }
    fecha_off_foco = "";
    fecha_on_foco = "";
    fecha_off_bomba = "";
    fecha_on_bomba = "";
}
#endif