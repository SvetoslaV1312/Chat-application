#pragma once
#include "Container.hpp"
#include "chat.h"
class ChatsRepo
{
public:
	friend std::ostream& operator <<(std::ostream& os, const Container<Chat* >& chats);
	friend std::istream& operator >>(std::istream& os, Container<Chat* >& chats);
	void readChatsTxt();
	void writeChatsTxt();
	void readChatsBin();
	void writeChatsBin();
	Container<Chat*>& getChats();
	const Container<Chat*>& getChats()const;
	void addChat(Chat* chat);
	size_t getSize()const;
	Chat* operator [](size_t index);
	void remove(size_t idx);

private:
	Container<Chat*> chats;
};

