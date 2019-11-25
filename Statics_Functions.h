//
// Created by tzachu@wincs.cs.bgu.ac.il on 22/11/2019.
//

#ifndef SPLFLIX_STATICS_FUNCTIONS_H
#define SPLFLIX_STATICS_FUNCTIONS_H
#include <iostream>
#include <string>
#include <vector>
#include <json.hpp>
#include "Watchable.h"
using json = nlohmann::json;
using namespace std;

class Statics_Functions{
public:
    static string vector_to_string(vector<string> &vec);
    static void buildDataBase(const string& path, vector<Watchable*> & content);


};
#endif //SPLFLIX_STATICS_FUNCTIONS_H
