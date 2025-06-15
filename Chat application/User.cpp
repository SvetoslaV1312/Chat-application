#include "User.h"
#include <fstream>
#include "Chat.h"

size_t Admin::lastID = 0;

User::User(const String& username, const String& password)
: username(username), password(password) {}



User::User(const User& other)
    : username(other.username), password(other.password), chats(other.chats) {}



void User::printTxt(std::ostream& os) const
{
    os << "User\n";
    os << username << " " << password << std::endl;
    os << chats;
}

void User::readTxt(std::istream& is)
{
    is >> username;
    is.ignore();
    is >> password;
    is.ignore();
    is >> chats;
}



bool User::operator==(const User& other) const {
    return username == other.username && password == other.password && chats == other.chats;
}

bool User::operator!=(const User& other) const {
    return !(*this == other);
}


const Vector<size_t> User::getChats() const
{
    return chats;
}



String User::getUsername() const
{
    return username;
}

User* User::clone() const {
    if (username.getSize() == 0 || password.getSize() == 0) {
        std::cerr << "Warning: Attempting to clone invalid User\n";
        return nullptr;
    }
    return new User(*this);
}



bool User::checkPassword(const String& password)
{
    return password==this->password;
}



void User::addChat(size_t chatId)
{
    chats.push_back(chatId);
}

void User::removeChat(size_t id)
{
    for (size_t i = 0; i < chats.getSize(); i++)
    {
        if (chats[i] == id) {
            chats.remove(i);
            break;
        }
    }
}

void User::printBin(std::ostream& os) const
{
    String type = "User";
    type.writeBinary(os);
    username.writeBinary(os);
    password.writeBinary(os);
    chats.writeBinary(os);
}

void User::readBin(std::istream& is)
{
    username.readBinary(is);
    password.readBinary(is);
    chats.readBinary(is);
}



bool isAdministrator(User* user)
{
    if (user == nullptr) {
        return false; 
    }
    Admin* admin = dynamic_cast<Admin*>(user);
    return admin != nullptr; 
}

User* Admin::clone() const
{
    return new Admin(*this);
}

Admin::Admin(const String& username, const String& password)
{
    id = lastID++;
    this->username = username;
    this->password = password;
}

Admin::Admin(const Admin& other) : User(other) {
    id = other.id;
}


Admin::Admin(const User& other) : User(other) {
    id = lastID++;
}

void Admin::printTxt(std::ostream& os) const
{
    os << "Admin\n";
    os << username << " " << password << std::endl;
    os << chats;
    os << id << ::std::endl;

}

void Admin::readTxt(std::istream& is)
{
    User::readTxt(is);
    is >> id;
    is.ignore();
}

void Admin::printLastIdTxt(std::ostream& os)
{
    os << lastID<<std::endl;
}

void Admin::loadLastIdTxt(std::istream& is)
{
    is >> lastID;
    is.ignore();
}

void Admin::printLattIdBin(std::ostream& os)
{
    os.write(reinterpret_cast<const char*>(&lastID), sizeof(lastID));
}

void Admin::loadLastIDBin(std::istream& is)
{
    is.read(reinterpret_cast<char*>(&lastID), sizeof(lastID));
}

void Admin::readBin(std::istream& is)
{
    User::readBin(is);
    is.read(reinterpret_cast<char*>(&id), sizeof(id));
}

void Admin::printBin(std::ostream& os) const
{
    String type = "Admin";
    type.writeBinary(os);
    username.writeBinary(os);
    password.writeBinary(os);
    chats.writeBinary(os);
    os.write(reinterpret_cast<const char*>(&id), sizeof(id));

}
