#include <vector>
#include <numbers>
#include "DxLib.h"
#include "Field.h"
#include "enum.h"
#include "Character/MyCharacter/MyCharacter.h"
#include "CrashEffect.h"

using std::unique_ptr;
using std::vector;
using std::make_unique;
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
    for (int i = 0; i < 20; ++i) {
        double arg = (DxLib::GetRand(360) / 180.0) * pi;
        double speed = 400;
        circles.emplace_back(init_pos_x, init_pos_y, arg, speed);
        arg = (DxLib::GetRand(360) / 180.0) * pi;
        triangles.emplace_back(init_pos_x, init_pos_y, arg, speed);
    }
}

void CrashEffect::update() {
    for (auto& circle : circles) {
        circle.update();
    }
    for (auto& triangle : triangles) {
        triangle.update();
    }
    // ◯秒経過したらupdateをやめる？
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
CrashEffect::Triangle::Triangle(
    double init_pos_x,
    double init_pos_y,
    double init_arg, 
    double init_speed
) : 
    position(make_unique<InFieldPosition>(init_pos_x, init_pos_y)),
    arg(init_arg), 
    speed(init_speed),
    last_updated_clock(DxLib::GetNowHiPerformanceCount())
{
    // ランダムな色を設定
    int r = DxLib::GetRand(255);
    int g = DxLib::GetRand(255);
    int b = DxLib::GetRand(255);
    color = GetColor(r, g, b);
}

void CrashEffect::Triangle::update() {
    // 位置を更新  
    LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;
    double distance = speed * update_delta_time / 1000 / 1000;
    double distance_x = distance * cos(arg);
    double distance_y = distance * sin(arg);
    position->x += distance_x;
    position->y += distance_y;
    last_updated_clock = DxLib::GetNowHiPerformanceCount();
}

void CrashEffect::Triangle::draw() {
    DrawTriangle(static_cast<int>(position->x), static_cast<int>(position->y),
                 static_cast<int>(position->x + 10), static_cast<int>(position->y + 10),
                 static_cast<int>(position->x - 10), static_cast<int>(position->y + 10), color, TRUE);
}

// Circle クラスの実装
CrashEffect::Circle::Circle(
    double init_pos_x,
    double init_pos_y,
    double init_arg,
    double init_speed
) :
    position(make_unique<InFieldPosition>(init_pos_x, init_pos_y)),
    arg(init_arg),
    speed(init_speed),
    last_updated_clock(DxLib::GetNowHiPerformanceCount())
{
    // ランダムな色を設定
    int r = DxLib::GetRand(255);
    int g = DxLib::GetRand(255);
    int b = DxLib::GetRand(255);
    color = GetColor(r, g, b);
}

void CrashEffect::Circle::update() {
    // 位置を更新
    LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;
    double distance = speed * update_delta_time / 1000 / 1000;
    double distance_x = distance * cos(arg);
    double distance_y = distance * sin(arg);
    position->x += distance_x;
    position->y += distance_y;
    last_updated_clock = DxLib::GetNowHiPerformanceCount();

}

void CrashEffect::Circle::draw() {
    DrawCircle(static_cast<int>(position->x), static_cast<int>(position->y), 5, color, TRUE);
}