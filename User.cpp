//
// Created by tzachu@wincs.cs.bgu.ac.il on 22/11/2019.
//
#include "User.h"
#include "Session.h"
#include "Watchable.h"
#include <map>
using namespace std;
User::User(const string& name):name(name){}
std::string User::getName() const {
    return name;
}
std::vector<Watchable*> User::get_history()  {
    return history;
}

void User::printHistory() {
    int j = 1;
    for (auto i = history.begin(); i != history.end(); ++i){ //create string from the tags vector
        cout << to_string(j) + ". " + (*i)->toString() << endl;
    j++;
}
}










///CLASS LengthRecommenderUser
LengthRecommenderUser::LengthRecommenderUser(const std::string& name):User(name){}
Watchable* LengthRecommenderUser::getRecommendation(Session &s) {
    if(s.getContent().size()<=history.size()) return nullptr;//if the user watched all the avaible content.
    double avg=0;
    int id_closest_to_avg=-1;
    long long min_distance_from_avg= INTMAX_MAX;
    for(auto & it: history)
        avg+=it->getLength();//for the average.
    avg/=history.size();//calculate average.
    for( auto & cont: s.getContent()){
        bool in_history=false;
        for(auto i = history.begin(); i!=history.end() && !(in_history);++i)
            if((*i)->getId()==cont->getId()) in_history=true;
        if(!in_history){
            int distance= abs(avg-cont->getLength());
            if(distance<min_distance_from_avg) {
                min_distance_from_avg = distance;//update new closest.
                id_closest_to_avg=cont->getId();
            }
        }

    }
    return s.getContent()[id_closest_to_avg];
}

///CLASS RerunRecommenderUser
RerunRecommenderUser::RerunRecommenderUser (const std::string& name):User(name){
    index_of_next_recommendation=0;
}
Watchable* RerunRecommenderUser::getRecommendation(Session &s) {
    if(history.size()==0) return nullptr;
    int to_return=index_of_next_recommendation;
    index_of_next_recommendation=(index_of_next_recommendation+1) % history.size();
    return history[to_return];
}

///CLASS GenreRecommenderUser
<<<<<<< HEAD
GenreRecommenderUser::GenreRecommenderUser (const std::string& name):User(name){
}
//Watchable* GenreRecommenderUser::getRecommendation(Session &s) {}
    //most popular tag:
=======
GenreRecommenderUser::GenreRecommenderUser (const std::string& name):User(name){}
std::map<std::string,int>* GenreRecommenderUser::initTagMap(){
    map <string, int>* mymap=new map<string,int>;
    for(auto it : history){//add all the user watch history to the map.
        vector<string> tags= it->getTags();
        for( auto tag: tags){
            if(mymap->count(tag)>0)
                (*mymap)[tag]++;
            else mymap->insert(pair<string,int>(tag,1));
        }
    }
    return mymap;
}
string GenreRecommenderUser::findTagToSearch(std::map<string,int>*& mymap){
    int max=-1;
    for(auto pair: *mymap)
        if(pair.second>max)
            max = pair.second;
    for(auto pair : *mymap)
        if(pair.second==max)
            return  pair.first;
    return nullptr;
}
bool User::userDidntWatch(Watchable* & content){
        for(auto & it:history)
            if(content->toString()==it->toString())
                return false;
        return true;
}
Watchable* GenreRecommenderUser::getRecommendation(Session &s) {
    if (history.size() == s.getContent().size()) return nullptr;//if the user watched all the content availble.
    else {
        //init map- free the map on this function
        map<string, int> *mymap = initTagMap();
        //try to find content to recommend
        while (!mymap->empty()) {
            string tag = findTagToSearch(mymap);
            for (auto cont: s.getContent())
                if (cont->containsTag(tag) && userDidntWatch(cont)) {//if you found content, return it.
                    delete mymap;
                    return cont;
                }
            mymap->erase(tag);
            }
        delete mymap;
        return nullptr;
    }
}



>>>>>>> eb59e3eb50945969f55e9fce1def061def2982c4


