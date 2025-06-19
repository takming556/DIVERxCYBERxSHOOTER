#pragma once
#include <vector>
#include "enum.h"
#include "Effect/Effect.h"

using std::unique_ptr;
using std::vector;

class CrashEffect : virtual public Effect{
private:
	double emitPosX;
	double emitPosY;
	int const generatedClock;
	int const emitEndClock;
	int lastEmittedClock;

	const static double INIT_SPEED;
	const static unsigned int EMIT_INTERVAL;
	const static unsigned int EMIT_TIME;
	const static unsigned int LIFE_SPAN;

	class Circle {
	private:
		unique_ptr<InFieldPosition> position;
		double arg;
		double speed;
		double size;
		unsigned int color;
		LONGLONG lastUpdatedClock;
	public:
		Circle(
			double init_pos_x,
			double init_pos_y,
			double init_arg,
			double init_speed
		);
		void Update();
		void Draw();
	};

	class Triangle {
	private:
		unique_ptr<InFieldPosition> position;
		double arg;
		double speed;
		double angle;
		double size;
		unsigned int color;
		LONGLONG lastUpdatedClock;
	public:
		Triangle(
			double init_pos_x,
			double init_pos_y,
			double init_arg,
			double init_speed
		);
		void Update();
		void Draw();
	};

	vector<Circle> circles;
	vector<Triangle> triangles;
public:
	CrashEffect(
		double init_pos_x,
		double init_pos_y
	);
	void Update() override;
	void Draw() override;
	bool IsExpired() override;

};