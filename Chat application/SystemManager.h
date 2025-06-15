#pragma once
#include "system.h"

class SystemManager
{
public:
	SystemManager() = default;
	SystemManager(System& system);
	~SystemManager();
	void loginUser();
	void registerUser();
	void makeAdmin();
	void createChat();
	void instanceViewChat();
	void selectChat();
	void createGroup();
	void addToGroup();
	void leaveGroupUser();
	void perfromKickFromGroup();
	void setAdminCommand();
	void displayGroupStats();
	void deleteUser();
	void deleteGroup();
	void viewAllChats();
	void logoutSession();
private:
	System& system;
};

