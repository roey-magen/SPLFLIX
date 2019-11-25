//
// Created by tzachu@wincs.cs.bgu.ac.il on 22/11/2019.
//
#include <iostream>
#include <json.hpp>
#include <fstream>
#include "Statics_Functions.h"
#include "Watchable.h"
using namespace std;
using json = nlohmann::json;
class Watchable;
class Movie;
class Episode;

string Statics_Functions::vector_to_string(vector<string> & vec) {
    string Tags="[";
    for(auto i = vec.begin(); i!=vec.end();++i)//create string from the tags vector
        Tags+= *i+", ";
    Tags=Tags.substr(0, Tags.size()-1);
    Tags.at(Tags.size()-1)=']';
    return Tags;
}
void Statics_Functions::buildDataBase(const string& path, vector<Watchable*> & content) {
    ifstream i("/home/tzach/CLionProjects/projectA/untitled/config1.json");///change to path later.
    if(!i){///need to check what to do if failed to load file.(maybe remove at the end)
        std::cout <<"Failed to open Json file. Please check the file path.";
    }
    json j;
    i>>j;
    ///finish reading file here
    long index = 0;
    for (auto it:j["movies"]) {
        string movie_name = it["name"].get<std::string>();
        int movie_length = it["length"];
        vector<string> tags;
        for (auto tag:it["tags"])
            tags.push_back(tag.get<std::string>());
        Watchable *movie = new Movie(index, movie_name, movie_length, tags);//check if we need to free this.
        index++;
        content.push_back(movie);
    }
    for (auto it:j["tv_series"]) {
        string series_name = it["name"].get<std::string>();
        int series_length = it["episode_length"];
        vector<string> tags;
        for (auto tag:it["tags"])
            tags.push_back(tag.get<std::string>());
        int season_number = 0;
        for (auto season:it["seasons"]) {
            season_number++;
            int episode_number = 1;
            while (season.get<std::int8_t>() != 0) {//need to check it reads!
                Watchable *episode = new Episode(index, series_name, series_length, season_number, episode_number,
                                                 tags);//check if we need to free.
                content.push_back(episode);
                index++;
                episode_number++;
            }

        }

    }
}
