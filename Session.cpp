//
// Created by tzachu@wincs.cs.bgu.ac.il on 22/11/2019.
//
#include "Watchable.h"
#include "Session.h"
#include "User.h"
#include "Statics_Functions.h"

///RULE OF 5
Session::Session(const std::string &configFilePath){//constructor
   content=Statics_Functions::buildDataBase(configFilePath);
   activeUser = new LengthRecommenderUser("default");
   userMap.insert({"default",activeUser});

}
Session::Session(const Session & other) {//copy constructor
    this->copy(other);
}
Session& Session::operator=(const Session& other) {//copy Assignment operator
    if(this != &other){
        clear();
        this->copy(other);
    }
    return *this;
}
Session::Session(Session&& other):content(other.content),actionsLog(other.actionsLog),userMap(other.userMap),activeUser(other.activeUser){//move constructor
    other.clearPointersObjects();
}
Session& Session::operator=(Session &&other){//move assignment operator.
    if(this!=&other){
        clear();
        content=other.content;
        actionsLog=other.actionsLog;
        userMap=other.userMap;
        activeUser=other.activeUser;
        other.clearPointersObjects();
    }
    return *this;
}
void Session::clearPointersObjects(){
    for(Watchable* w: content)
        w=nullptr;
    for(BaseAction* action: actionsLog)
        action= nullptr;
    for(auto x: userMap)
        x.second= nullptr;
    activeUser=nullptr;
}
Session::~Session() {//destructor
    clear();
}
void Session::copy(const Session & other){
    for(int i=0;i<other.content.size();i++)
        this->content.push_back(other.content[i]->clone());
    for(int i=0;i<other.actionsLog.size();i++)
        this->actionsLog.push_back(actionsLog[i]);//need to impliment clone for actions.
    for(auto it : other.userMap)
        this->userMap.insert(it);
    this->activeUser=other.activeUser->clone();
}
void Session::start(){
    string s1;
    bool flag=true;
    while (flag) {
        cin >> s1;
        vector<string> input = Statics_Functions::getCommand(s1, " ");
        if(input[0]=="createuser"){
            BaseAction *execute=new CreateUser(input[1],input[2]);
                actionsLog.push_back(execute);
        }
        else if(input[0]=="changeuser"){
            BaseAction *execute=new ChangeActiveUser(input[1]);
            actionsLog.push_back(execute);
        }
        else if(input[0]=="deleteuser"){
            BaseAction *execute=new DeleteUser(input[1]);
            actionsLog.push_back(execute);
        }
        else if(input[0]=="dupuser"){
            BaseAction *execute=new DuplicateUser(input[1],input[2]);
            actionsLog.push_back(execute);
        }
        else if(input[0]=="content"){
            BaseAction *execute=new PrintContentList();
            actionsLog.push_back(execute);
        }
        else if(input[0]=="watchhist"){
            BaseAction *execute=new PrintWatchHistory();
            actionsLog.push_back(execute);
        }
        else if(input[0]=="watch"){
            BaseAction *execute=new Watch(input[1]);
            actionsLog.push_back(execute);
        }
        else if(input[0]=="log"){
            BaseAction *execute=new PrintActionsLog();
            actionsLog.push_back(execute);
        }
        else if(input[0]=="exit"){
            BaseAction *execute=new PrintActionsLog();
            actionsLog.push_back(execute);
        }
        else cout<<"Invalid command. Try again."<<endl;
    }
}




void Session::clear(){
    for(int i=0;i<content.size();i++)
        delete content[i];
    for(int i=0;i<actionsLog.size();i++)
        delete actionsLog[i];
    delete activeUser;
    userMap.clear();
}






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
bool Session::printContentList() const{ //maybe need to change toString methood to only name, create new toString function
    int j=1;
    for (auto i = this->content.begin(); i != this->content.end(); ++i) {
        cout << j + ". " + (*i)->fullToString() << endl;
        j++;
    }

    return true;
}

std::vector<BaseAction*> & Session::getActionLog(){
    return  actionsLog;
}