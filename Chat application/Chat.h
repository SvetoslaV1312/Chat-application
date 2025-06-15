#pragma once
#include "Message.h"
#include "User.h"
#include "Vector.hpp"
#include "String.h"

class Chat
{
public:
	virtual void seeAndSendMessage(const String& sender) =0;
	virtual ~Chat()=default;
	virtual String getName(const String& caller)=0;
	void printMessages(const String& sender)const;
	String displaySender(const String& other, const String& sender) const;
	void pushMessage(const Message& message);
	void sendMessage(const String& sender);
	virtual void handleMessages(std::istream& fs);
	virtual void handleMessagesBin(std::istream& fs);
	virtual void del(const String& user)=0;
	size_t getStaticId()const;
	virtual void displayStats()const =0;
	virtual size_t getID()const;
	virtual void readBin(std::istream& is)=0;

	virtual void printTxt(std::ostream& os) const = 0;
	virtual Chat* clone() const = 0;
	static void printLastIdTxt(std::ostream&);
	static void loadLastIdTxt(std::istream&);
	static void printLastIdBin(std::ostream&);
	static void loadLastIdBin(std::istream&);
	virtual void printBin(std::ostream&) const = 0;

private:
protected:
	static size_t lastId;
	size_t id;
	Vector<Message> messages;

};


class Individual : public Chat 
{
public:
	Individual() = default;
	Individual(std::ifstream& fs);
	virtual String getName(const String& caller) override;
	virtual void seeAndSendMessage(const String& sender) override;
	virtual ~Individual() override = default;
	virtual void del(const String& user) override;
	void displayStats()const override;
	void printTxt(std::ostream& os)const override;
	Chat* clone()const override;
	Individual(const String& username1, const String& username2);
	void readBin(std::istream& is) override;
	virtual void printBin(std::ostream&) const override;
private:

protected:
	String users[2];
};

class Group : public Chat
{
public:
	Group() = default;
	Group(std::ifstream& fs);
	virtual void seeAndSendMessage(const String& sender)override;
	virtual ~Group() override = default;
	Group(const String& name, Vector<String> usernames, bool needsApproval);
	void addToGroup(const String& user);
	void leaveGroup(const String& user);
	bool userIsAdmin(const String& user)const;
	void removeUserFromGroup(const String& user);
	void makeAdmin(const String& user);
	void displayStats()const override;
	virtual String getName(const String& caller) override;
	virtual void del(const String& user) override;
	bool needApproval()const;
	void printTxt(std::ostream& os)const override;
	Chat* clone()const override;
	bool hasUser(const String& user)const;
	void perfromAdd(String& username);
	void readBin(std::istream& is) override;
	virtual void printBin(std::ostream&) const override;
private:
	
protected:
	size_t membersCount = 0;
	Vector<String> users;
	Vector<String> admins;
	String name;
	bool needsApproval = false;
};

