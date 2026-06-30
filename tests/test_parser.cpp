#include "laso.h"
#include <iostream>
//Para compilar y ejecutar
//g++ -Iinclude src/SerialParser.cpp tests/test_parser.cpp -o laso 
//./laso

void sumar(uint8_t* payload, uint8_t len){
    std::cout << "Comando sumar recibido\n";
}


int main(){
    SerialParser router;

    router.addCommand(1, sumar);

    uint8_t paquete[] ={
        0x02, // inicio
        0x01, // comando
        0x00  // tamaño
    };


    for(uint8_t byte : paquete){
        router.eatByte(byte);
    }

    return 0;
}
