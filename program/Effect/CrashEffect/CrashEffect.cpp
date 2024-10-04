#include <vector>
#include "DxLib.h"
#include "Field.h"
#include "enum.h"
#include "Character/MyCharacter/MyCharacter.h"
#include "CrashEffect.h"

std::vector<int> dnaLen;

CrashEffect::CrashEffect(
    double init_emit_pos_x,
    double init_emit_pos_y
) :
    Effect(
        init_emit_pos_x,
        init_emit_pos_y
    ),
    emit_pos_x(init_emit_pos_x),
    emit_pos_y(init_emit_pos_y)
{
	// �����_���V�[�h��������
	std::srand(static_cast<unsigned int>(std::time(0)));
}

void CrashEffect::update() {
};

void CrashEffect::draw() {
    RandomColor();
}

void CrashEffect::EmitPixel() {
    // �ŏ��ɂ��
    pixel_pos_x = emit_pos_x;
    pixel_pos_y = emit_pos_y;
    pixel_emit_arg = 

    int r = std::rand() % 256;
    int g = std::rand() % 256;
    int b = std::rand() % 256;
    GetColor(r, g, b)

    //�@
    DrawPixel(pixel_pos_x, pixel_pos_y, random_color);
}
    

// �s�N�Z���������_���ȐF�ŕ`�悷��
void CrashEffect::RandomColor() {
    // �����_���ȐF�𐶐� (RGB)

    //// ��ʂ̒��S�Ƀs�N�Z����`��
    //for (int i = 1; i <= 100; i++) {
    //    DrawPixel(emit_pos_x+i, emit_pos_y+i, GetColor(r, g, b));
    //}
}

