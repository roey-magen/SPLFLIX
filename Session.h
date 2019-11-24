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
    ~Session();//destructor
    void start();
    const  std::vector<Watchable*> & getContent() const;//our addition.
    unordered_map<string, User *> getUserMap() const; //our addition
    bool changeActiveUser(string name);  //our addition, return true if change user sucsess
    bool deleteUser(string name);
    bool printContentList() const;

    User & getActiveUser() const;//check how to return const- we have problem in getNextWatchable in watchable class.

private:
    std::vector<Watchable*> content;//available watching content (read the json text to this vector).
    std::vector<BaseAction*> actionsLog;//history of all actions.
    std::unordered_map<std::string,User*> userMap;
    User* activeUser;//currently active user (only 1 user can be active at the same time).
};
#endif
