#include "SerialParser.h"


struct Command {
    String name;
    void (*function)();
};


Command commands[20];
int commandCount = 0;


SerialParser::SerialParser(){

}


void SerialParser::addCommand(
    String name,
    void (*function)()
){

    commands[commandCount].name = name;
    commands[commandCount].function = function;
    commandCount++;

}



void SerialParser::parse(String input){

    input.trim();
    input.toUpperCase();


    for(int i=0;i<commandCount;i++){

        if(commands[i].name == input){

            commands[i].function();
            return;

        }

    }

}
