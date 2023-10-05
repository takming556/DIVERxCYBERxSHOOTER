#pragma once
#include <string>

using std::string;

class ResultOutput {
private:
	string s_year;
public:
	static void RESULT_OUTPUT();
	static string GET_RESULT_DATA();
	static string GET_DATE_STR();
	static string GET_PROGRESS_STR();
};
