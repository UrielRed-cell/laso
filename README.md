# laso es una plataforma para el control de mcu de manera simple y floja

## Objetivo

El objetivo de este programa es generar una comunicación  serial sencilla atraves de comandos los cuales referencian a funcionesdefinidas por el usuario

## Uso

Para usar **laso** debes de primero agregar el encabezado a tu programa, despues defines tus funciones que quieras controlar por comandos seriales

``` 
#include<SerialParser.h>

SerialParser router;

void fun(){
    //HAZ COSAS
}
//PARA ARDUINO
void setup(){
    router.addCommand("fun",fun);    
}

void loop(){
    if(Serial.available()){
        String command=Serial.readStringUntil('\n');
        router.parse(command);
    }
}

```
### ¿Como funciona?
Funciona creando una tabla de comandos

CMD      FUNCIÓN

MOVER -> mover()

El sistema parser buscara la mejor coincidencia y ejecutara la función deseada


