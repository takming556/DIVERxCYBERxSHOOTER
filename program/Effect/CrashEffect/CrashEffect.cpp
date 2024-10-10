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
    double init_pos_x,
    double init_pos_y
) :
    Effect(
        init_pos_x,
        init_pos_y
    )
{
    // 初期位置からサークルとトライアングルを生成
    for (int i = 0; i < 10; ++i) {
        double angle = (DxLib::GetRand(360) / 180.0) * pi;
        double speed = DxLib::GetRand(3) + 1;
        circles.emplace_back(init_pos_x, init_pos_y, angle, speed);
        triangles.emplace_back(init_pos_x, init_pos_y, angle, speed);
    }
}

void CrashEffect::update() {
    for (auto& circle : circles) {
        circle.update();
    }
    for (auto& triangle : triangles) {
        triangle.update();
    }
};

void CrashEffect::draw() {
    for (auto& circle : circles) {
        circle.draw();
    }
    for (auto& triangle : triangles) {
        triangle.draw();
    }
}

// Triangle クラスの実装
CrashEffect::Triangle::Triangle(double init_pos_x, double init_pos_y, double init_angle, double speed)
    : pos_x(init_pos_x), pos_y(init_pos_y), angle(init_angle)
{
    velocity_x = speed * cos(angle);
    velocity_y = speed * sin(angle);

    // ランダムな色を設定
    int r = DxLib::GetRand(255);
    int g = DxLib::GetRand(255);
    int b = DxLib::GetRand(255);
    color = GetColor(r, g, b);
}

void CrashEffect::Triangle::update() {
    // 位置を更新
    pos_x += velocity_x;
    pos_y += velocity_y;
}

void CrashEffect::Triangle::draw() {
    DrawTriangle(static_cast<int>(pos_x), static_cast<int>(pos_y),
                 static_cast<int>(pos_x + 10), static_cast<int>(pos_y + 10),
                 static_cast<int>(pos_x - 10), static_cast<int>(pos_y + 10), color, TRUE);
}

// Circle クラスの実装
CrashEffect::Circle::Circle(double init_pos_x, double init_pos_y, double init_angle, double speed)
    : pos_x(init_pos_x), pos_y(init_pos_y), angle(init_angle)
{
    velocity_x = speed * cos(angle);
    velocity_y = speed * sin(angle);

    // ランダムな色を設定
    int r = DxLib::GetRand(255);
    int g = DxLib::GetRand(255);
    int b = DxLib::GetRand(255);
    color = GetColor(r, g, b);
}

void CrashEffect::Circle::update() {
    // 位置を更新
    pos_x += velocity_x;
    pos_y += velocity_y;
}

void CrashEffect::Circle::draw() {
    DrawCircle(static_cast<int>(pos_x), static_cast<int>(pos_y), 5, color, TRUE);
}