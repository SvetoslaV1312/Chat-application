#pragma once
#include <iostream>
#include "String.h"
#include "Vector.hpp"


class User
{
public:
	User() = default;
	User(const String& username, const String& password);
	
	virtual void printTxt(std::ostream&)const;
	virtual void readTxt(std::istream&);
	bool operator==(const User& other) const;
	bool operator!=(const User& other) const;
	const Vector<size_t> getChats() const;
	virtual String getUsername() const;
	User(const User& other);
	friend bool isAdministrator(User* user);
	virtual User* clone()const;
	virtual ~User()=default; 
	bool checkPassword(const String& password);
	virtual void addChat(size_t chatId);
	virtual void removeChat(size_t id);
	virtual void printBin(std::ostream& os)const;
	virtual void readBin(std::istream& is);
private:
	
protected:
	String username;
	String password;
	Vector<size_t> chats;
};

class Admin :public User 
{
public:
	
	User* clone()const override;
	Admin() = default;
	Admin(const String& username, const String& password);
	Admin(const Admin& other);
	Admin(const User& other);
	void printTxt(std::ostream&)const override;
	void readTxt(std::istream&) override;
	static void printLastIdTxt(std::ostream&);
	static void loadLastIdTxt(std::istream&);
	static void printLattIdBin(std::ostream&);
	static void loadLastIDBin(std::istream&);
	void readBin(std::istream& is) override;
	virtual void printBin(std::ostream& os)const;


private:
	static size_t lastID;
	size_t id=0;
protected:

};

