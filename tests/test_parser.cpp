#include "laso.h"
#include <iostream>
//Para compilar y ejecutar
//g++ -Iinclude src/SerialParser.cpp tests/test_parser.cpp -o laso 
//./laso

void sumar(laso::u8bit* payload, laso::u8bit len){
    std::cout << "Comando sumar recibido\n";
}


int main(){
    laso::SerialParser router;

    router.addCommand(1, sumar);

    laso::u8bit paquete[] ={
        0x02, // inicio
        0x01, // comando
        0x00  // tamaño
    };


    for(laso::u8bit byte : paquete){
        router.eatByte(byte);
    }

    return 0;
}
