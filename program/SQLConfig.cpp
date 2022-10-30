#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "class.h"

using std::getline;
using std::ifstream;

string const SQLConfig::FILENAME_HOST("config/HOST");
string const SQLConfig::FILENAME_USER("config/USER");
string const SQLConfig::FILENAME_PASSWORD("config/PASSWORD");
string const SQLConfig::FILENAME_DATABASE("config/DATABASE");
string const SQLConfig::FILENAME_LOG("LogSQL.txt");

string SQLConfig::HOST;
string SQLConfig::USER;
string SQLConfig::PASSWORD;
string SQLConfig::DATABASE;

void SQLConfig::INITIALIZE(){
	ifstream fs_host;
	ifstream fs_user;
	ifstream fs_password;
	ifstream fs_database;

	fs_host.open(FILENAME_HOST, std::ios::in);
	fs_user.open(FILENAME_USER, std::ios::in);
	fs_password.open(FILENAME_PASSWORD, std::ios::in);
	fs_database.open(FILENAME_DATABASE, std::ios::in);

	getline(fs_host, HOST);
	getline(fs_user, USER);
	getline(fs_password, PASSWORD);
	getline(fs_database, DATABASE);

	fs_host.close();
	fs_user.close();
	fs_password.close();
	fs_database.close();
}