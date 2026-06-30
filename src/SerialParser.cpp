#include "SerialParser.h"

struct Command {
    uint8_t id;
    CommandFunction function;
};


Command commands[20];
int commandCount = 0;


SerialParser::SerialParser(){}


void SerialParser::addCommand(uint8_t id,CommandFunction function){
    if(commandCount<20){
        commands[commandCount].id = id;
        commands[commandCount].function = function;
        commandCount++;
    }
}
//[START][ID][SIZE][PAYLOAD...]
void SerialParser::eatByte(uint8_t incomingByte) {
    switch (state) {
        case 0: 
            if (incomingByte == 0x02) {
                index = 0;
                state = 1; 
            }
            break;

        case 1:             
            commandId = incomingByte;
            state = 2;
            break;

        case 2:
            payloadLength = incomingByte;
            
            if (payloadLength == 0) {
                this->parse(commandId, nullptr, 0);
                state = 0;
            } else if (payloadLength > 64) {
                state = 0; 
            } else {
                state = 3;
            }
            break;

        case 3:
            buffer[index] = incomingByte;
            index++;
            if (index == payloadLength) {
                this->parse(commandId, buffer, payloadLength);
                state = 0;
            }
            break;
    }
}

void SerialParser::parse(uint8_t cmdId, uint8_t* payload, uint8_t playloadLen) {
    for (int i = 0; i < commandCount; i++) {
        if (commands[i].id == cmdId) {
            commands[i].function(payload, playloadLen);
            return;
        }
    }
    // Mandar error: Comando no encontrado
}

