#pragma once
#include <vector>

using std::vector;

class ImageHandles {
private:
	ImageHandles() {}	//唯一のコンストラクタをprivateにすることで実体の生成を禁止している
public:
	static void LOAD_ALL_IMAGE();

	static int FULLBODY_ICHIGOCHAN_NORMAL;
	static int FULLBODY_ICHIGOCHAN_AVATAR;
	static int FULLBODY_MOFU;
	static int FULLBODY_NEON;
	static int FULLBODY_TOROI;

	static int SPRITE_ICHIGOCHAN;
	static int SPRITE_MOFU;
	static int SPRITE_NEON;
	static int SPRITE_TOROI;
	static int SPRITE_ZKCHR_KURAGE;
	static int SPRITE_ZKCHR_KUJIRA;
	static int SPRITE_ZKCHR_LIGHT_ELE;
	static int SPRITE_ZKCHR_KNIGHT_RAY;
	static int SPRITE_ZKCHR_GOZGOK;
	static int SPRITE_ZKCHR_MEZDOROGON;

	static int ANCHOR_BLACK;
	static int ANCHOR_GRAY;
	static int ANCHOR_SILVER;
	static int ANCHOR_WHITE;
	static int ANCHOR_BLUE;
	static int ANCHOR_NAVY;
	static int ANCHOR_TEAL;
	static int ANCHOR_GREEN;
	static int ANCHOR_LIME;
	static int ANCHOR_AQUA;
	static int ANCHOR_YELLOW;
	static int ANCHOR_RED;
	static int ANCHOR_FUCHSIA;
	static int ANCHOR_OLIVE;
	static int ANCHOR_PURPLE;
	static int ANCHOR_MAROON;

	static int BUBBLE_BLACK;
	static int BUBBLE_GRAY;
	static int BUBBLE_SILVER;
	static int BUBBLE_WHITE;
	static int BUBBLE_BLUE;
	static int BUBBLE_NAVY;
	static int BUBBLE_TEAL;
	static int BUBBLE_GREEN;
	static int BUBBLE_LIME;
	static int BUBBLE_AQUA;
	static int BUBBLE_YELLOW;
	static int BUBBLE_RED;
	static int BUBBLE_FUCHSIA;
	static int BUBBLE_OLIVE;
	static int BUBBLE_PURPLE;
	static int BUBBLE_MAROON;

	static int CIRCLE_BLACK;
	static int CIRCLE_GRAY;
	static int CIRCLE_SILVER;
	static int CIRCLE_WHITE;
	static int CIRCLE_BLUE;
	static int CIRCLE_NAVY;
	static int CIRCLE_TEAL;
	static int CIRCLE_GREEN;
	static int CIRCLE_LIME;
	static int CIRCLE_AQUA;
	static int CIRCLE_YELLOW;
	static int CIRCLE_RED;
	static int CIRCLE_FUCHSIA;
	static int CIRCLE_OLIVE;
	static int CIRCLE_PURPLE;
	static int CIRCLE_MAROON;

	static int CRYSTAL_BLACK;
	static int CRYSTAL_GRAY;
	static int CRYSTAL_SILVER;
	static int CRYSTAL_WHITE;
	static int CRYSTAL_BLUE;
	static int CRYSTAL_NAVY;
	static int CRYSTAL_TEAL;
	static int CRYSTAL_GREEN;
	static int CRYSTAL_LIME;
	static int CRYSTAL_AQUA;
	static int CRYSTAL_YELLOW;
	static int CRYSTAL_RED;
	static int CRYSTAL_FUCHSIA;
	static int CRYSTAL_OLIVE;
	static int CRYSTAL_PURPLE;
	static int CRYSTAL_MAROON;

	static int STRAWBERRY_BLACK;
	static int STRAWBERRY_GRAY;
	static int STRAWBERRY_SILVER;
	static int STRAWBERRY_WHITE;
	static int STRAWBERRY_BLUE;
	static int STRAWBERRY_NAVY;
	static int STRAWBERRY_TEAL;
	static int STRAWBERRY_GREEN;
	static int STRAWBERRY_LIME;
	static int STRAWBERRY_AQUA;
	static int STRAWBERRY_YELLOW;
	static int STRAWBERRY_RED;
	static int STRAWBERRY_FUCHSIA;
	static int STRAWBERRY_OLIVE;
	static int STRAWBERRY_PURPLE;
	static int STRAWBERRY_MAROON;

