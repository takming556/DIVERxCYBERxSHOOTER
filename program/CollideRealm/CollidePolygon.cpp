#include <cmath>
#include <numbers>
//#include <typeinfo>
#include "DxLib.h"
#include "CollideRealm/CollidePolygon.h"
#include "CollideRealm/CollideCircle.h"
#include "Colors.h"
#include "Utils.h"

using std::abs;		// 絶対値関数
using std::sqrt;	// 平方根関数
using std::pow;		// べき乗関数
using std::numbers::pi;


CollidePolygon::CollidePolygon(vector<InFieldPosition>& upd_angle_positions):
	angle_positions(upd_angle_positions)
{
}


bool CollidePolygon::is_collided_with(unique_ptr<CollideCircle>& given_collide_circle) {

	for (int i = 0; i < angle_positions.size(); ++i) {
		double xC = given_collide_circle->center_pos->x;	// いちごちゃんの円形当たり判定領域の中心座標X
		double yC = given_collide_circle->center_pos->y;	// いちごちゃんの円形当たり判定領域の中心座標Y
		double x1 = angle_positions.at(i).x;	// 多角形のi番目の辺の始点のX座標
		double y1 = angle_positions.at(i).y;	// 多角形のi番目の辺の始点のY座標
		double x2;	// 多角形のi番目の辺の終点のX座標
		double y2;	// 多角形のi番目の辺の終点のY座標
		if (i == angle_positions.size() - 1) {
			x2 = angle_positions.at(0).x;
			y2 = angle_positions.at(0).y;
		}
		else {
			x2 = angle_positions.at(i + 1).x;
			y2 = angle_positions.at(i + 1).y;
		}

		// 点と直線の距離を算出
		// 点 とは いちごちゃんの座標
		// 直線 とは 多角形の辺		
		// double a = (y2 - y1) / (x2 - x1);
		// double b = y1 - a * x1;
		// double c = -a * x2 - b * y2;

		double a = y2 - y1;
		double b = -(x2 - x1);
		double c = y2 * (x2 - x1) - x2 * (y2 - y1);


		// 直線 ax + by + c = 0
		// upper とは 高校数学Ⅱで習う点と直線の距離の公式の分子の部分
		// lower とは 高校数学Ⅱで習う点と直線の距離の公式の分母の部分

		double upper = abs(a * xC + b * yC + c);
		double lower = sqrt(pow(a, 2.0) + pow(b, 2.0));

		// distance とは 点と直線の距離
		double distance = upper / lower;

		// r とは いちごちゃんの円形当たり判定領域の半径
		double r = given_collide_circle->radius;

		// distance >= r ならば どう頑張っても衝突できないので スキップ
		if (distance >= r) continue;


		// いま，3つのベクトルを考えよう。
		// 多角形の辺の始点から終点に向かうベクトルをvと呼ぼう。
		// 多角形の辺の始点から円の中心に向かうベクトルをv1と呼ぼう。
		// 多角形の辺の終点から円の中心に向かうベクトルをv2と呼ぼう。
		// dot1 とは vとv1の内積である。
		// dot2 とは vとv2の内積である。
		double dot1 = (x2 - x1) * (xC - x1) + (y2 - y1) * (yC - y1);
		double dot2 = (x2 - x1) * (xC - x2) + (y2 - y1) * (yC - y2);

		// これらの内積の値が正であるとき、(vとv1)もしくは(vとv2)は鋭角をなしていると言える。
		// (distance < r) かつ (いずれかが鋭角) ならば衝突していることが確定なので return true

		if (dot1 * dot2 <= 0) {
			return true;
		}
		else {
			// 鋭角ではなくても、(辺の始点ないし終点) から (円の中心) までの距離がrよりも小さいならば、辺のどちらか一方が円に刺さっている状態なので衝突している。
			double d1 = sqrt(pow(xC - x1, 2.0) + pow(yC - y1, 2.0));
			double d2 = sqrt(pow(xC - x2, 2.0) + pow(yC - y2, 2.0));
			if (d1 < r || d2 < r) return true;

		}
	}

	// これでもカバーしきれないパターンがある。
	// 円が多角形の内部に完全に含まれているパターンである。
	// これを検出するには、多角形の辺を反時計回りにトレースするとき、円の中心点がずっと左側にいることを示す。
	// ずっと左側にいるということは円の中心が多角形の辺に包囲されていると見なせるからである。
	// 左側の検出にはベクトルの外積を使う。
	// 外積が正ならば左側に居るし、負ならば右側に居る。
	// 多角形のすべての辺に対して外積が正であることを示せれば、円は多角形に完全に含まれている。すなわち、衝突している。

	bool is_circle_center_included = true;
	for (int i = 0; i < angle_positions.size(); ++i) {
		double xC = given_collide_circle->center_pos->x;	// いちごちゃんの円形当たり判定領域の中心座標X
		double yC = given_collide_circle->center_pos->y;	// いちごちゃんの円形当たり判定領域の中心座標Y
		double x1 = angle_positions.at(i).x;	// 多角形のi番目の辺の始点のX座標
		double y1 = angle_positions.at(i).y;	// 多角形のi番目の辺の始点のY座標
		double x2;	// 多角形のi番目の辺の終点のX座標
		double y2;	// 多角形のi番目の辺の終点のY座標
		if (i == angle_positions.size() - 1) {
			x2 = angle_positions.at(0).x;
			y2 = angle_positions.at(0).y;
		}
		else {
			x2 = angle_positions.at(i + 1).x;
			y2 = angle_positions.at(i + 1).y;
		}
		double cross = (x2 - x1) * (yC - y1) - (xC - x1) * (y2 - y1);
		if (cross < 0) is_circle_center_included = false;
	}
	return is_circle_center_included;
}



