#include <cmath>
#include <typeinfo>
#include "DxLib.h"
#include "CollideRealm/CollidePolygon.h"
#include "CollideRealm/CollideCircle.h"
#include "Colors.h"

using std::abs;		// ê‚ëŒílä÷êî
using std::sqrt;	// ïΩï˚ç™ä÷êî
using std::pow;		// Ç◊Ç´èÊä÷êî

CollidePolygon::CollidePolygon(vector<InFieldPosition>& upd_angle_positions):
	angle_positions(upd_angle_positions)
{
}


bool CollidePolygon::is_collided_with(unique_ptr<CollideRealm>& given_collide_realm) {
	if (typeid(*given_collide_realm) == typeid(CollideCircle)) {
		bool judge = false;
		bool third_judge_activate_flag = true;
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

			double upper = v.x * m.y - v.y * m.x;
			double lower = sqrt(pow(v.x, 2.0) + pow(v.y, 2.0));
			bool C = upper / lower <= given_collide_circle->radius;

			InFieldPosition c(given_collide_circle->center_pos->x, given_collide_circle->center_pos->y);
			InFieldPosition p(angle_positions.at(i).x, angle_positions.at(i).y);
			InFieldPosition p1;
			if (i == angle_positions.size() - 1) {
				p1.x = angle_positions.at(0).x;
				p1.y = angle_positions.at(0).y;
			}
			else {
				p1.x = angle_positions.at(i + 1).x;
				p1.y = angle_positions.at(i + 1).y;
			}
			bool D = pow(c.x - p.x, 2.0) + pow(c.y - p.y, 2.0) <= pow(given_collide_circle->radius, 2.0);
			bool E = pow(c.x - p1.x, 2.0) + pow(c.y - p1.y, 2.0) <= pow(given_collide_circle->radius, 2.0);
			if (A && B && C) {
				third_judge_activate_flag = false;
				judge = true;
				break;
			}
			else if (D || E) {
				third_judge_activate_flag = false;
				judge = true;
				break;
			}

		}
		if (third_judge_activate_flag == true) {
			bool third_judge = true;
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

				double cross_v_m = v.x * m.y - v.y * m.x;
				if (cross_v_m > 0) {
					third_judge = false;
					judge = false;
					break;
				}
			}
			if (third_judge == true) {
				judge = true;
			}
		}
		return judge;
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