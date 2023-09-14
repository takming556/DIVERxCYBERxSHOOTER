#include <memory>
#include <cmath>
#include <typeinfo>
#include "DxLib.h"
#include "CollideRealm/CollideRealm.h"
#include "CollideRealm/CollideCircle.h"

using std::unique_ptr;
using std::make_unique;
using std::pow;
using std::sqrt;


CollideCircle::CollideCircle(double init_center_pos_x, double init_center_pos_y, unsigned int init_radius) :
	center_pos(make_unique<InFieldPosition>(init_center_pos_x, init_center_pos_y)),
	radius(init_radius)
{
}


bool CollideCircle::is_collided_with(unique_ptr<CollideRealm>& given_collide_realm) {

	//DxLib::DrawFormatString(0, 45, GetColor(255, 0, 0), "type = %s", typeid(*given_collide_realm).name());

	if (typeid(*given_collide_realm) == typeid(CollideCircle)) {
		CollideRealm* p_collide_realm = given_collide_realm.get();
		CollideCircle* given_collide_circle = static_cast<CollideCircle*>(p_collide_realm);
		double x1 = given_collide_circle->center_pos->x;
		double y1 = given_collide_circle->center_pos->y;
		unsigned int r1 = given_collide_circle->radius;
		double x2 = center_pos->x;
		double y2 = center_pos->y;
		unsigned int r2 = radius;
		double center_distance = sqrt(pow(x2 - x1, 2.0) + pow(y2 - y1, 2.0));	//三平方の定理
		return center_distance < r1 + r2;
	}
	else return false;

}


void CollideCircle::draw() {
	Position draw_pos = center_pos->get_draw_position();
	float draw_radius = radius * 1.0;
	DxLib::DrawCircleAA(draw_pos.x, draw_pos.y, draw_radius, 32, DRAW_COLOR, FALSE, 3.0F);
}


void CollideCircle::update(unique_ptr<InFieldPosition>& now_pos) {
	center_pos.get()->x = now_pos.get()->x;
	center_pos.get()->y = now_pos.get()->y;
}