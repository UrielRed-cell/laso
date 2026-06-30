#ifndef SERIALPARSER_H
#define SERIALPARSER_H
#include <cstdint>

typedef void (*CommandFunction)(uint8_t* payload,uint8_t length);

class SerialParser {

private:

    uint8_t buffer[64];
    uint8_t index=0;
    uint8_t payloadLength=0;
    uint8_t state=0;
    uint8_t commandId=0;

public:

    SerialParser();
    void begin();
    void addCommand(uint8_t id,CommandFunction fun);
    void parse(uint8_t cmdId,uint8_t* payload,uint8_t payloadLen);
    void eatByte(uint8_t incomingByte); 
};

#endif
