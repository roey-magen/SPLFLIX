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
private:
    std::vector<Watchable*> content;//available watching content (read the json text to this vector).
    std::vector<BaseAction*> actionsLog;//history of all actions.
    std::unordered_map<std::string,User*> userMap;
    User* activeUser;//currently active user (only 1 user can be active at the same time).
};
#endif
