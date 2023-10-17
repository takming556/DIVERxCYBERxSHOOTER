#include "Offensive/Laser/CartesianLaser/LeidenLaser.h"
#include "Field.h"


const unsigned int LeidenLaser::WIDTH = 5;
const unsigned int LeidenLaser::DPS = 15;


LeidenLaser::LeidenLaser(
	double init_begin_pos_x,
	double init_begin_pos_y,
	double init_end_pos_x,
	double init_end_pos_y
) :
	CartesianLaser(
		init_begin_pos_x,
		init_begin_pos_y,
		init_end_pos_x,
		init_end_pos_y,
		WIDTH,
		DPS,
		true,
		SkinID::NEON_SP3_LASER
	),
	collide_count(0)
{
}


void LeidenLaser::update() {
	vector<InFieldPosition> vertices;
	vertices.push_back(get_vert1_pos());
	vertices.push_back(get_vert2_pos());
	vertices.push_back(get_vert3_pos());
	vertices.push_back(get_vert4_pos());
	collidant->update(vertices);

	if (last_collided_with_mychr_flag == false) {
		if (collidant->is_collided_with(Field::MY_CHARACTER->collidant) == true) {
			last_collided_with_mychr_flag = true;
			++collide_count;
		}
	}
	else {
		if (collidant->is_collided_with(Field::MY_CHARACTER->collidant) == false) {
			last_collided_with_mychr_flag = false;
		}
	}
}