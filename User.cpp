//
// Created by tzachu@wincs.cs.bgu.ac.il on 22/11/2019.
//
#include "User.h"
#include "Session.h"
#include "Watchable.h"
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
GenreRecommenderUser::GenreRecommenderUser (const std::string& name):User(name){
}
//Watchable* GenreRecommenderUser::getRecommendation(Session &s) {}
    //most popular tag:


             //return a movie from content that not in history.
   //try next popular tag.
   //order map, multy map
   //sort algorithm:
