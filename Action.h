#ifndef ACTION_H_
#define ACTION_H_

#include <string>
#include <iostream>

class Session;
using namespace std;
enum ActionStatus{
	PENDING, COMPLETED, ERROR
};


class BaseAction{//the system input. ABSTRACT CLASS
public:
	BaseAction();//empty constructor
	ActionStatus getStatus() const;
	virtual void act(Session& sess)=0;// perform a specific action (not implimented here, implimented on each act)
	virtual std::string toString() const=0;
    virtual BaseAction* clone()=0;
    void setErrorMsg(const string & msg);
    void setStatus(const ActionStatus e);
protected:
	void complete();// called in order to change to status to COMPLETED.
	void error(const std::string& errorMsg);//display to the screen the error messege and change the status to ERROR.
	std::string getErrorMsg() const;
private:
	std::string errorMsg;
	ActionStatus status;// pending, completed, error
};

class CreateUser  : public BaseAction {
public:
    CreateUser(string userName,string recommend_algo); //our addition
	virtual void act(Session& sess);
	virtual std::string toString() const;
    virtual BaseAction* clone();
private: //our addition
    string userName;
    string recommend_algo;
};

class ChangeActiveUser : public BaseAction {
public:
    ChangeActiveUser(string name);
	virtual void act(Session& sess);
	virtual std::string toString() const;
    virtual BaseAction* clone();

private:
    string nameActiveUser;
};

class DeleteUser : public BaseAction {
public:
    DeleteUser(string name);
	virtual void act(Session & sess);
	virtual std::string toString() const;
    virtual BaseAction* clone();
private:
    string name;
};

class DuplicateUser : public BaseAction {
public:
    DuplicateUser(string originName, string newName);
	virtual void act(Session & sess);
	virtual std::string toString() const;
    virtual BaseAction* clone();

private:
    string newName;
    string originName;
};

class PrintContentList : public BaseAction {
public:
    PrintContentList();
	virtual void act (Session& sess);
	virtual std::string toString() const;
    virtual BaseAction* clone();
};

class PrintWatchHistory : public BaseAction {
public:
    PrintWatchHistory();
	virtual void act (Session& sess);
	virtual std::string toString() const;
    virtual BaseAction* clone();

};

class Watch : public BaseAction {
public:
    Watch(long contentId);
	virtual void act(Session& sess);
	virtual std::string toString() const;
    virtual BaseAction* clone();

private:
   long contentId;
};

class PrintActionsLog : public BaseAction {
public:
    PrintActionsLog();
	virtual void act(Session& sess);
	virtual std::string toString() const;
    virtual BaseAction* clone();
};

class Exit : public BaseAction {
public:
    Exit();
	virtual void act(Session& sess);
	virtual std::string toString() const;
    virtual BaseAction* clone();
};
#endif
