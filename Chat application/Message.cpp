#include "Message.h"
#include <iostream>

Message::Message(const String& sender, const String& text)
    : sender(sender), text(text)
{
    setTime();
}

void Message::setTime() {
    time_t now = std::time(nullptr);
    tm* localTime = localtime(&now);

    char buffer[20];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localTime);

    time = String(buffer);
}

String Message::getSender() const
{
    return sender;
}

String Message::getText() const
{
    return text;
}

String Message::getTime() const
{
    return time;
}

void Message::readBinary(std::istream& is)
{
    sender.readBinary(is);
    text.readBinary(is);
    time.readBinary(is);
}

void Message::writeBinary(std::ostream& os) const
{
    sender.writeBinary(os);
    text.writeBinary(os);
    time.writeBinary(os);
}

std::ostream& operator<<(std::ostream& os, const Message& other)
{
    return os << other.sender << " " << other.text << "\n" << other.time << "\n";
}
 std::istream& operator>>(std::istream& is, Message& other) {
    if (getline(is, other.sender, ' ')) { 
        if (getline(is, other.text, '\n')) { 
            if (getline(is, other.time,'\n')) { // 
                return is;
            }
        }
    }
    return is;
}