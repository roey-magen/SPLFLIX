#include <iostream>
#include "Session.h"
#include "Watchable.h"

using namespace std;
#include <json.hpp>
using json = nlohmann::json;
class Movie;
class Episode;
class Watchable;
int main(int argc, char** argv){
//	if(argc!=2)
//	{
//		cout << "usage splflix input_file" << endl;
//		return 0;
//	}
//	Session s(argv[1]);
//	s.start();

    return 0;
}
//
//void buildDataBase(const string& path, vector<Watchable*> & content) {
//    std::ifstream i("/home/tzach/CLionProjects/projectA/untitled/config1.json");///change to path later.
//    if(!i){///need to check what to do if failed to load file.(maybe remove at the end)
//        std::cout <<"failed";
//    }
//    json j;
//    i>>j;
//    ///finish reading file here
//    long index = 0;
//    for (auto it:j["movies"]) {
//        string movie_name = it["name"].get<std::string>();
//        int movie_length = it["length"];
//        vector<string> tags;
//        for (auto tag:it["tags"])
//            tags.push_back(tag.get<std::string>());
//        Watchable *movie = new Movie(index, movie_name, movie_length, tags);//check if we need to free this.
//        index++;
//        content.push_back(movie);
//    }
//    for (auto it:j["tv_series"]) {
//        string series_name = it["name"].get<std::string>();
//        int series_length = it["episode_length"];
//        vector<string> tags;
//        for (auto tag:it["tags"])
//            tags.push_back(tag.get<std::string>());
//        int season_number = 0;
//        for (auto season:it["seasons"]) {
//            season_number++;
//            int episode_number = 1;
//            while (season.get<std::int8_t>() != 0) {//need to check it reads!
//                Watchable *episode = new Episode(index, series_name, series_length, season_number, episode_number,
//                                                 tags);//check if we need to free.
//                content.push_back(episode);
//                index++;
//                episode_number++;
//            }
//
//        }
//
//    }
//}