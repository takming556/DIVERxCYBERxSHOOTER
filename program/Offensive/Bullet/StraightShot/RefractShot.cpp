#include <cmath>
#include <numbers>
#include "DxLib.h"
#include "enum.h"
#include "Field.h"
#include "Character/Character.h"
#include "Character/EnemyCharacter/EnemyCharacter.h"
#include "ImageHandles.h"
#include "DebugParams.h"
#include "Position/InFieldPosition.h"
#include "Offensive/Bullet/StraightShot/RefractShot.h"

using std::sin;
using std::cos;
using std::numbers::pi;

RefractShot::RefractShot(
	double init_pos_x ,
	double init_pos_y ,
	double init_arg ,
	double init_speed ,
	unsigned int collidant_size ,
	unsigned int durability ,
	SkinID given_skin_id
) :
	Offensive(given_skin_id) ,
	Bullet(init_pos_x , init_pos_y , init_arg , init_speed , durability , collidant_size)
{
}

void RefractShot::update() {

	/*bool zk_1_crash_flag = ( *Field::DEAD_FLAGS )[ CharacterID::ZKCHRSTG2BSNM4_1 ];
	bool zk_2_crash_flag = ( *Field::DEAD_FLAGS )[ CharacterID::ZKCHRSTG2BSNM4_2 ];
	bool zk_3_crash_flag = ( *Field::DEAD_FLAGS )[ CharacterID::ZKCHRSTG2BSNM4_3 ];
	bool zk_4_crash_flag = ( *Field::DEAD_FLAGS )[ CharacterID::ZKCHRSTG2BSNM4_4 ];
	bool zk_5_crash_flag = ( *Field::DEAD_FLAGS )[ CharacterID::ZKCHRSTG2BSNM4_5 ];*/

	bool zk_1_existed_flag = Field::IS_THERE(CharacterID::ZKCHRSTG2BSNM4_1);
	bool zk_2_existed_flag = Field::IS_THERE(CharacterID::ZKCHRSTG2BSNM4_2);
	bool zk_3_existed_flag = Field::IS_THERE(CharacterID::ZKCHRSTG2BSNM4_3);
	bool zk_4_existed_flag = Field::IS_THERE(CharacterID::ZKCHRSTG2BSNM4_4);
	bool zk_5_existed_flag = Field::IS_THERE(CharacterID::ZKCHRSTG2BSNM4_5);

	if ( zk_1_existed_flag == true) {
		EnemyCharacter& zako1 = *Field::GET_ENEMY_CHARACTER(CharacterID::ZKCHRSTG2BSNM4_1);
		bool zk_1_is_collided_with_detected = collidant->is_collided_with(zako1.collidant);

		if ( zk_1_is_collided_with_detected == true ) {
			if ( position->x >= zako1.position->x ) {
				arg += 4.0 / 9.0 * pi;
			}
			else if ( position->x < zako1.position->x ) {
				arg -= 4.0 / 9.0 * pi;
			}
		}
	}
	if ( zk_2_existed_flag == true ) {
		EnemyCharacter& zako2 = *Field::GET_ENEMY_CHARACTER(CharacterID::ZKCHRSTG2BSNM4_2);
		bool zk_2_is_collided_with_detected = collidant->is_collided_with(zako2.collidant);

		if ( zk_2_is_collided_with_detected == true) {
			if ( position->x >= zako2.position->x ) {
				arg += 4.0 / 9.0 * pi;
			}
			else if ( position->x < zako2.position->x ) {
				arg -= 4.0 / 9.0 * pi;
			}
		}
	}
	if ( zk_3_existed_flag == true ) {
		EnemyCharacter& zako3 = *Field::GET_ENEMY_CHARACTER(CharacterID::ZKCHRSTG2BSNM4_3);
		bool zk_3_is_collided_with_detected = collidant->is_collided_with(zako3.collidant);

		if (zk_3_is_collided_with_detected == true ) {
			if ( position->x >= zako3.position->x ) {
				arg += 4.0 / 9.0 * pi;
			}
			else if ( position->x < zako3.position->x ) {
				arg -= 4.0 / 9.0 * pi;
			}
		}
	}
	if ( zk_4_existed_flag == true ) {
		EnemyCharacter& zako4 = *Field::GET_ENEMY_CHARACTER(CharacterID::ZKCHRSTG2BSNM4_4);
		bool zk_4_is_collided_with_detected = collidant->is_collided_with(zako4.collidant);

		if (zk_4_is_collided_with_detected == true ) {
			if ( position->x >= zako4.position->x ) {
				arg += 4.0 / 9.0 * pi;
			}
			else if ( position->x < zako4.position->x ) {
				arg -= 4.0 / 9.0 * pi;
			}
		}
	}
	if ( zk_5_existed_flag == true ) {
		EnemyCharacter& zako5 = *Field::GET_ENEMY_CHARACTER(CharacterID::ZKCHRSTG2BSNM4_5);
		bool zk_5_is_collided_with_detected = collidant->is_collided_with(zako5.collidant);

		if (zk_5_is_collided_with_detected == true ) {
			if ( position->x >= zako5.position->x ) {
				arg += 4.0 / 9.0 * pi;
			}
			else if ( position->x < zako5.position->x ) {
				arg -= 4.0 / 9.0 * pi;
			}
		}
	}

	LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;
	double distance = speed * update_delta_time / 1000 / 1000;
	double distance_x = distance * cos(arg);
	double distance_y = distance * sin(arg);
	position->x += distance_x;
	position->y += distance_y;
	last_updated_clock = DxLib::GetNowHiPerformanceCount();

	collidant->update(position);
}

void RefractShot::draw() {
	int delta_time_frame_update = DxLib::GetNowCount() - last_frame_updated_clock;
	Position draw_pos = position->get_draw_position();

	switch ( skin_id ){
	case SkinID::NEON_NM4_CRYSTAL_RED:
		DxLib::DrawRotaGraph(draw_pos.x , draw_pos.y , 0.75 , -arg , ImageHandles::CRYSTAL_RED , TRUE);
		break;

	case SkinID::NEON_NM4_CRYSTAL_BLUE:
		DxLib::DrawRotaGraph(draw_pos.x , draw_pos.y , 0.75 , -arg , ImageHandles::CRYSTAL_BLUE , TRUE);
		break;
	}

	if ( DebugParams::DEBUG_FLAG == true ) collidant->draw();
}