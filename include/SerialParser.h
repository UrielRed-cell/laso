#ifndef SERIALPARSER_H
#define SERIALPARSER_H


class SerialParser {

public:

    SerialParser();

    void begin();

    void addCommand(
        String name,
        void (*function)()
    );

    void parse(String input);

};

#endif
