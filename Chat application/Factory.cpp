#include "Factory.h"
#include "Command.h"

Command* Factory::getCommand(const String& command)
{
    if (command == "login")
        return new LoginCommand();
    else if (command == "create-account")
        return new RegisterCommand();
    else if (command == "view-chats")
        return new ViewChatsCommand();
    else if (command == "select-chat")
        return new SelectChatCommand();
    else if (command == "create-group")
        return new CreateGroupCommand();
    else if (command == "leave-group")
        return new LeaveGrupCommand();
    else if (command == "kick-from-group")
        return new KickFromGroupCommand();
    else if (command == "set-group-admin")
        return new SetGroupAdminCommand();
    else if (command == "group-stats")
        return new GroupStatsCommand();
    else if (command == "delete-user")
        return new DeleteUserCommand();
    else if (command == "delete-group")
        return new DeleteGroupCommand();
    else if (command == "make-admin")
        return new MakeAdminCommand();
    else if (command == "create-chat")
        return new CreateChatCommand();
    else if (command == "logout")
        return new LogoutCommand();
    else if (command == "view-all-chats")
        return new ViewAllChatsCommand();
    else if (command == "add-to-group")
        return new AddToGroupCommand();
    else return nullptr; 
}


