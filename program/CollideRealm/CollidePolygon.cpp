#include <cmath>
#include <typeinfo>
#include "DxLib.h"
#include "CollideRealm/CollidePolygon.h"
#include "CollideRealm/CollideCircle.h"
#include "Colors.h"

using std::abs;		// ê‚ëŒílä÷êî

CollidePolygon::CollidePolygon(vector<InFieldPosition>& upd_angle_positions):
	angle_positions(upd_angle_positions)
{
}


bool CollidePolygon::is_collided_with(unique_ptr<CollideRealm>& given_collide_realm) {
	if (typeid(*given_collide_realm) == typeid(CollideCircle)) {
		for (int i = 0; i < angle_positions.size(); ++i) {

			InFieldPosition v_begin = angle_positions.at(i);
			InFieldPosition v_end;
			if (i == angle_positions.size() - 1) {
				v_end = angle_positions.at(0);
			}
			else {
				v_end = angle_positions.at(i + 1);
			}
			InFieldPosition v(v_end.x - v_begin.x, v_end.y - v_end.y);

			unique_ptr<CollideCircle> given_collide_circle(dynamic_cast<CollideCircle*>(given_collide_realm.get()));
			InFieldPosition m_begin = angle_positions.at(i);
			InFieldPosition m_end = *(given_collide_circle->center_pos);
			InFieldPosition m(m_end.x - m_begin.x, m_end.y - m_begin.y);
			
			double dot_v_m = v.x * m.x + v.y * m.y;
			bool A = dot_v_m >= 0;
			
			InFieldPosition m1_begin;
			if (i == angle_positions.size() - 1) {
				m1_begin = angle_positions.at(0);
			}
			else {
				m1_begin = angle_positions.at(i + 1);
			}
			InFieldPosition m1_end = *(given_collide_circle->center_pos);
			InFieldPosition m1(m1_end.x - m1_begin.x, m1_end.y - m1_begin.y);
			double dot_v_m1 = v.x * m1.x + v.y * m1.y;
			bool B = dot_v_m1 <= 0;

			double upper;
		}
	}
	else return false;
}


void CollidePolygon::draw() {
	for (int i = 0; i < angle_positions.size(); ++i) {
		Position draw_pos_begin = angle_positions.at(i).get_draw_position();
		Position draw_pos_end;

		if (i == angle_positions.size() - 1) {
			draw_pos_end = angle_positions.at(0).get_draw_position();
		}
		else {
			draw_pos_end = angle_positions.at(i + 1).get_draw_position();
		}
		DxLib::DrawLineAA(
			draw_pos_begin.x,
			draw_pos_begin.y,
			draw_pos_end.x,
			draw_pos_end.y,
			CollideRealm::DRAW_COLOR,
			CollideRealm::DRAW_THICKNESS
		);
	}
}


void CollidePolygon::update(vector<InFieldPosition>& upd_angle_positions) {
	angle_positions = upd_angle_positions;
}