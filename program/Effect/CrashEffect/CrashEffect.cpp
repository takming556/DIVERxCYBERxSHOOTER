#include <vector>
#include <numbers>
#include "DxLib.h"
#include "Field.h"
#include "enum.h"
#include "Character/MyCharacter/MyCharacter.h"
#include "CrashEffect.h"

std::vector<int> dnaLen;
using std::numbers::pi;

CrashEffect::CrashEffect(
    double init_emit_pos_x,
    double init_emit_pos_y
) :
    Effect(
        init_emit_pos_x,
        init_emit_pos_y
    ),
    emit_pos_x(init_emit_pos_x),
    emit_pos_y(init_emit_pos_y),
    pixel_pos_x(0.0),
    pixel_pos_y(0.0),
    pixel_emit_arg(0.0),
    pixel_color(0)
{
    pixel_pos_x = emit_pos_x;
    pixel_pos_y = emit_pos_y;
    pixel_emit_arg = DxLib::GetRand(48) / 24.0 * pi;

    int r = DxLib::GetRand(256);
    int g = DxLib::GetRand(256);
    int b = DxLib::GetRand(256);
    pixel_color = GetColor(r, g, b);
}

void CrashEffect::update() {

};

void CrashEffect::draw() {
    EmitPixel();
}

void CrashEffect::EmitPixel() {



    DrawPixel(pixel_pos_x, pixel_pos_y, pixel_color);
}
    
void CrashEffect::

