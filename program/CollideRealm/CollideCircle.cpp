#include <memory>
#include <cmath>
#include <numbers>
//#include <typeinfo>
#include "DxLib.h"
#include "CollideRealm/CollideRealm.h"
#include "CollideRealm/CollideCircle.h"
#include "Utils.h"
#include "DebugParams.h"
#include "enum.h"

using std::unique_ptr;
using std::make_unique;
using std::pow;
using std::sqrt;
using std::atan2;
using std::numbers::pi;


CollideCircle::CollideCircle(double init_center_pos_x, double init_center_pos_y, unsigned int init_radius) :
	center_pos(make_unique<InFieldPosition>(init_center_pos_x, init_center_pos_y)),
	radius(init_radius)
{
}


//bool CollideCircle::is_collided_with(unique_ptr<CollideRealm>& given_collide_realm) {
//
//	//DxLib::DrawFormatString(0, 45, GetColor(255, 0, 0), L"type = %s", typeid(*given_collide_realm).name());
//
//	if (typeid(*given_collide_realm) == typeid(CollideCircle)) {
//		CollideRealm* p_collide_realm = given_collide_realm.get();
//		CollideCircle* given_collide_circle = static_cast<CollideCircle*>(p_collide_realm);
//		double x1 = given_collide_circle->center_pos->x;
//		double y1 = given_collide_circle->center_pos->y;
//		unsigned int r1 = given_collide_circle->radius;
//		double x2 = center_pos->x;
//		double y2 = center_pos->y;
//		unsigned int r2 = radius;
//		double center_distance = sqrt(pow(x2 - x1, 2.0) + pow(y2 - y1, 2.0));	//三平方の定理
//		return center_distance < r1 + r2;
//	}
//	else return false;
//
//}


bool CollideCircle::is_collided_with(unique_ptr<CollideCircle>& given_collide_circle) {

		double x1 = given_collide_circle->center_pos->x;
		double y1 = given_collide_circle->center_pos->y;
		unsigned int r1 = given_collide_circle->radius;
		double x2 = center_pos->x;
		double y2 = center_pos->y;
		unsigned int r2 = radius;
		double center_distance = sqrt(pow(x2 - x1, 2.0) + pow(y2 - y1, 2.0));	//三平方の定理
		return center_distance < r1 + r2;

}


