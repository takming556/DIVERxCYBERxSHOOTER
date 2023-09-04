//#include <iostream>
//#include <fstream>
//#include <sstream>
//#include <string>
//#include "SQLConfig.h"
//
//using std::getline;
//using std::ifstream;
//
//string const SQLConfig::FILENAME_HOST("config/host.txt");
//string const SQLConfig::FILENAME_USER("config/user.txt");
//string const SQLConfig::FILENAME_PASSWORD("config/password.txt");
//string const SQLConfig::FILENAME_DATABASE("config/database.txt");
//string const SQLConfig::FILENAME_DEVICE("config/device.txt");
//string const SQLConfig::FILENAME_TABLE("config/table.txt");
//string const SQLConfig::FILENAME_PORT("config/port.txt");
//string const SQLConfig::FILENAME_LOG("LogSQL.txt");
//
//string SQLConfig::HOST;
//string SQLConfig::USER;
//string SQLConfig::PASSWORD;
//string SQLConfig::DATABASE;
//string SQLConfig::DEVICE;
//string SQLConfig::TABLE;
//string SQLConfig::PORT;
//
//void SQLConfig::INITIALIZE(){
//	ifstream fs_host;
//	ifstream fs_user;
//	ifstream fs_password;
//	ifstream fs_database;
//	ifstream fs_device;
//	ifstream fs_table;
//	ifstream fs_port;
//
//	fs_host.open(FILENAME_HOST, std::ios::in);
//	fs_user.open(FILENAME_USER, std::ios::in);
//	fs_password.open(FILENAME_PASSWORD, std::ios::in);
//	fs_database.open(FILENAME_DATABASE, std::ios::in);
//	fs_device.open(FILENAME_DEVICE, std::ios::in);
//	fs_table.open(FILENAME_TABLE, std::ios::in);
//	fs_port.open(FILENAME_PORT, std::ios::in);
//
//	getline(fs_host, HOST);
//	getline(fs_user, USER);
//	getline(fs_password, PASSWORD);
//	getline(fs_database, DATABASE);
//	getline(fs_device, DEVICE);
//	getline(fs_table, TABLE);
//	getline(fs_port, PORT);
//
//	fs_host.close();
//	fs_user.close();
//	fs_password.close();
//	fs_database.close();
//	fs_device.close();
//	fs_table.close();
//	fs_port.close();
//}