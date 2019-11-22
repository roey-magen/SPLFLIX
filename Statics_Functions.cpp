//
// Created by tzachu@wincs.cs.bgu.ac.il on 22/11/2019.
//

#include "Statics_Functions.h"
using namespace std;


string Statics_Functions::vector_to_string(vector<string> & vec) {
    string Tags="[";
    for(auto i = vec.begin(); i!=vec.end();++i)//create string from the tags vector
        Tags+= *i+", ";
    Tags=Tags.substr(0, Tags.size()-1);
    Tags.at(Tags.size()-1)=']';
    return Tags;
}
