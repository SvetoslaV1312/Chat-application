#include "App.h"
#include "Factory.h"
//Svetoslav 9MI0600427
#include "CommandInvoker.h"

System App::system;
SystemManager App::manager(system);


void App::run() {
    
    CommandInvoker invoke;

    invoke.run( App::manager);
}
