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
    cout<<"Error - "+errorMsg<<endl; //check if we need it here
}
void BaseAction::setErrorMsg(const string & msg){
    errorMsg=msg;
}
void BaseAction::setStatus(const ActionStatus e){
    status=e;
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
            sess.updateUserMap({userName, u});
        } else if (recommend_algo == "rer") {
            u = new RerunRecommenderUser(userName);
            sess.updateUserMap({userName, u});
        } else if (recommend_algo == "gen") {
            u = new GenreRecommenderUser(userName);
            sess.updateUserMap({userName, u});
        }
        u= nullptr;
        this->complete();
    }
}
std::string CreateUser::toString() const{
       if(getStatus()==COMPLETED)
           return "CreateUser COMPLETED";
       else if(getStatus()==ERROR) return "CreateUser ERROR: "+getErrorMsg();
}
BaseAction* CreateUser::clone(){
    CreateUser* toReturn=new CreateUser(this->userName,this->recommend_algo);
    toReturn->setErrorMsg(this->getErrorMsg());
    toReturn->setStatus(this->getStatus());
}


///CHANGE_ACTIVE_USER
ChangeActiveUser::ChangeActiveUser(string nameActiveUser):nameActiveUser(nameActiveUser) {}
void ChangeActiveUser::act(Session& sess){
    if(sess.changeActiveUser(nameActiveUser)) this->complete();
    else this->error("input name is invalid");
}
std::string ChangeActiveUser::toString() const{
    if(getStatus()==COMPLETED)
        return "ChangeActiveUser COMPLETED";
    else if(getStatus()==ERROR) return "ChangeActiveUse ERROR: "+getErrorMsg();
}
BaseAction* ChangeActiveUser::clone(){
    ChangeActiveUser* toReturn=new ChangeActiveUser(this->nameActiveUser);
    toReturn->setErrorMsg(this->getErrorMsg());
    toReturn->setStatus(this->getStatus());
}


///DELETE_USER
DeleteUser::DeleteUser(string name): name(name) {}
void DeleteUser::act(Session& sess){
    if(sess.deleteUser(name)) this->complete();
    else this->error("input name is invalid");
}
std::string DeleteUser::toString() const{
    if(getStatus()==COMPLETED)
        return "DeleteUser COMPLETED";
    else if(getStatus()==ERROR) return "DeleteUser ERROR: "+getErrorMsg();
}
BaseAction* DeleteUser::clone(){
    DeleteUser* toReturn=new DeleteUser(this->name);
    toReturn->setErrorMsg(this->getErrorMsg());
    toReturn->setStatus(this->getStatus());
}


///DUPLICATE USER
DuplicateUser::DuplicateUser(string originName, string newName):newName(newName),originName(originName) {}
void DuplicateUser::act(Session& sess){
    if(sess.dupUser(newName,originName)) this->complete();
    else this->error("input name is invalid");
}
std::string DuplicateUser::toString() const{
    if(getStatus()==COMPLETED)
        return "DuplicateUser COMPLETED";
    else if(getStatus()==ERROR) return "DuplicateUser ERROR: "+getErrorMsg();
}
BaseAction* DuplicateUser::clone(){
    DuplicateUser *toReturn=new DuplicateUser(this->newName,this->originName);
    toReturn->setErrorMsg(this->getErrorMsg());
    toReturn->setStatus(this->getStatus());
}


///PRINT CONTENT LIST
PrintContentList::PrintContentList() {} //check if is ok to use fullToString
void PrintContentList::act (Session& sess){
   if(sess.printContentList()) this->complete();
}
std::string PrintContentList::toString() const{
    if(getStatus()==COMPLETED)
        return "PrintContentList COMPLETED";
    else if(getStatus()==ERROR) return "PrintContentList ERROR: "+getErrorMsg();
}
BaseAction* PrintContentList::clone(){
    PrintContentList *toReturn=new PrintContentList();
    toReturn->setErrorMsg(this->getErrorMsg());
    toReturn->setStatus(this->getStatus());
}


///PRINT WATCH HISTROY
PrintWatchHistory::PrintWatchHistory() {}
void PrintWatchHistory::act(Session& sess) {
    cout<<"Watch history for "+sess.getActiveUser().getName()<<endl;
    sess.getActiveUser().printHistory();
    this->complete();
}
std::string PrintWatchHistory::toString() const{
    if(getStatus()==COMPLETED)
        return "PrintWatchHistory COMPLETED";
    else if(getStatus()==ERROR) return "PrintWatchHistory ERROR: "+getErrorMsg();
}
BaseAction* PrintWatchHistory::clone(){
    PrintWatchHistory *toReturn=new PrintWatchHistory();
    toReturn->setErrorMsg(this->getErrorMsg());
    toReturn->setStatus(this->getStatus());
}



///WATCH
Watch::Watch(long contentId):contentId(contentId) {} //not finish
string Watch::toString() const {
    if(getStatus()==COMPLETED)
        return "Watch COMPLETED";
    else if(getStatus()==ERROR) return "Watch ERROR: "+getErrorMsg();
}
void Watch::act(Session &sess) {//need to complete
    vector<Watchable *> currContent = sess.getContent();
    if (contentId <= currContent.size() && contentId > 0) {
        cout << "Watching " + currContent[contentId - 1]->toString() << endl;
        sess.getActiveUser().addToHistory(currContent[contentId-1]);
        complete();
        Watchable *rec=currContent[contentId-1]->getNextWatchable(sess);
        if(rec!=nullptr){
            string answer;
            cout<<"We recommend watching "+rec->toString()+", continue watching? [y/n]"<<endl;
            cin>>answer;
            if(answer=="y"){
                BaseAction *execute=new Watch(rec->getId()+1);
                sess.getActionLog().push_back(execute);
                execute->act(sess);
            }
            else if(answer=="n"){}
        }
    }
    else{error("Content id not valid.");}

}
BaseAction* Watch::clone(){
   Watch *toReturn=new Watch(this->contentId);
    toReturn->setErrorMsg(this->getErrorMsg());
    toReturn->setStatus(this->getStatus());
}


///PRINT ACTION LOG
PrintActionsLog::PrintActionsLog(){}
void PrintActionsLog::act(Session& sess){ //not finish
    for(int i=sess.getActionLog().size()-1;i>=0;--i)
        cout<<sess.getActionLog()[i]->toString()<<endl;
    complete();

}
std::string PrintActionsLog::toString() const{
    if(getStatus()==COMPLETED)
        return "PrintActionLog COMPLETED";
    else if(getStatus()==ERROR) return "PrintActionLog ERROR: "+getErrorMsg();
}
BaseAction* PrintActionsLog::clone(){
    PrintActionsLog *toReturn=new PrintActionsLog();
    toReturn->setErrorMsg(this->getErrorMsg());
    toReturn->setStatus(this->getStatus());
}


///EXIT
Exit::Exit(){}
void Exit::act(Session& sess){
    complete();
}
std::string Exit::toString() const{
    if(getStatus()==COMPLETED)
        return "Exit COMPLETED";
    else if(getStatus()==ERROR) return "Exit ERROR: "+getErrorMsg();
}
BaseAction* Exit::clone(){
    Exit* toReturn=new Exit();
    toReturn->setErrorMsg(this->getErrorMsg());
    toReturn->setStatus(this->getStatus());
}

