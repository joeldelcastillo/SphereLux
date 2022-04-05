#ifndef Helper_H
#define Helper_H

#include <Arduino.h>

class Helper
{

private:
    String name;

public:
    Helper(String name)
    {
        this->name = name;
    }
};

#endif
