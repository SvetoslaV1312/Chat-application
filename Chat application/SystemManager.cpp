#include "SystemManager.h"
int choice=1;

SystemManager::SystemManager(System& system)
	:system(system)
{
	std::cout << "Press 1 for txt reading and writing or 2 for binary reading and writing.\n";
	std::cin >> choice;
	switch (choice)
	{
	case 1:
		system.loadSystemFromTxt();
		break;
	case 2:
		system.loadSystemFromBin();
		break;
	default:
		break;
	}
}

SystemManager::~SystemManager()
{
	switch (choice)
	{
	case 1:
		system.writeSystemFromTxt();
		break;
	case 2:
		system.writeSystemFromBin();
		break;
	default:
		break;
	}
}

void SystemManager::loginUser()
{
	if (system.getInstance())
	{
		std::cerr << "You are logged in already.\n";
		return;
	}
	String username, password;
	readConsole(username);
	readConsole(password);
	size_t numberUsers = system.getUsers().getSize();
	for (size_t i = 0; i < numberUsers; i++)
	{
		if (system.getUsers()[i]->getUsername() == username && system.getUsers()[i]->checkPassword(password)) {
			system.setSession(system.getUsers()[i]);
			std::cout << "You have been logged in.\n";
			return;
		}
		else if (system.getUsers()[i]->getUsername() == username && !system.getUsers()[i]->checkPassword(password))
		{
			std::cout << "Passowrd for this user doesnt match" << std::endl;
			return;
		}
	}
	std::cerr << "User not found.\n";
}

void SystemManager::registerUser()
{
	if (system.getInstance())
	{
		std::cerr << "You are logged in another account.\n";
		return;
	}
	String username, password;
	readConsole(username);
	readConsole(password);
	size_t numberUsers = system.getUsers().getSize();
	if (numberUsers == 0)
	{
		system.setSession(new Admin(username, password));
		system.addUser(system.getInstance());
		std::cout << "You have been added as admin as you are the first user.\n";
		return;
	}
	for (size_t i = 0; i < numberUsers; i++)
	{
		if (system.getUsers()[i]->getUsername() == username) {
			std::cout << "Username already exists command terminated.\n";
			return;
		}
	}
	system.setSession(new User(username, password));
	system.addUser(system.getInstance());
	std::cout << "You have been added.\n";
}
void SystemManager::makeAdmin() {
	Admin* a = dynamic_cast<Admin*>(system.getInstance());
	if (!a)
	{
		std::cerr << "only admin can perfrom this function.\n";
		return;
	}
	String username;
	std::cout << "Enter the username to promote to admin: ";
	readConsole(username);

	size_t userCount = system.getUsers().getSize();

	for (size_t i = 0; i < userCount; ++i) {
		if (system.getUsers()[i]->getUsername() == username)
		{
			Admin* newAdmin = new Admin(*(system.getUsers()[i])); //wrong setting in here
			system.getUsers().remove(i);                   
			system.getUsers().push_back(newAdmin);        

			std::cout << "User " << username << " promoted to admin.\n";
			return;
		}
	}

	std::cout << "User not found.\n";
}

void SystemManager::createChat()
{
	String username;
	std::cout << "Please enter the username to add to chat.\n";
	readConsole(username);
	User* reciever= system.findUserByUsername(username);
	if (reciever)
	{
		Individual i(system.getInstance()->getUsername(), reciever->getUsername());
		reciever->addChat(i.getID());
		system.getInstance()->addChat(i.getID());
		system.addChat(i.clone());
		std::cout << "The chat has been created with id " << i.getID() <<std::endl;
		return;
	}
	std::cerr<< "The chat not has been created user not found.\n";
		
}

void SystemManager::instanceViewChat()
{
	size_t chatId;
	std::cout << "Enter the chat id to view: ";
	if (!(std::cin >> chatId)) {
		std::cerr << "Wrong input, command terminated.\n";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return;
	}	Chat* c=system.findChatById(chatId);
	c->printMessages(system.getInstance()->getUsername());
}

void SystemManager::selectChat()
{
	size_t chatId;
	std::cout << "Please enter the chat id.\n";
	if (!(std::cin >> chatId)) {
		std::cerr << "Wrong input, command terminated.\n";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return;
	}	Chat* c = system.findChatById(chatId);
	c->sendMessage(system.getInstance()->getUsername());
}

void SystemManager::createGroup() {
	String groupName;
	Vector<String> usernames;
	bool needsApproval;
	String creator= system.getInstance()->getUsername();
	usernames.push_back(creator);
	std::cout << "Enter group name: ";	
	readConsole(groupName);
	std::cout << "Enter usernames to add to the group (type 'done' to finish):\n";
	String currentUsername;

	while (true) {
		readConsole(currentUsername);
		if (currentUsername == "done") break;

		if (!system.usernameExists(currentUsername)) {
			std::cerr << "User does not exist. Try again.\n";
		}
		else {
			usernames.push_back(currentUsername);
		}
	}

	std::cout << "Should new members require admin approval? (0 = no, 1 = yes): ";
	std::cin >> needsApproval;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear rest of line

	Group g(groupName, usernames, needsApproval);
	size_t id = g.getID();
	for (size_t i = 0; i < usernames.getSize(); i++)
	{
		system.findUserByUsername(usernames[i])->addChat(id);
	}
	std::cout << "Group '" << groupName << "' created successfully with id "<<id<<"\n";
	system.addChat(&g);
}

