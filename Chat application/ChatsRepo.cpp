#include "ChatsRepo.h"

void ChatsRepo::readChatsTxt()
{
	std::ifstream file("Chats.txt");
	if (!file.is_open()) {
		std::cerr << "Error: could not open Chats.txt for reading.\n";
		return;
	}
	String temp;
	if (file >> temp)
	{
		file.seekg(0);  // Reset to beginning
		Chat::loadLastIdTxt(file);
		chats.readFromStream(file);
	}
	
}


void ChatsRepo::writeChatsTxt()
{
	std::ofstream file("Chats.txt", std::ios::out | std::ios::trunc);
	if (!file.is_open()) {
		std::cerr << "Error: could not open Chats.txt for writing.\n";
		return;
	}

	Chat::printLastIdTxt(file);
	chats.writeToStream(file);
}


void ChatsRepo::readChatsBin()
{
	std::ifstream file("Chats.bin", std::ios::binary);
	if (!file.is_open()) {
		std::cerr << "Error: could not open Chats.bin for reading.\n";
		return;
	}


	String temp;
	if (file >> temp)
	{
		file.seekg(0);  // Reset to beginning
		Chat::loadLastIdBin(file);
		chats.readFromStreamBin(file);
	}
	
}

void ChatsRepo::writeChatsBin()
{
	std::ofstream file("Chats.bin", std::ios::binary | std::ios::trunc);
	if (!file.is_open()) {
		std::cerr << "Error: could not open Chats.bin for writing.\n";
		return;
	}

	Chat::printLastIdBin(file);
	chats.writeToStreamBin(file);
}

Container<Chat*>& ChatsRepo::getChats()
{
	return chats;
}

const Container<Chat*>& ChatsRepo::getChats() const
{
	return chats;
}

void ChatsRepo::addChat(Chat* chat)
{
	chats.push_back(chat);
}

size_t ChatsRepo::getSize() const
{
	return chats.getSize();
}

Chat* ChatsRepo::operator[](size_t index)
{
	return chats[index];
}

void ChatsRepo::remove(size_t idx)
{
	chats.remove(idx);
}
