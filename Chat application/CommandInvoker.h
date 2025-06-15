#pragma once
//Svetoslav 9MI0600427

#include "Command.h"
#include "Factory.h"
#include "String.h"

class CommandInvoker {
public:
    void run(SystemManager& manager);
};