#pragma once
#include <string>

using std::string;

class SQLConfig {
private:
	SQLConfig() {}
public:
	static void INITIALIZE();

	static const string FILENAME_HOST;
	static const string FILENAME_USER;
	static const string FILENAME_PASSWORD;
	static const string FILENAME_DATABASE;
	static const string FILENAME_DEVICE;
	static const string FILENAME_TABLE;
	static const string FILENAME_PORT;
	static const string FILENAME_LOG;


	static string HOST;
	static string USER;
	static string PASSWORD;
	static string DATABASE;
	static string DEVICE;
	static string TABLE;
	static string PORT;
};
