#include "System.h"

User* System::session = nullptr;


void System::loadSystemFromBin()
{
    users.readUsersBin();
    chats.readChatsBin();
}

void System::writeSystemFromBin()
{
    users.writeUsersBin();
    chats.writeChatsBin();
}

void System::loadSystemFromTxt()
{
    users.readUsersTxt();
    chats.readChatsTxt();
}

void System::writeSystemFromTxt()
{
    users.writeUsersTxt();
    chats.writeChatsTxt();
}

const Container<Chat*>& System::getChats() const
{
    return  chats.getChats();
}

Container<Chat*>& System::getChats()
{
    return chats.getChats();
}

const Container<User*>& System::getUsers() const
{
    return users.getUsers();
}

Container<User*>& System::getUsers()
{
    return users.getUsers();
}

void System::addUser(User* user)
{
    users.addUser(user);
}

void System::addChat(Chat* chat)
{
    return  chats.addChat(chat);
}

User* System::findUserByUsername(const String& username)
{
    for (size_t i = 0; i < users.getSize(); ++i) {
        if (users[i]->getUsername() == username && !isAdministrator(users[i]))
            return dynamic_cast<User*>(users[i]);
        else if (users[i]->getUsername() == username && isAdministrator(users[i]))
            return dynamic_cast<Admin*>(users[i]);
       
    }
    return nullptr;
}

Chat* System::findChatById(size_t id)
{
    size_t size = chats.getSize();
    for (size_t i = 0; i < size; ++i) {
        if (chats[i]->getID() == id && dynamic_cast<Individual* >(chats[i]))
            return dynamic_cast<Chat*>(chats[i]);
        else if (chats[i]->getID() == id && dynamic_cast<Group*>(chats[i]))
            return dynamic_cast<Group*>(chats[i]);

    }
    return nullptr;
}



void System::removeUserByUsername(const String& username)
{
    for (size_t i = 0; i < users.getSize(); i++) {
        if (users[i]->getUsername() == username) {
            users.remove(i);
            std::cerr << "User removed.\n";

            return;
        }
    }
    std::cerr << "User with name " << username << " not found.\n";
}

void System::removeChatById(size_t id)
{
    for (size_t i = 0; i < chats.getSize(); i++) {
        if (chats[i]->getID() == id) {
            chats.remove(i);
            std::cerr << "Chat removed.\n";
            return;
        }
    }
    std::cerr << "Chat with ID " << id << " not found.\n";
}

void System::removeMessagesFromUser(const String& username) {
    for (size_t i = 0; i < chats.getSize(); ++i) {
        if (chats[i]) {
            chats[i]->del(username); 
        }
    }

    std::cout << "All messages from user '" << username << "' removed from all chats.\n";
}


User* System::getInstance()
{
    return session;
}

void System::setSession(User* other)
{
    session = other;
}

bool System::usernameExists(const String& other)
{
    size_t size = users.getSize();
    for (size_t i = 0; i < size; i++)
    {
        if (other == getUsers()[i]->getUsername()) return true;
    }
    return false;
}

void System::removeChatFromUsers(size_t id) {
    for (size_t i = 0; i < users.getSize(); ++i) {
        users.getUsers()[i]->removeChat(id);
    }
}

void System::printAllChats() const
{
    for (size_t i = 0; i < chats.getSize(); i++)
    {
        std::cout << chats.getChats()[i]->getID() << " Id.\n";
        chats.getChats()[i]->printMessages(String());
        std::cout<<std::endl;
    }
}
