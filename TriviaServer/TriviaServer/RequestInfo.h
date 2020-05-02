#pragma once
#include <ctime>
#include <vector>
#include "json.hpp"

using std::vector;
class RequestInfo
{
public:
	//----------------------constructors------------------
	RequestInfo(int id, time_t time, vector<unsigned char> buff);
	RequestInfo(nlohmann::json j);
	//---------------------getters------------------------
	int getId();
	time_t getTime();
	vector<unsigned char> getBuffer();
protected:
	int _id;
	time_t _receivalTime;
	vector<unsigned char> _buffer;

	
};