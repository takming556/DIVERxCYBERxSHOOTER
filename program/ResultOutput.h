#pragma once
#include <string>

using std::string;

class ResultOutput {
private:
	//static std::stringstream s;
	string s_year;
public:
	static void RESULT_OUTPUT();
	static string GET_RESULT_DATA();
	static string GET_DATE_STR();

	//string get_result_data();
	//string get_date_str();
};
