#include "CommandInvoker.h"
#include <iostream>
//Svetoslav 9MI0600427


void CommandInvoker::run( SystemManager& manager) {
    String c_command;
    while (true) {
        readConsole(c_command);
        if (c_command == "stop") break;

        Command* command = Factory::getCommand(c_command);
        if (command == nullptr) {
            std::cerr << "Wrong command entered. Try a new one\n";
            if (std::cin.peek() != '\n' && std::cin.peek() != EOF) {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            std::cin.clear();
            continue;
        }
        command->execute(manager);
        delete command;
    }
}