void SystemManager::addToGroup()
{
	size_t id;
	std::cout << "Enter the id of the group you want to add the person to.\n";
	if (!(std::cin >> id)) {
		std::cerr << "Wrong input, command terminated.\n";
		std::cin.clear(); 
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return;
	}

	String username;
	std::cout << "Enter the username of the user you want to add the to group.\n";
	readConsole(username);
	Group* g = dynamic_cast<Group*>(system.findChatById(id));
	if (!g)
	{
		std::cout << "Wrong id.\n";
		return;
	}
	if (!system.findUserByUsername(username))
	{
		std::cout << "Wrong username.\n";
		return;
	}
	if ((g->needApproval() && g->userIsAdmin(system.getInstance()->getUsername())))
	{
		g->perfromAdd(username);
	}
	else if (!g->needApproval() && g->hasUser(system.getInstance()->getUsername()))
	{
		g->perfromAdd(username);
	}
	else if (g->hasUser(system.getInstance()->getUsername()))
	{
		std::cout << "Notify the admins to add the person to the group.\n";
		g->sendMessage(system.getInstance()->getUsername());
	}
	else std::cerr << "You are not allowed to add people to the group.\n";
}

void SystemManager::leaveGroupUser()
{
	size_t id;
	std::cout << "Enter the group id you want to exit: ";
	if (!(std::cin >> id)) {
		std::cerr << "Wrong input, command terminated.\n";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return;
	}	Group* g = dynamic_cast<Group*>(system.findChatById(id));
	if (!g)
	{
		std::cout << "Wrong id.\n";
		return;
	}
	g->leaveGroup(system.getInstance()->getUsername());

}

void SystemManager::perfromKickFromGroup()
{
	size_t id;
	std::cout << "Enter the id of the group you want to remove person from.\n";
	if (!(std::cin >> id)) {
		std::cerr << "Wrong input, command terminated.\n";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return;
	}
	String username;
	std::cout << "Enter the username of the user you want to remove.\n";
	readConsole(username);
	Group* g = dynamic_cast<Group*>(system.findChatById(id));
	if (!g)
	{
		std::cout << "Wrong id.\n";
		return;
	}
	if (!system.findUserByUsername(username))
	{
		std::cout << "Wrong username.\n";
		return;
	}
	if (g->userIsAdmin(system.getInstance()->getUsername()) && g->hasUser(system.getInstance()->getUsername()))
	{
		g->removeUserFromGroup(username);
	}
	else
		std::cerr << "You are not part of the group.\n";
}

void SystemManager::setAdminCommand()
{
	size_t id;
	std::cout << "Enter the id of the group you want to make admin person.\n";
	if (!(std::cin >> id)) {
		std::cerr << "Wrong input, command terminated.\n";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return;
	}	String username;
	std::cout << "Enter the username of the user you want to make admin the to group.\n";
	readConsole(username);
	Group* g = dynamic_cast<Group*>(system.findChatById(id));
	if (!g)
	{
		std::cout << "Wrong id of group.\n";
		return;
	}
	if (!system.findUserByUsername(username))
	{
		std::cout << "Wrong username.\n";
		return;
	}
	if ( g->userIsAdmin(system.getInstance()->getUsername())&& g->hasUser(system.getInstance()->getUsername()))
	{
		g->makeAdmin(username);
		std::cout << "Successfully made admin of group.\n";
	}
	else std::cerr << "User is not Admin of the group.\n";
}

void SystemManager::displayGroupStats()
{
	size_t id;
	std::cout << "Enter the id of the group you want to see stats.\n";
	if (!(std::cin >> id)) {
		std::cerr << "Wrong input, command terminated.\n";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return;
	}	Group* g = dynamic_cast<Group*>(system.findChatById(id));
	if (!g)
	{
		std::cout << "Wrong id.\n";
		return;
	}
	g->displayStats();
}

void SystemManager::deleteGroup(){

	Admin* a = dynamic_cast<Admin*>(system.getInstance());
	if (a)
	{
		size_t id;
		std::cout << "Enter the id of the group you want to delete.\n";
		if (!(std::cin >> id)) {
			std::cerr << "Wrong input, command terminated.\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			return;
		}		system.removeChatById(id);
		system.removeChatFromUsers(id);
		return;
	}
	std::cerr << "This commamd can only be perfromed by admins.\n";

}

void SystemManager::viewAllChats()
{
	Admin* a = dynamic_cast<Admin*>(system.getInstance());
	if (a)
	{
		system.printAllChats();
		return;
	}
	std::cerr << "This commamd can only be perfromed by admins.\n";
}

void SystemManager::logoutSession()
{
	if (!system.getInstance())
	{
		std::cerr << "You are not logged in can't perfrom.\n";
		return;
	}
	system.setSession(nullptr);
	std::cout << "You have beeen logged out.\n";
}

void SystemManager::deleteUser()
{
	Admin* a = dynamic_cast<Admin*>(system.getInstance());
	if (a)
	{
		String username;
		std::cout << "Enter the username of the user you want to be deleted: ";
		readConsole(username);
		system.removeUserByUsername(username);
		system.removeMessagesFromUser(username);
		return;
	}
	std::cerr << "This commamd can only be perfromed by admins.\n";
}



