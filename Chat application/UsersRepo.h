#pragma once
#include "Container.hpp"
#include "user.h"
#include <fstream>
class UsersRepo
{
public:
	friend std::ostream& operator <<(std::ostream& os, const Container<User* >& users);
	friend std::istream& operator >>(std::istream& os, Container<User* >& users);
	void readUsersTxt();
	void writeUsersTxt();
	void readUsersBin();
	void writeUsersBin();
	Container<User*>& getUsers();
	const Container<User*> getUsers() const;
	void addUser(User* user);
	size_t getSize()const;
	User* operator [](size_t index);
	void remove(size_t idx);
private:
	Container<User*> users;
};