//double arg = Utils::fixed_atan2(y2 - y1, x2 - x1);
//double arg1 = Utils::fixed_atan2(yC - y1, xC - x1);
//double arg2 = Utils::fixed_atan2(yC - y2, xC - x2);
//double theta1 = arg1 - arg;
//double theta2 = arg2 - arg;
//if (theta1 <= 1.0 / 2.0 * pi || theta2 <= 1.0 / 2.0 * pi) {
//	return true;
//}


//bool judge = false;
//bool third_judge_activate_flag = true;
//for (int i = 0; i < angle_positions.size(); ++i) {

//	InFieldPosition v_begin = angle_positions.at(i);
//	InFieldPosition v_end;
//	if (i == angle_positions.size() - 1) {
//		v_end = angle_positions.at(0);
//	}
//	else {
//		v_end = angle_positions.at(i + 1);
//	}
//	InFieldPosition v(v_end.x - v_begin.x, v_end.y - v_end.y);

//	//unique_ptr<CollideCircle> given_collide_circle(dynamic_cast<CollideCircle*>(given_collide_realm.get()));
//	InFieldPosition m_begin = angle_positions.at(i);
//	InFieldPosition m_end = *(given_collide_circle->center_pos);
//	InFieldPosition m(m_end.x - m_begin.x, m_end.y - m_begin.y);

//	double dot_v_m = v.x * m.x + v.y * m.y;
//	bool A = dot_v_m >= 0;

//	InFieldPosition m1_begin;
//	if (i == angle_positions.size() - 1) {
//		m1_begin = angle_positions.at(0);
//	}
//	else {
//		m1_begin = angle_positions.at(i + 1);
//	}
//	InFieldPosition m1_end = *(given_collide_circle->center_pos);
//	InFieldPosition m1(m1_end.x - m1_begin.x, m1_end.y - m1_begin.y);
//	double dot_v_m1 = v.x * m1.x + v.y * m1.y;
//	bool B = dot_v_m1 <= 0;

//	double upper = v.x * m.y - v.y * m.x;
//	double lower = sqrt(pow(v.x, 2.0) + pow(v.y, 2.0));
//	bool C = upper / lower <= given_collide_circle->radius;

//	InFieldPosition c(given_collide_circle->center_pos->x, given_collide_circle->center_pos->y);
//	InFieldPosition p(angle_positions.at(i).x, angle_positions.at(i).y);
//	InFieldPosition p1;
//	if (i == angle_positions.size() - 1) {
//		p1.x = angle_positions.at(0).x;
//		p1.y = angle_positions.at(0).y;
//	}
//	else {
//		p1.x = angle_positions.at(i + 1).x;
//		p1.y = angle_positions.at(i + 1).y;
//	}
//	bool D = pow(c.x - p.x, 2.0) + pow(c.y - p.y, 2.0) <= pow(given_collide_circle->radius, 2.0);
//	bool E = pow(c.x - p1.x, 2.0) + pow(c.y - p1.y, 2.0) <= pow(given_collide_circle->radius, 2.0);
//	if (A && B && C) {
//		third_judge_activate_flag = false;
//		judge = true;
//		break;
//	}
//	else if (D || E) {
//		third_judge_activate_flag = false;
//		judge = true;
//		break;
//	}

//}
//if (third_judge_activate_flag == true) {
//	bool third_judge = true;
//	for (int i = 0; i < angle_positions.size(); ++i) {
//		InFieldPosition v_begin = angle_positions.at(i);
//		InFieldPosition v_end;
//		if (i == angle_positions.size() - 1) {
//			v_end = angle_positions.at(0);
//		}
//		else {
//			v_end = angle_positions.at(i + 1);
//		}
//		InFieldPosition v(v_end.x - v_begin.x, v_end.y - v_end.y);

