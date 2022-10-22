//#include <memory>
//#include "DxLib.h"
//#include "class.h"
//
//
//using std::make_unique;
//
//
//StraightSimpleRadiation::StraightSimpleRadiation
//(
//	double emit_pos_x,
//	double emit_pos_y,
//	unsigned int emit_amount,
//	double given_speed,
//	unsigned int given_collidant_size,
//	unsigned int given_durability,
//	enum TeamID given_team_id,
//	enum SkinID given_skin_id
//) :
//	SimpleRadiation(emit_pos_x, emit_pos_y, emit_amount),
//	team_id(given_team_id),
//	giving_speed(given_speed),
//	giving_collidant_size(given_collidant_size),
//	giving_durability(given_durability),
//	giving_skin_id(given_skin_id)
//{
//}
//
//
//void StraightSimpleRadiation::perform() {
//	for (int i = 0; i < amount; i++) {
//		double arg = 2 * pi / amount * i;
//
//		if (team_id == TeamID::MY) {
//			Field::MY_OFFENSIVES->push_back(make_unique<StraightShot>(x, y, arg, giving_speed, giving_collidant_size, giving_durability, giving_skin_id));
//		}
//		else if (team_id == TeamID::ENEMY) {
//			Field::ENEMY_OFFENSIVES->push_back(make_unique<StraightShot>(x, y, arg, giving_speed, giving_collidant_size, giving_durability, giving_skin_id));
//		}
//	}
//}