	static int POTATO_BASIC;
	static int POTATO_BLACK;
	static int POTATO_GRAY;
	static int POTATO_SILVER;
	static int POTATO_WHITE;
	static int POTATO_BLUE;
	static int POTATO_NAVY;
	static int POTATO_TEAL;
	static int POTATO_GREEN;
	static int POTATO_LIME;
	static int POTATO_AQUA;
	static int POTATO_YELLOW;
	static int POTATO_RED;
	static int POTATO_FUCHSIA;
	static int POTATO_OLIVE;
	static int POTATO_PURPLE;
	static int POTATO_MAROON;

	static int GHOST_RED_FRONT;
	static int GHOST_RED_BACK;
	static int GHOST_ORANGE_FRONT;
	static int GHOST_ORANGE_BACK;
	static int GHOST_YELLOW_FRONT;
	static int GHOST_YELLOW_BACK;
	static int GHOST_GREEN_FRONT;
	static int GHOST_GREEN_BACK;
	static int GHOST_TEAL_FRONT;
	static int GHOST_TEAL_BACK;
	static int GHOST_AQUA_FRONT;
	static int GHOST_AQUA_BACK;
	static int GHOST_BLUE_FRONT;
	static int GHOST_BLUE_BACK;
	static int GHOST_PURPLE_FRONT;
	static int GHOST_PURPLE_BACK;
	static int GHOST_FUCHSIA_FRONT;
	static int GHOST_FUCHSIA_BACK;
	static int GHOST_SILVER_FRONT;
	static int GHOST_SILVER_BACK;
	static int GHOST_GRAY_FRONT;
	static int GHOST_GRAY_BACK;

	static vector<int> GHOST_RED;
	static vector<int> GHOST_ORANGE;
	static vector<int> GHOST_YELLOW;
	static vector<int> GHOST_GREEN;
	static vector<int> GHOST_TEAL;
	static vector<int> GHOST_AQUA;
	static vector<int> GHOST_BLUE;
	static vector<int> GHOST_PURPLE;
	static vector<int> GHOST_FUCHSIA;
	static vector<int> GHOST_SILVER;
	static vector<int> GHOST_GRAY;

	static int LEIDENJAR0;
	static int LEIDENJAR1;
	static int LEIDENJAR2;
	static int LEIDENJAR3;

	static int LASER_RED;
	static int LASER_ORANGE;
	static int LASER_YELLOW;
	static int LASER_GREEN;
	static int LASER_TEAL;
	static int LASER_AQUA;
	static int LASER_BLUE;
	static int LASER_PURPLE;
	static int LASER_FUCHSIA;
	static int LASER_SILVER;
	static int LASER_GRAY;

	static int HEART_RED;
	static int HEART_ORANGE;
	static int HEART_YELLOW;
	static int HEART_GREEN;
	static int HEART_TEAL;
	static int HEART_AQUA;
	static int HEART_BLUE;
	static int HEART_PURPLE;
	static int HEART_FUCHSIA;
	static int HEART_SILVER;
	static int HEART_GRAY;	

	static int OVAL_RED;
	static int OVAL_ORANGE;
	static int OVAL_YELLOW;
	static int OVAL_GREEN;
	static int OVAL_TEAL;
	static int OVAL_AQUA;
	static int OVAL_BLUE;
	static int OVAL_PURPLE;
	static int OVAL_FUCHSIA;
	static int OVAL_SILVER;
	static int OVAL_GRAY;


	static int LOGO;
	static int LOGO_NONSILHOUETTE;
	static int ICHIGOCHAN_CONCEPTUAL;
	static int SCREEN_BACKGROUND;
	static int SCREEN_BACKGROUND_CROPPED;
	static int FIELD_BACKGROUND_STAGE1;
	static int FIELD_BACKGROUND_STAGE2;
	static int FIELD_BACKGROUND_STAGE3;
	static int DIGIT_CURSOR;
	static int NARRATIVE_POP;
	static int HP_DONUT;
	static int TEXT_FILE;

	static int FIELD_BACKGROUND;
	static int TEST_SHOOTER;
	static int BLUE_MARBLE;
	static int RED_MARBLE;
	static int ORANGE_TRIANGLE;
	static int MAJIKICHI_SMILE;
	static int HAND_POWER;
	static int PIEN;
	static int HEART;
	static int MELTING_FACE;
	static int THINKING_FACE;
	static int SUNGLASS_FACE;
	static int KURAGE;
	static int KUJIRA;
};