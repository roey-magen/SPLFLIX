#ifndef SESSION_H_
#define SESSION_H_

#include <vector>
#include <unordered_map>
#include <string>
#include "Action.h"

class User;
class Watchable;

class Session{//this is the main class of the program.
public:
    Session(const std::string &configFilePath);//constructor.
    Session(const Session & other);//copy constructor
    ~Session();//destructor
    Session& operator=(const Session& other);//copy Assignment operator
    Session(Session&& other);//move constructor
    Session& operator=(Session &&other);//move assignment operator.
    void clearPointersObjects();
    void copy(const Session & other);
    void start();
    void updateUserMap(pair<string,User*>);
    void clear();
    bool changeActiveUser(string name);  //our addition, return true if change user sucsess
    bool deleteUser(string name);
    bool dupUser(string originName,string newName);
    bool printContentList() const;
    const  std::vector<Watchable*> & getContent() const;//our addition.
    User & getActiveUser() const;//check how to return const- we have problem in getNextWatchable in watchable class.
    std::vector<BaseAction*> & getActionLog();
    unordered_map<string, User *> getUserMap() const; //our addition
private:
    std::vector<Watchable*> content;//available watching content (read the json text to this vector).
    std::vector<BaseAction*> actionsLog;//history of all actions.
    std::unordered_map<std::string,User*> userMap;
    User* activeUser;//currently active user (only 1 user can be active at the same time).
};
#endif
