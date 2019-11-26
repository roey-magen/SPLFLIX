#ifndef WATCHABLE_H_
#define WATCHABLE_H_

#include <string>
#include <vector>


class Session;

class Watchable{// MOVIE OR EPISODE. ABSTRACT CLASS
public:
    Watchable(long id, int length, const std::vector<std::string>& tags);//constructor.
    Watchable(const Watchable & other);
    virtual ~Watchable();//destructor
    virtual std::string toString() const = 0;//abstract, only string of name
    virtual std::string fullToString() const=0; //string include: name, seasion/episode(if episode),leangth' tags
    virtual Watchable* getNextWatchable(Session&) const = 0;//abstract.
    virtual void setNextId( long id )=0;//our addition
    virtual Watchable* clone()=0;
    virtual std::string getName() const =0;
    const long getId() const;//out addition.
    const int getLength() const;//our addition.
    const std::vector<std::string> getTags() const;//our addition
    bool containsTag(const  std::string& s);//our addition
protected:
private:
    const long id;
    int length;
    std::vector<std::string> tags;
};

class Movie : public Watchable{
public:
    virtual std::string getName() const;//our addition.
    Movie(const Watchable & other);
    Movie(long id, const std::string& name, int length, const std::vector<std::string>& tags);//constructor.
    virtual std::string toString() const;
    virtual std::string fullToString() const;
    virtual Watchable* getNextWatchable(Session&) const;//get the next recommondation according to the user algorithm. (return null if not exist)
    virtual void setNextId( long id );//our addition
    virtual Watchable* clone();
private:
    std::string name;
};


class Episode: public Watchable{
public:
    virtual std::string getName() const;
    Episode(const Watchable & other);
    Episode(long id, const std::string& seriesName,int length, int season, int episode ,const std::vector<std::string>& tags);//constructor.
    virtual std::string toString() const;
    virtual std::string fullToString() const;
    virtual Watchable* getNextWatchable(Session&) const;//get the next rec.
    virtual void setNextId( long id );//our addition
    virtual Watchable* clone();
//high chance we dont need destructor.
private:
    std::string seriesName;
    int season;
    int episode;
    long nextEpisodeId;
};

#endif
