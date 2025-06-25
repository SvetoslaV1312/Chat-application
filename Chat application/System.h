#pragma once
#include "ChatsRepo.h"
#include "UsersRepo.h"
#include "Container.hpp"
#include "Chat.h"
#include "User.h"

class System
{
public:
	void loadSystemFromBin();
	void writeSystemFromBin();
	void loadSystemFromTxt();
	void writeSystemFromTxt();
	const Container<Chat*>& getChats() const;
	Container<Chat*>& getChats();
	const Container<User*>& getUsers() const;
	Container<User*>& getUsers();
	void addUser(User* user);
	void addChat(Chat* email);
	User* findUserByUsername(const String& username);
	Chat* findChatById(size_t ownerId);
	void removeUserByUsername(const String& username);
	void removeChatById(size_t id);
	void removeMessagesFromUser(const String& username);
	User* getSystemUser();
	void setSession(User* other);
	bool usernameExists(const String& other);
	void removeChatFromUsers(size_t id);
	void printAllChats()const;

private:
	UsersRepo users;
	ChatsRepo chats;
	static User* session;
protected:

};

