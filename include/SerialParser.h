#ifndef SERIALPARSER_H
#define SERIALPARSER_H
#include "types.h"


namespace laso{

    using CommandFunction = void (*)(laso::u8bit* payload, laso::u8bit length);

    struct Command {
        laso::u8bit id;
        CommandFunction function;
    };

    class SerialParser {

    private:
        
        Command commands[20];
        laso::u8bit commandCount;
        laso::u8bit buffer[64];
        laso::u8bit index;
        laso::u8bit payloadLength;
        laso::u8bit state;
        laso::u8bit commandId;

    public:

        SerialParser();
        void begin();
        void addCommand(laso::u8bit id,CommandFunction fun);
        void parse(laso::u8bit cmdId,laso::u8bit* payload,laso::u8bit payloadLen);
        void eatByte(laso::u8bit incomingByte); 
    };
}
#endif
