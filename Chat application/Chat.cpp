#include "Chat.h"
#include <limits>
#include <exception>

size_t Chat::lastId = 0;


Individual::Individual(std::ifstream& fs)
{
    fs >> id;
    fs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    fs >> users[0] >> users[1];
    fs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    handleMessages(fs);
}

void Chat::handleMessages(std::istream& fs)
{
    size_t numberMessages;
    if (!(fs >> numberMessages)) {
        throw std::runtime_error("Failed to read number of messages.");
    }

    fs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    for (size_t i = 0; i < numberMessages; i++)
    {
        Message currentMessage;
        if (fs >> currentMessage) {
            messages.push_back(currentMessage);
        }
        else {
            throw std::runtime_error("Failed to read message");
        }
    }
}


void Chat::handleMessagesBin(std::istream& fs)
{
    size_t numberMessages = 0;
    fs.read(reinterpret_cast<char*>(numberMessages), sizeof(numberMessages));
    for (size_t i = 0; i < numberMessages; i++)
    {
        Message currentMessage;
        currentMessage.readBinary(fs);
        messages.push_back(currentMessage);
    }
}

size_t Chat::getStaticId() const
{
    return Chat::lastId;
}

String Individual::getName(const String& caller)
{
    return users[0] == caller ? users[1] : users[0];
}

void Individual::seeAndSendMessage(const String& sender)
{
    std::cout << "Individual chat" << std::endl;
    printMessages(sender);
    sendMessage(sender);
}


void Individual::del(const String& user)
{
    for (size_t i = 0; i < 2; i++)
    {
        if (users[i] == user) users[i] = nullptr;
    }
    size_t size = messages.getSize();
    for (size_t i = 0; i < size; i++)
    {
        if (messages[i].getSender() == user) messages.remove(i);
    }
}

void Individual::displayStats() const
{
    std::cout << "Id: " << id << std::endl;
    for (size_t i = 0; i < 2; i++)
    {
        std::cout << "User number" << i << " : " << users[i] << std::endl;
    }
    size_t messageCount = messages.getSize();
    std::cout << "The number of messages is: " << messageCount << std::endl;
}

void Chat::printMessages(const String& sender) const
{
    size_t messageCount = messages.getSize();
    for (size_t i = 0; i < messageCount; i++)
    {
        std::cout << "[" << displaySender(messages[i].getSender(), sender) << ", " << messages[i].getTime() << "] " << messages[i].getText() << std::endl;
    }
}

String Chat::displaySender(const String& other, const String& sender) const
{
    return other == sender ? String("you") : other;
}

void Chat::pushMessage(const Message& message)
{
    messages.push_back(message);
}

