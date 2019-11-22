#include <iostream>
#include "Session.h"
using namespace std;
#include <json.hpp>
#include <fstream>
using json= nlohmann::json;

int main(int argc, char** argv){
//	if(argc!=2)
//	{
//		cout << "usage splflix input_file" << endl;
//		return 0;
//	}
//	Session s(argv[1]);
//	s.start();
std::ifstream i("config1.json");
json j;
j=json::parse(i);
cout<<j;
	return 0;
}
