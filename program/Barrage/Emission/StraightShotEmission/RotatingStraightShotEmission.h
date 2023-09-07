#pragma once
#include "DxLib.h"
#include "Barrage/Emission/StraightShotEmission/StraightShotEmission.h"

class RotatingStraightShotEmission : public StraightShotEmission {
private:
	double x;
	double y;
	double arg;
	double rotate_speed;
	bool emit_unlimited_flag;
	unsigned int emits;
	unsigned int emit_nozzles;
	unsigned int emit_interval;
	unsigned int emit_count;
	int last_emitted_clock;
	LONGLONG last_updated_clock;
	double shot_speed;
	unsigned int shot_collidant_size;
	unsigned int shot_durability;
	enum TeamID shot_team_id;
	enum SkinID shot_skin_id;
	bool emitting_flag;
public:
	RotatingStraightShotEmission(
		double init_pos_x,
		double init_pos_y,
		double init_arg,
		double given_rotate_speed,
		bool given_emit_unlimited_flag,
		unsigned int given_emits,
		unsigned int given_emit_nozzles,
		unsigned int given_emit_interval,
		double given_shot_speed,
		unsigned int given_shot_collidant_size,
		unsigned int given_shot_durability,
		enum TeamID given_shot_team_id,
		enum SkinID given_shot_skin_id
	);
	void update(double upd_pos_x, double upd_pos_y);
	void emit();
	void pause_emitting();
	void resume_emitting();
};