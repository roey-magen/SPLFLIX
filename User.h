#ifndef USER_H_
#define USER_H_

#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <map>
class Watchable;
class Session;

class LengthRecommenderUser;

class User{//ABSTRACT CLASS
public:
    User(const std::string& name);//constructor.
    virtual~User();
    virtual Watchable* getRecommendation(Session& s) = 0;//abstract.
    virtual User* clone()=0;
    void addToHistory(Watchable* toAdd);
    void printHistory();
    void setName(const std::string& name);
    std::vector<Watchable*> get_history() ;
    std::vector<Watchable*> &getHistoryByRef() ;
    std::string getName() const;


protected:
    std::vector<Watchable*> history;
    bool userDidntWatch(Watchable* & content);
private:
     std::string name;

};

class LengthRecommenderUser : public User {//prefer to watch content whose length is closest to the avg length of all the things he watched so far.
public:
    LengthRecommenderUser(const std::string& name);//constructor.
    virtual Watchable* getRecommendation(Session& s);// holds the next recommendation.
    virtual User* clone();
private:
};

class RerunRecommenderUser : public User {//recommned by cycle: first recommend the first WATCHABLE, then second, third..... n.(saves the index of the last recomandation) 
public:
    RerunRecommenderUser(const std::string& name);//constructor.
    virtual Watchable* getRecommendation(Session& s);// holds the next recommendation.
    virtual User* clone();
private:
    int index_of_next_recommendation;//our addition
};

class GenreRecommenderUser : public User {//recommend contect based on the most popular tag in the user WATCH HISTORY. if a set of tags has the same value, it will recommand by lex order. recommand on content that the user didnt watch already. If no such content exists, it will try with the second most popular tag, and so on.
public:
    GenreRecommenderUser(const std::string& name);//constructor.
    virtual Watchable* getRecommendation(Session& s);// holds the next recommendation.
    virtual User* clone();
    std::map<std::string,int>* initTagMap();//our addition.
    std::string findTagToSearch(std::map<std::string,int>*& mymap);//our addition.
private:

};
#endif
