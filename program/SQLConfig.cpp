//#include <iostream>
//#include <fstream>
//#include <sstream>
//#include <string>
//#include "SQLConfig.h"
//
//using std::getline;
//using std::ifstream;
//
//wstring const SQLConfig::FILENAME_HOST("config/host.txt");
//wstring const SQLConfig::FILENAME_USER("config/user.txt");
//wstring const SQLConfig::FILENAME_PASSWORD("config/password.txt");
//wstring const SQLConfig::FILENAME_DATABASE("config/database.txt");
//wstring const SQLConfig::FILENAME_DEVICE("config/device.txt");
//wstring const SQLConfig::FILENAME_TABLE("config/table.txt");
//wstring const SQLConfig::FILENAME_PORT("config/port.txt");
//wstring const SQLConfig::FILENAME_LOG("LogSQL.txt");
//
//wstring SQLConfig::HOST;
//wstring SQLConfig::USER;
//wstring SQLConfig::PASSWORD;
//wstring SQLConfig::DATABASE;
//wstring SQLConfig::DEVICE;
//wstring SQLConfig::TABLE;
//wstring SQLConfig::PORT;
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