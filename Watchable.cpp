//
// Created by tzachu@wincs.cs.bgu.ac.il on 22/11/2019.
//

#include "Watchable.h"
#include "Session.h"
#include "User.h"
#include "Statics_Functions.h"
using namespace std;
Watchable::Watchable(long id, int length, const std::vector<std::string> &tags) : id(id), length(length), tags(tags){}
Watchable::~Watchable() {}
const int Watchable::getLength() const{
    return length;
}
const std::vector<std::string> Watchable::getTags() const{
    return tags;
}
const long Watchable::getId() const {
        return id;
}




///MOVIE CLASS
Movie::Movie(long id, const std::string& name, int length, const std::vector<std::string>& tags): Watchable(id,length,tags), name(name) {}
Watchable* Movie::getNextWatchable(Session & s) const{
    return s.getActiveUser().getRecommendation(s);
}
std::string Movie::toString() const{
    vector<string> vector_of_tags=this->getTags();
    string Tags=Statics_Functions::vector_to_string(vector_of_tags);
    return name+" "+to_string(this->getLength())+" Minutes "+Tags;
}



///EPISODE CLASS

Episode::Episode(long id, const std::string &seriesName, int length, int season, int episode,const std::vector<std::string> &tags):
                 Watchable(id,length,tags),seriesName(seriesName),season(season),episode(episode),nextEpisodeId(-1) {}


Watchable* Episode::getNextWatchable(Session & s) const {
    if(nextEpisodeId!=-1){//the last episode of each series is -1.
        return s.getContent()[nextEpisodeId];
    }
    else{//return the recomm.
        return s.getActiveUser().getRecommendation(s);
    }
}
std::string Episode::toString() const{
    vector<string> vector_of_tags=this->getTags();
    string Tags=Statics_Functions::vector_to_string(vector_of_tags);
    if(season<10 && episode<10)
        return seriesName+" S0"+ to_string(season)+"E0"+to_string(episode)+" "+to_string(this->getLength())+" Minutes"+" " +Tags;
    else if(season<10 && episode>9)
        return seriesName+" S0"+ to_string(season)+"E"+to_string(episode)+" "+to_string(this->getLength())+" Minutes"+" " +Tags;
    else if(season>10 && episode<10 )
        return seriesName+" S"+ to_string(season)+"E0"+to_string(episode)+" "+to_string(this->getLength())+" Minutes"+" " +Tags;
    else return seriesName+" S"+ to_string(season)+"E"+to_string(episode)+" "+to_string(this->getLength())+" Minutes"+" " +Tags;
}
