#pragma once
#include "IDatabase.h"
#include "sqlite3.h"
#include <io.h>
#include <exception>

using std::exception;

class SqliteDataBase : IDatabase
{
public:
	SqliteDataBase();
	~SqliteDataBase();
	virtual bool doesUserExist(string username, string password) throw();
	void addNewUser(string username, string password, string email) override;

private:
	const string DB_NAME = "OurDB.sqlite.db";
	sqlite3* _dataBase;

	void executeCommand(const char* statement, int (*callback)(void*, int, char**, char**), void* arg) throw();
	static int callbackCheckExistence(void* data, int argc, char** argv, char** azColName);
};