void Chat::sendMessage(const String& sender)
{
    std::cout << "Do you want to send a message? (y/n) ";
    char option = '\0';
    std::cin >> option;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    String messageText;
    while (option == 'y')
    {
        std::cout << "Enter message: ";
        getline(std::cin, messageText, '\n');
        pushMessage(Message(sender, messageText));
        std::cout << "Do you want to send another message? (y/n) ";
        std::cin >> option;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}


void Group::seeAndSendMessage(const String& sender)
{
    std::cout << "Group name: " << name << std::endl;
    printMessages(sender);
    sendMessage(sender);
}

String Group::getName(const String& caller)
{
    return name;
}

void Group::del(const String& user)
{
    size_t size = users.getSize();
    for (size_t i = 0; i < 2; i++)
    {
        if (users[i] == user) users[i] = nullptr;
    }
    size = messages.getSize();
    for (size_t i = 0; i < size; i++)
    {
        if (messages[i].getSender() == user) messages.remove(i);
    }
}

bool Group::needApproval() const
{
    return needsApproval;
}

size_t Chat::getID() const
{
    return this->id;
}

void Chat::printLastIdTxt(std::ostream& os)
{
    os << lastId<<std::endl;

}

void Chat::loadLastIdTxt(std::istream& is)
{
    is >> lastId;
    is.ignore();
}

void Chat::printLastIdBin(std::ostream& os)
{
    os.write(reinterpret_cast<const char*>(&lastId), sizeof(lastId));
}

void Chat::loadLastIdBin(std::istream& is)
{
    is.read(reinterpret_cast<char*>(&lastId), sizeof(lastId));
}

Group::Group(const String& name, Vector<String> usernames, bool needsApproval)
{
    this -> id = Chat::lastId++;
    this->name = name;
    this -> users = usernames;
    this -> admins.push_back(usernames[0]);
    this -> needsApproval = needsApproval;
}

void Group::addToGroup(const String& user)
{
    if (id >= lastId)
    {
        std::cerr << "Group doesn't exist";
        return;
    }
    users.push_back(user);
}

void Group::leaveGroup(const String& user)
{
    if (id >= lastId)
    {
        std::cerr << "Group doesn't exist";
        return;
    }
    size_t usersCount = users.getSize();
    for (size_t i = 0; i < usersCount; i++)
    {
        if (users[i] == user) users.remove(i);
        {
            std::cout << "User removed from the group.\n";
            return;
        }
    }
    std::cout << "User doesn't belong to the group.\n";
}

bool Group::userIsAdmin(const String& user) const
{
    size_t adminCount = admins.getSize();
    for (size_t i = 0; i < adminCount; i++)
    {
        if (admins[i] == user) return true;
    }
    return false;
}

void Group::removeUserFromGroup(const String& user)
{
    leaveGroup(user);
}

void Group::makeAdmin(const String& user)
{
    admins.push_back(user);
}

void Group::displayStats() const
{
    std::cout << "Group" << name << std::endl;
    std::cout << "Id: " << id << std::endl;
    std::cout << "The group needs approval: " << (int)needsApproval << std::endl;
    size_t userCount = users.getSize();
    std::cout << "Number of users: " << userCount << std::endl;
    for (size_t i = 0; i < userCount; i++)
    {
        std::cout << "User number" << i << " : " << users[i] << std::endl;
    }
    size_t messageCount = messages.getSize();
    std::cout << "Number of messsages:" << messageCount << std::endl;
}

void Individual::printTxt(std::ostream& os) const {
    os << id << '\n';
    os << users[0] << '\n' << users[1] << '\n';
    os << messages.getSize() << '\n';
    for (size_t i = 0; i < messages.getSize(); ++i) {
        os << messages[i];
    }
}

Chat* Individual::clone() const {
    return new Individual(*this);
}

Individual::Individual(const String& username1, const String& username2)
{
    this->users[0] = username1;
    this->users[1] = username2;
    this->id = lastId++;
}

void Individual::readBin(std::istream& is)
{
    is.read(reinterpret_cast<char*>(&id), sizeof(id));
    users[0].readBinary(is);
    users[1].readBinary(is);
    handleMessagesBin(is);
}

Group::Group(std::ifstream& fs)
{
    fs >> id;
    fs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    fs >> needsApproval;
    fs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    size_t userCount = 0;
    fs >> userCount;
    fs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    users.clear();
    for (size_t i = 0; i < userCount; i++)
    {
        String user;
        getline(fs, user, '\n');
        users.push_back(user);
    }
    size_t adminCount = 0;
    fs >> adminCount;
    for (size_t i = 0; i < adminCount; i++)
    {
        String admin;
        getline(fs, admin, '\n');
        admins.push_back(admin);
    }
    getline(fs, name, '\n');
    handleMessages(fs);
}


void Group::printTxt(std::ostream& os) const {
    os << id << '\n';
    os << (int)needsApproval << '\n';
    os << users.getSize() << '\n';
    for (size_t i = 0; i < users.getSize(); ++i) {
        os << users[i] << '\n';
    }
    for (size_t i = 0; i < admins.getSize(); i++)
    {
        os << admins[i] << '\n';
    }
    os << name << '\n';
    os << messages.getSize() << '\n';
    for (size_t i = 0; i < messages.getSize(); ++i) {
        os << messages[i];
    }
}

Chat* Group::clone() const {
    return new Group(*this);
}

bool Group::hasUser(const String& user) const
{
    for (size_t i = 0; i < users.getSize(); i++)
    {
        if (users[i] == user) return true;
    }
    return false;
}

void Group::perfromAdd(String& username)
{
    if (!hasUser(username))
    {
        addToGroup(username);
        std::cout << "User is part of the group now.\n";

    }
    else std::cout << "User is already part of the group.\n";
}

void Group::readBin(std::istream& is) {
    is.read((char*)&id, sizeof(id));

    int approval = 0;
    is.read((char*)&approval, sizeof(approval));
    needsApproval = static_cast<bool>(approval);

    size_t userCount = 0;
    is.read((char*)&userCount, sizeof(userCount));
    users.clear();
    for (size_t i = 0; i < userCount; ++i) {
        String user;
        user.readBinary(is);
        users.push_back(user);
    }
    size_t adminCount = 0;
    is.read((char*)&adminCount, sizeof(adminCount));
    for (size_t i = 0; i < adminCount; ++i) {
        String admin;
        admin.readBinary(is);
        admins.push_back(admin);
    }
    name.readBinary(is);

    size_t messageCount = 0;
    is.read((char*)&messageCount, sizeof(messageCount));
    messages.clear();
    for (size_t i = 0; i < messageCount; ++i) {
        Message msg;
        msg.readBinary(is);
        messages.push_back(msg);
    }
}

void Individual::printBin(std::ostream& os) const {
    String type = "Individual";
    type.writeBinary(os);
    os.write(reinterpret_cast<const char*>(&id), sizeof(id));

    users[0].writeBinary(os);
    users[1].writeBinary(os);

    size_t msgCount = messages.getSize();
    os.write(reinterpret_cast<const char*>(&msgCount), sizeof(msgCount));
    for (size_t i = 0; i < msgCount; ++i) {
        messages[i].writeBinary(os);
    }
}

void Group::printBin(std::ostream& os) const {
    String type = "Group";
    type.writeBinary(os);
    os.write(reinterpret_cast<const char*>(&id), sizeof(id));

    int approval = (int)needsApproval;
    os.write(reinterpret_cast<const char*>(&approval), sizeof(approval));

    size_t userCount = users.getSize();
    os.write(reinterpret_cast<const char*>(&userCount), sizeof(userCount));
    for (size_t i = 0; i < userCount; ++i) {
        users[i].writeBinary(os);
    }
    size_t adminCount = admins.getSize();
    os.write(reinterpret_cast<const char*>(&adminCount), sizeof(adminCount));
    for (size_t i = 0; i < adminCount; ++i) {
        admins[i].writeBinary(os);
    }
    name.writeBinary(os);

    size_t msgCount = messages.getSize();
    os.write(reinterpret_cast<const char*>(&msgCount), sizeof(msgCount));
    for (size_t i = 0; i < msgCount; ++i) {
        messages[i].writeBinary(os);
    }
}