bool CollideCircle::is_collided_with(unique_ptr<CollidePolygon>& given_collide_polygon) {

	for (int i = 0; i < given_collide_polygon->angle_positions.size(); ++i) {
		double xC = center_pos->x;	// いちごちゃんの円形当たり判定領域の中心座標X
		double yC = center_pos->y;	// いちごちゃんの円形当たり判定領域の中心座標Y
		double x1 = given_collide_polygon->angle_positions.at(i).x;	// 多角形のi番目の辺の始点のX座標
		double y1 = given_collide_polygon->angle_positions.at(i).y;	// 多角形のi番目の辺の始点のY座標
		double x2;	// 多角形のi番目の辺の終点のX座標
		double y2;	// 多角形のi番目の辺の終点のY座標
		if (i == given_collide_polygon->angle_positions.size() - 1) {
			x2 = given_collide_polygon->angle_positions.at(0).x;
			y2 = given_collide_polygon->angle_positions.at(0).y;
		}
		else {
			x2 = given_collide_polygon->angle_positions.at(i + 1).x;
			y2 = given_collide_polygon->angle_positions.at(i + 1).y;
		}

		// 点と直線の距離を算出
		// 点 とは いちごちゃんの座標
		// 直線 とは 多角形の辺

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
		double r = radius;


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
	// それは、円か多角形のどちらか一方が他方に完全に含まれている場合である。
	// これを検出するには、多角形の辺を反時計回りにトレースするとき、円の中心点がずっと左もしくはずっと右に居ることを示す。
	// ずっと同じ側にいるということは円と多角形どちらか一方が他方に包囲されていると見なせるからである。
	// 検出にはベクトルの外積を使う。
	// 外積が正ならば左側に居るし、負ならば右側に居る。
	// 多角形のすべての辺に対して外積が正であることを示せれば、円は多角形に完全に含まれている。すなわち、衝突している。
	// 多角形のすべての辺に対して外積が負であることを示せれば、多角形は円に完全に含まれている。すなわち、衝突している。

	bool is_circle_center_included = true;
	CollideJudgeTraceSide last_side;
	for (int i = 0; i < given_collide_polygon->angle_positions.size(); ++i) {
		double xC = center_pos->x;	// いちごちゃんの円形当たり判定領域の中心座標X
		double yC = center_pos->y;	// いちごちゃんの円形当たり判定領域の中心座標Y
		double x1 = given_collide_polygon->angle_positions.at(i).x;	// 多角形のi番目の辺の始点のX座標
		double y1 = given_collide_polygon->angle_positions.at(i).y;	// 多角形のi番目の辺の始点のY座標
		double x2;	// 多角形のi番目の辺の終点のX座標
		double y2;	// 多角形のi番目の辺の終点のY座標
		if (i == given_collide_polygon->angle_positions.size() - 1) {
			x2 = given_collide_polygon->angle_positions.at(0).x;
			y2 = given_collide_polygon->angle_positions.at(0).y;
		}
		else {
			x2 = given_collide_polygon->angle_positions.at(i + 1).x;
			y2 = given_collide_polygon->angle_positions.at(i + 1).y;
		}
		double cross = (x2 - x1) * (yC - y1) - (xC - x1) * (y2 - y1);
		CollideJudgeTraceSide current_side;
		if (cross < 0)
			current_side = CollideJudgeTraceSide::OUTER;
		else
			current_side = CollideJudgeTraceSide::INNER;
		if (i >= 1) {
			if (current_side != last_side) is_circle_center_included = false;
		}
		last_side = current_side;
	}
	return is_circle_center_included;
}



//double arg = atan2(y2 - y1, x2 - x1);
//double arg1 = atan2(yC - y1, xC - x1);
//double arg2 = atan2(yC - y2, xC - x2);
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
//for (int i = 0; i < given_collide_polygon->angle_positions.size(); ++i) {
//	InFieldPosition v_begin = given_collide_polygon->angle_positions.at(i);
//	InFieldPosition v_end;
//	if (i == given_collide_polygon->angle_positions.size() - 1) {
//		v_end = given_collide_polygon->angle_positions.at(0);
//	}
//	else {
//		v_end = given_collide_polygon->angle_positions.at(i + 1);
//	}
//	InFieldPosition v(v_end.x - v_begin.x, v_end.y - v_end.y);

//	//unique_ptr<CollideCircle> given_collide_circle(dynamic_cast<CollideCircle*>(given_collide_realm.get()));
//	InFieldPosition m_begin = given_collide_polygon->angle_positions.at(i);
//	InFieldPosition m_end = *center_pos;
//	InFieldPosition m(m_end.x - m_begin.x, m_end.y - m_begin.y);

//	double dot_v_m = v.x * m.x + v.y * m.y;
//	bool A = dot_v_m >= 0;

//	InFieldPosition m1_begin;
//	if (i == given_collide_polygon->angle_positions.size() - 1) {
//		m1_begin = given_collide_polygon->angle_positions.at(0);
//	}
//	else {
//		m1_begin = given_collide_polygon->angle_positions.at(i + 1);
//	}
//	InFieldPosition m1_end = *center_pos;
//	InFieldPosition m1(m1_end.x - m1_begin.x, m1_end.y - m1_begin.y);
//	double dot_v_m1 = v.x * m1.x + v.y * m1.y;
//	bool B = dot_v_m1 <= 0;

//	double upper = v.x * m.y - v.y * m.x;
//	double lower = sqrt(pow(v.x, 2.0) + pow(v.y, 2.0));
//	bool C = upper / lower <= radius;

//	InFieldPosition c(center_pos->x, center_pos->y);
//	InFieldPosition p(given_collide_polygon->angle_positions.at(i).x, given_collide_polygon->angle_positions.at(i).y);
//	InFieldPosition p1;
//	if (i == given_collide_polygon->angle_positions.size() - 1) {
//		p1.x = given_collide_polygon->angle_positions.at(0).x;
//		p1.y = given_collide_polygon->angle_positions.at(0).y;
//	}
//	else {
//		p1.x = given_collide_polygon->angle_positions.at(i + 1).x;
//		p1.y = given_collide_polygon->angle_positions.at(i + 1).y;
//	}
//	bool D = pow(c.x - p.x, 2.0) + pow(c.y - p.y, 2.0) <= pow(radius, 2.0);
//	bool E = pow(c.x - p1.x, 2.0) + pow(c.y - p1.y, 2.0) <= pow(radius, 2.0);
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
//	for (int i = 0; i < given_collide_polygon->angle_positions.size(); ++i) {
//		InFieldPosition v_begin = given_collide_polygon->angle_positions.at(i);
//		InFieldPosition v_end;
//		if (i == given_collide_polygon->angle_positions.size() - 1) {
//			v_end = given_collide_polygon->angle_positions.at(0);
//		}
//		else {
//			v_end = given_collide_polygon->angle_positions.at(i + 1);
//		}
//		InFieldPosition v(v_end.x - v_begin.x, v_end.y - v_end.y);

//		//unique_ptr<CollideCircle> given_collide_circle(dynamic_cast<CollideCircle*>(given_collide_realm.get()));
//		InFieldPosition m_begin = given_collide_polygon->angle_positions.at(i);
//		InFieldPosition m_end = *center_pos;
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




void CollideCircle::draw() {
	Position draw_pos = center_pos->get_draw_position();
	float draw_radius = radius * 1.0;
	DxLib::DrawCircleAA(
		draw_pos.x,
		draw_pos.y,
		draw_radius,
		32,
		CollideRealm::DRAW_COLOR,
		FALSE,
		CollideRealm::DRAW_THICKNESS
	);
}


void CollideCircle::update(unique_ptr<InFieldPosition>& now_pos) {
	center_pos.get()->x = now_pos.get()->x;
	center_pos.get()->y = now_pos.get()->y;
}


void CollideCircle::set_radius(double alt_radius) {
	radius = alt_radius;
}