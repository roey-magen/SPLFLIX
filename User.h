#ifndef USER_H_
#define USER_H_

#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
class Watchable;
class Session;

class User{//ABSTRACT CLASS
public:
    User(const std::string& name);//constructor.
    virtual Watchable* getRecommendation(Session& s) = 0;//abstract.
    std::string getName() const;
    std::vector<Watchable*> get_history() const;//return history, why not by reference, not our class
    void printHistory();
protected:
    std::vector<Watchable*> history;//vector of all the things the user watched in the past.
private:
    const std::string name;// name of the user.

};

//recomendation algorithms:
//ALL ALGORITHMS:
//if the user watched a movie - recommend by user  recomendation algorithm.
//if the user watched an episode- recommend the next episode, if exists. if not, recommend by user  recomendation algorithm.
class LengthRecommenderUser : public User {//prefer to watch content whose length is closest to the avg length of all the things he watched so far.
public:
    LengthRecommenderUser(const std::string& name);//constructor.
    virtual Watchable* getRecommendation(Session& s);// holds the next recommendation.
private:
};

class RerunRecommenderUser : public User {//recommned by cycle: first recommend the first WATCHABLE, then second, third..... n.(saves the index of the last recomandation) 
public:
    RerunRecommenderUser(const std::string& name);//constructor.
    virtual Watchable* getRecommendation(Session& s);// holds the next recommendation.
private:
    int index_of_next_recommendation;//our addition
};

class GenreRecommenderUser : public User {//recommend contect based on the most popular tag in the user WATCH HISTORY. if a set of tags has the same value, it will recommand by lex order. recommand on content that the user didnt watch already. If no such content exists, it will try with the second most popular tag, and so on.
public:
    GenreRecommenderUser(const std::string& name);//constructor.
    virtual Watchable* getRecommendation(Session& s);// holds the next recommendation.
private:

};
//additional notes:
//-In the case in which there is more than one content which fits the recommendation criteria –for example, two movies whose length is equal to the average content length in theuser’swatching history, the content with the smaller index in the content vector would be picked.
//-If no content fits the recommendation criteria –a null pointer should be returned.
#endif
