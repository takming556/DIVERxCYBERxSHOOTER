#pragma once
#include "enum.h"
#include "Effect/Effect.h"

class CrashEffect : virtual public Effect{
private:
	class Triangle {
	private:
		double pos_x, pos_y;
		double velocity_x, velocity_y;
		double angle;
		unsigned int color;

	public:
		Triangle(
			double init_pos_x,
			double init_pos_y,
			double angle,
			double speed
		);
		void update();
		void draw();
	};
	class Circle {
	private:
		double pos_x, pos_y;
		double velocity_x, velocity_y;
		double angle;
		unsigned int color;

	public:
		Circle(
			double init_pos_x,
			double init_pos_y,
			double angle,
			double speed
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
	void EmitPixel();
};