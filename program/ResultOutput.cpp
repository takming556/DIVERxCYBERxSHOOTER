#include <fstream>
#include <string>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <DxLib.h>
#include "GameConductor.h"
#include "time.h"
#include "ResultOutput.h"
#include "Field.h"
//#include "Character/MyCharacter/MyCharacter.h"

using std::string;
using namespace std;
using std::max;

void ResultOutput::RESULT_OUTPUT() {
	std::ofstream writing_file;
	string filename = "result_log.txt";
	writing_file.open(filename, std::ios::app);

	string text = GET_RESULT_DATA();

	writing_file << text << std::endl;

	writing_file.close();
}

string ResultOutput::GET_RESULT_DATA() {
	string date = GET_DATE_STR();		// string型で年月日を取得

	// score, remain_hp, progressをココで取得したい
	string score = to_string(GameConductor::SCORE);		// スコアをstring型に変換
	string remain_hp = to_string(Field::MY_CHARACTER->hp);
	
	string stage = "";
	string progress = "";

	switch (GameConductor::NOW_STAGE)
	{
	case Stage::STAGE1:
		stage = "Stage1";
		//progressの場合分け(クソ長予定)
		break;
	case Stage::STAGE2:
		stage = "Stage2";
		//progressの場合分け(クソ長予定)
		break;
	case Stage::STAGE3:
		stage = "Stage3";
		//progressの場合分け(クソ長予定)
		break;
	}
	

	//書き込むテキストをまとめる
	string s_result = date + ","
		+ score + ","
		+ remain_hp + ","
		+ stage + ","
		+ progress;

	// 取得するところをget_result_data()とかでまとめたい
	// 文字列の連結まで
	// 戻り値をs_resultの1つのみにする
	
	return s_result;
}

string ResultOutput::GET_DATE_STR() {

		//time_t t = time(nullptr);
		//const tm* localTime = localtime(&t);
		//std::stringstream s;
		//s << localTime->tm_year + 1900;
		//// setw(),setfill()で0詰め
		//s << setw(2) << setfill('0') << localTime->tm_mon + 1;
		//s << setw(2) << setfill('0') << localTime->tm_mday;
		//s << setw(2) << setfill('0') << localTime->tm_hour;
		//s << setw(2) << setfill('0') << localTime->tm_min;
		//s << setw(2) << setfill('0') << localTime->tm_sec;
		//// std::stringにして値を返す
		//return s.str();

	// 年月日を取得
	/*time_t t = time(NULL);
	struct tm* local = localtime(&t);
	time_t t_year = local->tm_year + 1900;
	time_t t_mon = local->tm_mon + 1;
	time_t t_mday = local->tm_mday;*/

	// time_t型からstring型へ変換 
	/*string s_year = ctime(&t_year);
	string s_mon = ctime(&t_mon);
	string s_mday = ctime(&t_mday);
	string s_date = s_year + s_mon + s_mday;*/

	DATEDATA Date;
	
	GetDateTime(&Date);
	
	string s_year = to_string(Date.Year);
	string s_mon = to_string(Date.Mon);
	string s_day = to_string(Date.Day);

	//MonとDayを2桁で0詰め
	s_mon = std::string(max(0, 2 - (int)s_mon.size()), '0') + s_mon;
	s_day = std::string(max(0, 2 - (int)s_day.size()), '0') + s_day;

	string s_date = s_year + s_mon + s_day;

	/*printf("%04d/", local->tm_year + 1900);
	printf("%02d/", local->tm_mon + 1);
	printf("%02d", local->tm_mday);*/

	return s_date;
}