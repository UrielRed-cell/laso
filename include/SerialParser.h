#ifndef SERIALPARSER_H
#define SERIALPARSER_H
#include "types.h"

typedef void (*CommandFunction)(uint8_t* payload,uint8_t length);

class SerialParser {

private:

    laso::u8bit buffer[64];
    laso::u8bit index=0;
    laso::u8bit payloadLength=0;
    laso::u8bit state=0;
    laso::u8bit commandId=0;

public:

    SerialParser();
    void begin();
    void addCommand(laso::u8bit id,CommandFunction fun);
    void parse(laso::u8bit cmdId,laso::u8bit* payload,laso::u8bit payloadLen);
    void eatByte(laso::u8bit incomingByte); 
};

#endif
