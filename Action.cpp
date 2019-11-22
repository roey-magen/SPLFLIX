#include "Action.h"
using namespace std;

BaseAction::BaseAction():errorMsg("ERROR"), status(ERROR){}


void BaseAction::complete() {
    status = ActionStatus::COMPLETED;
}

void BaseAction::error(const std::string &errorMsg)  {
    status = ActionStatus::ERROR;
    this->errorMsg=errorMsg;
}


