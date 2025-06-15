#pragma once
#include "Command.h"
#include "String.h"

class Factory {
public:
    static Command* getCommand(const String& command);
private:
protected:
};