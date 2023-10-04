#include <fstream>
#include <string>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <DxLib.h>
#include "GameConductor.h"
#include "enum.h"
#include "Scenario/Stage1.h"
#include "Scenario/Stage2.h"
#include "Scenario/Stage3.h"
#include "Character/EnemyCharacter/BossCharacter/Mofu.h"
#include "Character/EnemyCharacter/BossCharacter/Neon.h"
#include "Character/EnemyCharacter/BossCharacter/Toroi.h"
#include "time.h"
#include "ResultOutput.h"
#include "Field.h"
//#include "Character/MyCharacter/MyCharacter.h"

using std::string;
using namespace std;
using std::max;

void ResultOutput::RESULT_OUTPUT() {
	std::ofstream writing_file;
	string filename = "ResultLog.txt";
	writing_file.open(filename, std::ios::app);

	string text = GET_RESULT_DATA();

	writing_file << text << std::endl;

	writing_file.close();
}

string ResultOutput::GET_RESULT_DATA() {
	string date = GET_DATE_STR();		// string?^??N???????ï
	string score = to_string(GameConductor::SCORE);		// ?X?R?A??string?^????
	string remain_hp = to_string(Field::MY_CHARACTER->hp);
	string progress = GET_PROGRESS_STR();
	
	string s_result = date + "," + score + "," + remain_hp + "," + progress;	//????????e?L?X?g???????
	
	return s_result;
}

string ResultOutput::GET_DATE_STR() {

	DATEDATA Date;
	GetDateTime(&Date);
	
	string s_year = to_string(Date.Year);
	string s_mon = to_string(Date.Mon);
	string s_day = to_string(Date.Day);

	s_mon = std::string(max(0, 2 - (int)s_mon.size()), '0') + s_mon;	//Mon??Day??2????0?l??
	s_day = std::string(max(0, 2 - (int)s_day.size()), '0') + s_day;

	string s_date = s_year + s_mon + s_day;

	return s_date;
}

string ResultOutput::GET_PROGRESS_STR() {
	string p;
	switch (GameConductor::NOW_STAGE)
	{
	case Stage::STAGE1:
		p = "Stage1";
		switch (Stage1::PROGRESS)
		{
		case Stage1Progress::START:
			p += "START";
			break;
		case Stage1Progress::A_LEFT_1:
			p += "A_LEFT1";
			break;
		case Stage1Progress::A_LEFT_2:
			p += "A_LEFT2";
			break;
		case Stage1Progress::A_LEFT_3:
			p += "A_LEFT3";
			break;
		case Stage1Progress::A_RIGHT_1:
			p += "A_RIGHT_1";
			break;
		case Stage1Progress::A_RIGHT_2:
			p += "A_RIGHT_2";
			break;
		case Stage1Progress::A_RIGHT_3:
			p += "A_RIGHT_3";
			break;
		case Stage1Progress::B1:
			p += "B1";
			break;
		case Stage1Progress::B2:
			p += "B2";
			break;
		case Stage1Progress::C:
			p += "C";
			break;
		case Stage1Progress::D1:
			p += "D1";
			break;
		case Stage1Progress::D2:
			p += "D2";
			break;
		case Stage1Progress::D3:
			p += "D3";
			break;
		case Stage1Progress::D4:
			p += "D4";
			break;
		case Stage1Progress::E:
			p += "E";
			break;
		case Stage1Progress::MOFU:
			p += "MOFU";
			//Mofu.cpp?????o
			switch (Mofu::STATUS)
			{
			case MofuStatus::NORMAL1:
				p += "NORMAL1";
				break;
			case MofuStatus::SP1:
				p += "SP1";
				break;
			case MofuStatus::NORMAL2:
				p += "NORMAL2";
				break;
			case MofuStatus::SP2:
				p += "SP2";
				break;
			case MofuStatus::NORMAL3:
				p += "NORMAL3";
				break;
			case MofuStatus::SP3:
				p += "SP3";
				break;
			case MofuStatus::FINISH:
				p += "FINISH";
				break;
			}
			break;
		case Stage1Progress::FINISH:
			p += "FINISH";
			break;
		}
		break;
	case Stage::STAGE2:
		p = "Stage2";
		switch (Stage2::PROGRESS)
		{
		case Stage2Progress::WAVE1:
			p += "WAVE1";
			break;
		case Stage2Progress::WAVE2:
			p += "WAVE2";
			break;
		case Stage2Progress::WAVE3:
			p += "WAVE3";
			break;
		case Stage2Progress::WAVE4:
			p += "WAVE4";
			break;
		case Stage2Progress::WAVE5:
			p += "WAVE5";
			break;
		case Stage2Progress::WAVE6:
			p += "WAVE6";
			break;
		case Stage2Progress::WAVE7:
			p += "WAVE7";
			break;
		case Stage2Progress::WAVE8:
			p += "WAVE8";
			break;
		case Stage2Progress::BOSS:
			p += "BOSS";
			switch (Neon::STATUS)
			{
			case NeonStatus::NORMAL1:
				p += "NORMAL1";
				break;
			case NeonStatus::SP1:
				p += "SP1";
				break;
			case NeonStatus::NORMAL2:
				p += "NORMAL2";
				break;
			case NeonStatus::SP2:
				p += "SP2";
				break;
			case NeonStatus::NORMAL3:
				p += "NORMAL3";
				break;
			case NeonStatus::SP3:
				p += "SP3";
				break;
			case NeonStatus::NORMAL4:
				p += "NORMAL4";
				break;
			case NeonStatus::SP4:
				p += "SP4";
				break;

			}
			break;
		case Stage2Progress::END:
			p += "END";
			break;
		}
	case Stage::STAGE3:
		p = "Stage3";
		switch (Stage3::PROGRESS)
		{
		case Stage3Progress::WAVE1:
			p += "WAVE1";
			break;
		case Stage3Progress::WAVE2:
			p += "WAVE2";
			break;
		case Stage3Progress::WAVE3:
			p += "WAVE3";
			break;
		case Stage3Progress::WAVE4:
			p += "WAVE4";
			break;
		case Stage3Progress::WAVE5:
			p += "WAVE5";
			break;
		case Stage3Progress::WAVE6:
			p += "WAVE6";
			break;
		case Stage3Progress::BOSS:
			p += "BOSS";
			switch (Toroi::STATUS)
			{
			case ToroiStatus::NORMAL1:
				p += "NORMAL1";
				break;
			case ToroiStatus::SP1:
				p += "SP1";
				break;
			case ToroiStatus::NORMAL2:
				p += "NORMAL2";
				break;
			case ToroiStatus::SP2:
				p += "SP2";
				break;
			case ToroiStatus::SP3:
				p += "SP3";
				break;
			case ToroiStatus::NORMAL3:
				p += "NORMAL3";
				break;
			case ToroiStatus::SP4:
				p += "SP4";
				break;
			case ToroiStatus::SP5:
				p += "SP5";
				break;
			case ToroiStatus::NORMAL4:
				p += "NORMAL4";
				break;
			case ToroiStatus::SP6:
				p += "SP6";
				break;
			case ToroiStatus::SP7:
				p += "SP7";
				break;
			}
			break;
		}
		break;
	}
	return p;
}