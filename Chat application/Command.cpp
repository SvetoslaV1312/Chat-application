#include "Command.h"

#include "User.h"
#include "Chat.h"
#include <filesystem>



void LoginCommand::execute(SystemManager& manager)
{
	manager.loginUser();
}

void RegisterCommand::execute(SystemManager& manager)
{
	manager.registerUser();
}

void ViewChatsCommand::execute(SystemManager& manager)
{
	manager.instanceViewChat();
}

void SelectChatCommand::execute(SystemManager& manager)
{
	manager.selectChat();
}

void CreateGroupCommand::execute(SystemManager& manager)
{
	manager.createGroup();
}

void AddToGroupCommand::execute(SystemManager& manager)
{
	manager.addToGroup();
}

void LeaveGrupCommand::execute(SystemManager& manager)
{
	manager.leaveGroupUser();
}

void KickFromGroupCommand::execute(SystemManager& manager)
{
	manager.perfromKickFromGroup();
}

void SetGroupAdminCommand::execute(SystemManager& manager)
{
	manager.setAdminCommand();
}

void GroupStatsCommand::execute(SystemManager& manager)
{
	manager.displayGroupStats();
}

void DeleteUserCommand::execute(SystemManager& manager)
{
	manager.deleteUser();
}

void DeleteGroupCommand::execute(SystemManager& manager)
{
	manager.deleteGroup();
}

void ViewAllChatsCommand::execute(SystemManager& manager)
{
	manager.viewAllChats();
}

void MakeAdminCommand::execute(SystemManager& manager)
{
	manager.makeAdmin();
}

void CreateChatCommand::execute(SystemManager& manager)
{
	manager.createChat();
}

void LogoutCommand::execute(SystemManager& manager)
{
	manager.logoutSession();
}
