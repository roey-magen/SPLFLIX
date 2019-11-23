//
// Created by tzachu@wincs.cs.bgu.ac.il on 22/11/2019.
//
#include "Watchable.h"
#include "Session.h"
#include "User.h"
const  std::vector<Watchable*> & Session::getContent() const{
    return content;
}
User & Session::getActiveUser()  const{//check how to return const- we have problem in getNextWatchable in watchable class.
    return *activeUser;
}

unordered_map<string, User *> Session::getUserMap() const{
    return userMap;
}

bool Session::changeActiveUser(string name){  //return true if change user sucsess
    if (userMap.count(name)==0)  return false;
    else activeUser=userMap.find(name)->second;
    return true;
}

bool Session::deleteUser(string name){
    if(userMap.count(name)==0) return false;
    userMap.erase(name);//maybe need to delete the user himself!!!!!!
    return true;

}