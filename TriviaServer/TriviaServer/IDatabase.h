#pragma once
#include <string>

using std::string;

class IDatabase
{
public:
	virtual bool doesUserExist(string username) = 0;
	virtual bool doesPasswordMatch(string password) = 0;
	virtual void addNewUser(string username, string password, string email) = 0;
};
