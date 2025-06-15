#pragma once
#include <ctime>
#include "String.h"
//

class Message
{
public:
    Message() = default;
    Message(const String& sender, const String& text);
    void setTime();
    String getSender() const;
    String getText() const;
    String getTime() const;
    void readBinary(std::istream& is);
    void writeBinary(std::ostream& os)const;
    friend std::ostream& operator<<(std::ostream& os, const Message& other);

    friend std::istream& operator>>(std::istream& is, Message& other);

private:
    String sender;
    String text;
    String time;
protected:
};