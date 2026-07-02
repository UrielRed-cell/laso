#include "SerialParser.h"

namespace laso{

    SerialParser::SerialParser(){
        commandCount=0;
        index=0;
        payloadLength=0;
        state=0;
        commandId=0;
    }


    void SerialParser::addCommand(laso::u8bit id,CommandFunction function){
        if(commandCount<20){
            commands[commandCount].id = id;
            commands[commandCount].function = function;
            commandCount++;
        }
    }

    //[START][ID][SIZE][PAYLOAD...]
    void SerialParser::eatByte(laso::u8bit incomingByte) {
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

    void SerialParser::parse(laso::u8bit cmdId, laso::u8bit* payload, laso::u8bit playloadLen) {
        for (int i = 0; i < commandCount; i++) {
            if (commands[i].id == cmdId) {
                commands[i].function(payload, playloadLen);
                return;
            }
        }
        // Mandar error: Comando no encontrado
    }

}
