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