//		//unique_ptr<CollideCircle> given_collide_circle(dynamic_cast<CollideCircle*>(given_collide_realm.get()));
//		InFieldPosition m_begin = angle_positions.at(i);
//		InFieldPosition m_end = *(given_collide_circle->center_pos);
//		InFieldPosition m(m_end.x - m_begin.x, m_end.y - m_begin.y);

//		double cross_v_m = v.x * m.y - v.y * m.x;
//		if (cross_v_m > 0) {
//			third_judge = false;
//			judge = false;
//			break;
//		}
//	}
//	if (third_judge == true) {
//		judge = true;
//	}
//}
//return judge;




//bool CollidePolygon::is_collided_with(unique_ptr<CollideRealm>& given_collide_realm) {
//	if (typeid(*given_collide_realm) == typeid(CollideCircle)) {
//		bool judge = false;
//		bool third_judge_activate_flag = true;
//		for (int i = 0; i < angle_positions.size(); ++i) {
//
//			InFieldPosition v_begin = angle_positions.at(i);
//			InFieldPosition v_end;
//			if (i == angle_positions.size() - 1) {
//				v_end = angle_positions.at(0);
//			}
//			else {
//				v_end = angle_positions.at(i + 1);
//			}
//			InFieldPosition v(v_end.x - v_begin.x, v_end.y - v_end.y);
//
//			unique_ptr<CollideCircle> given_collide_circle(dynamic_cast<CollideCircle*>(given_collide_realm.get()));
//			InFieldPosition m_begin = angle_positions.at(i);
//			InFieldPosition m_end = *(given_collide_circle->center_pos);
//			InFieldPosition m(m_end.x - m_begin.x, m_end.y - m_begin.y);
//
//			double dot_v_m = v.x * m.x + v.y * m.y;
//			bool A = dot_v_m >= 0;
//
//			InFieldPosition m1_begin;
//			if (i == angle_positions.size() - 1) {
//				m1_begin = angle_positions.at(0);
//			}
//			else {
//				m1_begin = angle_positions.at(i + 1);
//			}
//			InFieldPosition m1_end = *(given_collide_circle->center_pos);
//			InFieldPosition m1(m1_end.x - m1_begin.x, m1_end.y - m1_begin.y);
//			double dot_v_m1 = v.x * m1.x + v.y * m1.y;
//			bool B = dot_v_m1 <= 0;
//
//			double upper = v.x * m.y - v.y * m.x;
//			double lower = sqrt(pow(v.x, 2.0) + pow(v.y, 2.0));
//			bool C = upper / lower <= given_collide_circle->radius;
//
//			InFieldPosition c(given_collide_circle->center_pos->x, given_collide_circle->center_pos->y);
//			InFieldPosition p(angle_positions.at(i).x, angle_positions.at(i).y);
//			InFieldPosition p1;
//			if (i == angle_positions.size() - 1) {
//				p1.x = angle_positions.at(0).x;
//				p1.y = angle_positions.at(0).y;
//			}
//			else {
//				p1.x = angle_positions.at(i + 1).x;
//				p1.y = angle_positions.at(i + 1).y;
//			}
//			bool D = pow(c.x - p.x, 2.0) + pow(c.y - p.y, 2.0) <= pow(given_collide_circle->radius, 2.0);
//			bool E = pow(c.x - p1.x, 2.0) + pow(c.y - p1.y, 2.0) <= pow(given_collide_circle->radius, 2.0);
//			if (A && B && C) {
//				third_judge_activate_flag = false;
//				judge = true;
//				break;
//			}
//			else if (D || E) {
//				third_judge_activate_flag = false;
//				judge = true;
//				break;
//			}
//
//		}
//		if (third_judge_activate_flag == true) {
//			bool third_judge = true;
//			for (int i = 0; i < angle_positions.size(); ++i) {
//				InFieldPosition v_begin = angle_positions.at(i);
//				InFieldPosition v_end;
//				if (i == angle_positions.size() - 1) {
//					v_end = angle_positions.at(0);
//				}
//				else {
//					v_end = angle_positions.at(i + 1);
//				}
//				InFieldPosition v(v_end.x - v_begin.x, v_end.y - v_end.y);
//
//				unique_ptr<CollideCircle> given_collide_circle(dynamic_cast<CollideCircle*>(given_collide_realm.get()));
//				InFieldPosition m_begin = angle_positions.at(i);
//				InFieldPosition m_end = *(given_collide_circle->center_pos);
//				InFieldPosition m(m_end.x - m_begin.x, m_end.y - m_begin.y);
//
//				double cross_v_m = v.x * m.y - v.y * m.x;
//				if (cross_v_m > 0) {
//					third_judge = false;
//					judge = false;
//					break;
//				}
//			}
//			if (third_judge == true) {
//				judge = true;
//			}
//		}
//		return judge;
//	}
//	else return false;
//}


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