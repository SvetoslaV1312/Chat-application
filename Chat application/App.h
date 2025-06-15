#pragma once
#include "User.h"
#include "SystemManager.h"
#include "system.h"
class Factory;

class App {
public:
    void run();
private:
protected:
   static SystemManager manager;
   static System system;
};