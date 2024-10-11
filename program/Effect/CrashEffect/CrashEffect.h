#pragma once
#include <vector>
#include "enum.h"
#include "Effect/Effect.h"

using std::unique_ptr;
using std::vector;

class CrashEffect : virtual public Effect{
private:
	double emit_pos_x;
	double emit_pos_y;
	int start_clock;
	int end_clock;
	int move_clock;

	const static double INIT_SPEED;
	const static unsigned int EMIT_INTERVAL;
	const static unsigned int EMIT_TIME;

	class Circle {
	private:
		unique_ptr<InFieldPosition> position;
		double arg;
		double speed;
		double size;
		unsigned int color;
		LONGLONG last_updated_clock;
	public:
		Circle(
			double init_pos_x,
			double init_pos_y,
			double init_arg,
			double init_speed
		);
		void update();
		void draw();
	};

	class Triangle {
	private:
		unique_ptr<InFieldPosition> position;
		double arg;
		double speed;
		double angle;
		double size;
		unsigned int color;
		LONGLONG last_updated_clock;
	public:
		Triangle(
			double init_pos_x,
			double init_pos_y,
			double init_arg,
			double init_speed
		);
		void update();
		void draw();
	};

	std::vector<Circle> circles;
	std::vector<Triangle> triangles;
public:
	CrashEffect(
		double init_pos_x,
		double init_pos_y
	);
	void update() override;
	void draw() override;

};