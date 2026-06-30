# laso es una plataforma para el control de mcu de manera simple y floja

## Objetivo

El objetivo de este programa es generar una comunicación  serial sencilla atraves de comandos los cuales referencian a funciones definidas por el usuario

## Uso

Para usar **laso** debes de primero agregar el encabezado a tu programa, despues defines tus funciones que quieras controlar por comandos seriales

``` 
#include "laso.h"

SerialParser router;

//argumentos del motor
struct ArgumentosMotor {
    uint8_t  idMotor;    
    uint16_t pasos;      
    float    velocidad;  
}; 

void fun(uint8_t* payload, uint8_t length) {
    if (length < sizeof(ArgumentosMotor)) return;

    ArgumentosMotor* args = (ArgumentosMotor*) payload;

    if (args->idMotor == 1) {
        moverMotor(args->pasos, args->velocidad);
    }
}

//PARA ARDUINO
void setup(){
    router.addCommand(0x01,&fun);    
}

void loop(){
    if(Serial.available()){
        router.eatByte(Serial.read())
    }
}
//PARA OTROS EJEMPLOS VER COMUNICACIÓN UART
```
Si usas **platformio** puedes incluir mi repo de la siguiente forma:

`lib_deps=https://github.com/UrielRed-cell/laso.git`

O si lo prefieres puedes descargar la libreria y compilarla:

`git clone https://github.com/UrielRed-cell/laso.git`
`g++ -Iinclude src/SerialParser.cpp main.cpp -o laso `

Tu archivo main.cpp es donde se incluira las librerias(ver ejemplo en tests).

## ¿Como funciona?
Funciona creando una tabla de comandos

CMD      FUNCIÓN

MOVER -> mover()

El sistema parser buscara la mejor coincidencia y ejecutara la función deseada, ademas utilizara una estructura de comandos especial
**Estructura de bits en serial**
_[START][CMDID][LENGTH][PAYLOAD]_
El primer bit recibido sera para indicar que escuche router, ese bit tendra un valor de 0x02, el siguiente es el id del comando que diste cuando llamaste a `router.addCommand()` el tercero es la cantidad de argumentos que recibira la función que escribiste y la última cadena de bytes es el valor de cada argumento de forma ordenada, como se indica en el ejemplo realizando un _cast_ entre una estructura que recibe los comandos y la carga útil se ahorran problemas de recepción de datos.

**Estar atento a posibles cambios de laso**
