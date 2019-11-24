#ifndef WATCHABLE_H_
#define WATCHABLE_H_

#include <string>
#include <vector>


class Session;

class Watchable{// MOVIE OR EPISODE. ABSTRACT CLASS
public:
    Watchable(long id, int length, const std::vector<std::string>& tags);//constructor.
    virtual ~Watchable();//destructor
    virtual std::string toString() const = 0;//abstract, only string of name
    virtual std::string fullToString() const=0; //string include: name, seasion/episode(if episode),leangth' tags
    virtual Watchable* getNextWatchable(Session&) const = 0;//abstract.
    const long getId() const;//out addition.
    const int getLength() const;//our addition.
protected:
    const std::vector<std::string> getTags() const;//our addition
private:
    const long id;
    int length;
    std::vector<std::string> tags;
};

class Movie : public Watchable{
public:
    Movie(long id, const std::string& name, int length, const std::vector<std::string>& tags);//constructor.
    virtual std::string toString() const;
    virtual std::string fullToString() const;
    virtual Watchable* getNextWatchable(Session&) const;//get the next recommondation according to the user algorithm. (return null if not exist)
private:
    std::string name;
};


class Episode: public Watchable{
public:
    Episode(long id, const std::string& seriesName,int length, int season, int episode ,const std::vector<std::string>& tags);//constructor.
    virtual std::string toString() const;
    virtual std::string fullToString() const;
    virtual Watchable* getNextWatchable(Session&) const;//get the next rec.

//high chance we dont need destructor.
private:
    std::string seriesName;
    int season;
    int episode;
    long nextEpisodeId;
};

#endif
