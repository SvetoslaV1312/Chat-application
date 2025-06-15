#include "UsersRepo.h"

void UsersRepo::readUsersTxt()
{
	std::ifstream file("users.txt");
	if (!file.is_open()) {
		std::cerr << "Error: could not open Users.txt for reading.\n";
		return;
	}
	String temp;
	if (file >> temp) 
	{
		file.seekg(0);  // Reset to beginning
		Admin::loadLastIdTxt(file);
		users.readFromStream(file);
	}
}

void UsersRepo::writeUsersTxt()
{
	std::ofstream file("users.txt", std::ios::trunc);
	if (!file.is_open()) {
		std::cerr << "Error: could not open Users.txt for writing.\n";
		return;
	}
	Admin::printLastIdTxt(file);
	users.writeToStream(file);
}

void UsersRepo::readUsersBin()
{
	std::ifstream file("users.bin", std::ios::binary);
	if (!file.is_open()) {
		std::cerr << "Error: could not open Users.bin for reading.\n";
		return;
	}
	String temp;
	if (file >> temp)
	{
		file.seekg(0);  // Reset to beginning
		Admin::loadLastIDBin(file);
		users.readFromStreamBin(file);
	}
}

void UsersRepo::writeUsersBin()
{
	std::ofstream file("users.bin", std::ios::binary | std::ios::trunc);
	if (!file.is_open()) {
		std::cerr << "Error: could not open Users.bin for writing.\n";
		return;
	}
	Admin::printLattIdBin(file);
	users.writeToStreamBin(file);
}

Container<User*>& UsersRepo::getUsers()
{
	return users;
}

const Container<User*> UsersRepo::getUsers() const
{
	return users;
}

void UsersRepo::addUser(User* user)
{
	users.push_back(user);
}

size_t UsersRepo::getSize() const
{
	return users.getSize();
}

User* UsersRepo::operator[](size_t index)
{
	return users[index];
}

void UsersRepo::remove(size_t idx)
{
	users.remove(idx);
}

