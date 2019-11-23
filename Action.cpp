#include "Action.h"
#include "User.h"
#include "Session.h""
#include "Watchable.h"
#include <unordered_map>
using namespace std;

BaseAction::BaseAction():errorMsg(""), status(PENDING){} //check if need to init

ActionStatus BaseAction::getStatus() const{ //check if is it ok return by value
    return status;
}

//BaseAction::~BaseAction(){} - CHECK IF NEED

void BaseAction::complete() {
    status = ActionStatus::COMPLETED;
}

void BaseAction::error(const std::string &errorMsg)  {
    status = ActionStatus::ERROR;
    this->errorMsg=errorMsg;
    cout<<"Error - "+errorMsg; //check if we need it here
}

std::string BaseAction::getErrorMsg() const{
    return errorMsg;
}


CreateUser::CreateUser(string userName, string recommend_algo):BaseAction(),userName(userName), recommend_algo(recommend_algo) {}

void CreateUser::act(Session& sess){
    if(recommend_algo!="len" && recommend_algo=="rer" && recommend_algo!="gen")
        this->error("no legal algorithm");
    else if( sess.getUserMap().count(userName)>0)
        this->error("name already exist"); ///need to check if name is legal
     else { //input legal
        User *u;
        if (recommend_algo == "len") {
            u = new LengthRecommenderUser("userName");
            sess.getUserMap().insert({userName, u});
        } else if (recommend_algo == "rer") {
            u = new RerunRecommenderUser("userName");
            sess.getUserMap().insert({userName, u});
        } else if (recommend_algo == "gen") {
            u = new GenreRecommenderUser("userName");
            sess.getUserMap().insert({userName, u});
        }
        u = nullptr;
        this->complete();
    }
}

ChangeActiveUser::ChangeActiveUser(string nameActiveUser):nameActiveUser(nameActiveUser) {}

void ChangeActiveUser::act(Session& sess){
    if(sess.changeActiveUser(nameActiveUser)) this->error("input name is invalid");
    else this->complete();
}

DeleteUser::DeleteUser(string name): name(name) {}

void DeleteUser::act(Session& sess){
    if(sess.deleteUser(name)) this->error("input name is invalid");
    else this->complete();
}

//DuplicateUser::DuplicateUser(string newName, string originName):newName(newName),originName(originName) {}

