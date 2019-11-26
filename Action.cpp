#include "Action.h"
#include "User.h"
#include "Session.h"
#include "Watchable.h"
#include <unordered_map>
using namespace std;

BaseAction::BaseAction():errorMsg(""), status(PENDING){} //check if need to init
ActionStatus BaseAction::getStatus() const{ //check if is it ok return by value
    return status;
}
//BaseAction::~BaseAction(){}
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

///CREATE_USER
CreateUser::CreateUser(string userName, string recommend_algo):BaseAction(),userName(userName), recommend_algo(recommend_algo) {}
void CreateUser::act(Session& sess){
    if(recommend_algo!="len" && recommend_algo!="rer" && recommend_algo!="gen")
        this->error("no legal algorithm");
    else if( sess.getUserMap().count(userName)>0)
        this->error("name already exist"); ///need to check if name is legal
     else { //input legal
        User *u;
        if (recommend_algo == "len") {
            u = new LengthRecommenderUser(userName);
            sess.getUserMap().insert({userName, u});
        } else if (recommend_algo == "rer") {
            u = new RerunRecommenderUser(userName);
            sess.getUserMap().insert({userName, u});
        } else if (recommend_algo == "gen") {
            u = new GenreRecommenderUser(userName);
            sess.getUserMap().insert({userName, u});
        }
        u= nullptr;
        this->complete();
    }
}
std::string CreateUser::toString() const{}

///CHANGE_ACTIVE_USER
ChangeActiveUser::ChangeActiveUser(string nameActiveUser):nameActiveUser(nameActiveUser) {}
void ChangeActiveUser::act(Session& sess){
    if(sess.changeActiveUser(nameActiveUser)) this->error("input name is invalid");
    else this->complete();
}
std::string ChangeActiveUser::toString() const{}

///DELETE_USER
DeleteUser::DeleteUser(string name): name(name) {}
void DeleteUser::act(Session& sess){
    if(sess.deleteUser(name)) this->error("input name is invalid");
    else this->complete();
}
std::string DeleteUser::toString() const{}



///DUPLICATE USER
DuplicateUser::DuplicateUser(string newName, string originName):newName(newName),originName(originName) {}
void DuplicateUser::act(Session& sess){}
std::string DuplicateUser::toString() const{}



PrintContentList::PrintContentList() {} //check if is ok to use fullToString
void PrintContentList::act (Session& sess){
   if(sess.printContentList()) this->complete();
}
std::string PrintContentList::toString() const{}




PrintWatchHistory::PrintWatchHistory() {}
void PrintWatchHistory::act(Session& sess) {
    cout<<"Watch history for "+sess.getActiveUser().getName()<<endl;
    sess.getActiveUser().printHistory();
}
std::string PrintWatchHistory::toString() const{}


Exit::Exit(){}
void Exit::act(Session& sess){}
std::string Exit::toString() const{}


Watch::Watch(int contentId):contentId(contentId) {} //not finish
string Watch::toString() const {}
void Watch::act(Session &sess) {//need to complete
    cout<<"Watching "+sess.getContent()[contentId]->toString()<<endl;
}

PrintActionsLog::PrintActionsLog(){}
void PrintActionsLog::act(Session& sess){ //not finish
//    string status="";
//    for (vector<BaseAction>::reverse_iterator i = sess.getActionLog().rbegin(); i != sess.getActionLog().rend(); i++) {
//        if(i->getStatus()== ActionStatus::ERROR)
//            status="ERROR";
//        if(i->getStatus()== ActionStatus::COMPLETED)
//            status="COMPLETED";
//   //     cout << i->toString()+" "+status+i->getErrorMsg()<<endl;
//    }
}
std::string PrintActionsLog::toString() const{}


