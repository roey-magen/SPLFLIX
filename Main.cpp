#include <iostream>
#include "Session.h"
#include "Watchable.h"
#include "Statics_Functions.h"
#include "User.h"
using namespace std;
#include <json.hpp>
using json = nlohmann::json;
class Movie;
class Episode;
class Watchable;

int main(int argc, char** argv) {
    if(argc!=2)
    {
        cout << "usage splflix input_file" << endl;
        return 0;
    }
    Session* s = new Session(argv[1]);
    s->start();
    s->start();
    Session s2 = *s;
    delete(s);
    s2.start();

    return 0;



//    Session s(argv[1]);
//    Session t=s;//works
//    Session* h=new Session(argv[1]);
//    Session f(s);
}


//
