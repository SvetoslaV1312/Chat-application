#pragma once
#include "App.h" 

class Command {
public:
    virtual void execute(SystemManager& manager) = 0;
    virtual bool isAdminOnly() const { return false; }
    virtual ~Command() = default;
};

class LoginCommand : public Command {
public:
    void execute( SystemManager& manager)  override;
};

class RegisterCommand : public Command {
public:
    void execute( SystemManager& manager)  override;
};

class MakeAdminCommand : public Command {
public:
    void execute(SystemManager& manager)  override;
};

class CreateChatCommand : public Command {
public:
    void execute(SystemManager& manager)  override;
};


class ViewChatsCommand : public Command {
public:
    void execute( SystemManager& manager)  override;
};

class SelectChatCommand : public Command {
public:
    void execute( SystemManager& manager)  override;
};
class CreateGroupCommand : public Command {
public:
    void execute( SystemManager& manager)  override;
};
class AddToGroupCommand : public Command {
public:
    void execute( SystemManager& manager)  override;
};
class LeaveGrupCommand : public Command {
public:
    void execute( SystemManager& manager)  override;
};
class KickFromGroupCommand : public Command {
public:
    void execute( SystemManager& manager)  override;
};
class SetGroupAdminCommand : public Command {
public:
    void execute( SystemManager& manager)  override;
};
class GroupStatsCommand : public Command {
public:
    void execute( SystemManager& manager)  override;
};
class DeleteUserCommand : public Command {
public:
    void execute( SystemManager& manager)  override;
};
class DeleteGroupCommand : public Command {
public:
    void execute( SystemManager& manager)  override;
};
class ViewAllChatsCommand : public Command {
public:
    void execute( SystemManager& manager)  override;
};

class LogoutCommand : public Command {
public:
    void execute(SystemManager& manager)  override;
};