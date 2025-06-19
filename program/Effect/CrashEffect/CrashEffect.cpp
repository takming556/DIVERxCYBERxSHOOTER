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

const double CrashEffect::INIT_SPEED = 400;
const unsigned int CrashEffect::EMIT_INTERVAL = 5;
const unsigned int CrashEffect::EMIT_TIME = 250;
const unsigned int CrashEffect::LIFE_SPAN = 3000;

CrashEffect::CrashEffect(
    double init_pos_x,
    double init_pos_y
) :
    Effect(
        init_pos_x,
        init_pos_y
    ),
    emitPosX(init_pos_x),
    emitPosY(init_pos_y),
    generatedClock(DxLib::GetNowCount()),
    emitEndClock(generatedClock + EMIT_TIME),
    lastEmittedClock(DxLib::GetNowCount())
{
}

void CrashEffect::Update() {
    int current_clock = DxLib::GetNowCount();
    int delta_time = current_clock - lastEmittedClock;
    if (delta_time >= EMIT_INTERVAL && DxLib::GetNowCount() <= emitEndClock) {
        double arg = DxLib::GetRand(360) / 180.0 * pi;
        double speed = INIT_SPEED;
        int circle_or_triangle = DxLib::GetRand(1);
        if (circle_or_triangle == 1) {
            circles.emplace_back(emitPosX, emitPosY, arg, speed);
        }
        else {
            triangles.emplace_back(emitPosX, emitPosY, arg, speed);
        }
        lastEmittedClock = DxLib::GetNowCount();
    }

    for (auto& circle : circles) {
        circle.Update();
    }
    for (auto& triangle : triangles) {
        triangle.Update();
    }
    // ◯秒経過したらupdateをやめる？
};

void CrashEffect::Draw() {
    for (auto& circle : circles) {
        circle.Draw();
    }
    for (auto& triangle : triangles) {
        triangle.Draw();
    }
}

bool CrashEffect::IsExpired() {
    if (DxLib::GetNowCount() > generatedClock + LIFE_SPAN)
        return true;
    else
        return false;
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
    lastUpdatedClock(DxLib::GetNowHiPerformanceCount())
{
    size = 10.0 + (DxLib::GetRand(10000.0) - 5000.0) / 1000.0;
    int r = DxLib::GetRand(1) * 255;
    int g = DxLib::GetRand(1) * 255;
    int b = 255;
    if (DxLib::GetRand(1) == 0) {
        r = 255;
        g = 0;
    }
    else {
        r = 0;
        g = 255;
    }
    color = GetColor(r, g, b);
}

void CrashEffect::Circle::Update() {
    LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - lastUpdatedClock;
    double distance = speed * update_delta_time / 1000 / 1000;
    double distance_x = distance * cos(arg);
    double distance_y = distance * sin(arg);
    position->x += distance_x;
    position->y += distance_y;
    lastUpdatedClock = DxLib::GetNowHiPerformanceCount();
}

void CrashEffect::Circle::Draw() {
    Position draw_pos = position->get_draw_position();
    DrawCircle(static_cast<int>(draw_pos.x), static_cast<int>(draw_pos.y), size, color, TRUE);
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
    lastUpdatedClock(DxLib::GetNowHiPerformanceCount())
{
    angle = DxLib::GetRand(24) / 24.0 * pi;
    size = 10.0 + (DxLib::GetRand(10000.0) - 5000.0) / 1000.0;
    int r = DxLib::GetRand(1) * 255;
    int g = DxLib::GetRand(1) * 255;
    int b = 255;
    if (DxLib::GetRand(1) == 0) {
        r = 255;
        g = 0;
    }
    else {
        r = 0;
        g = 255;
    }
    color = GetColor(r, g, b);
}

void CrashEffect::Triangle::Update() {
    LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - lastUpdatedClock;
    double distance = speed * update_delta_time / 1000 / 1000;
    double distance_x = distance * cos(arg);
    double distance_y = distance * sin(arg);
    position->x += distance_x;
    position->y += distance_y;
    angle += 1.0 / 360.0 / 5.0 * pi;
    lastUpdatedClock = DxLib::GetNowHiPerformanceCount();
}

void CrashEffect::Triangle::Draw() {
    Position draw_pos = position->get_draw_position();

    // 頂点間の角度は 2/3π (120度) ずつ
    const double angleOffset = 2.0 * pi / 3.0;

    double x1 = draw_pos.x + size * cos(angle);
    double y1 = draw_pos.y + size * sin(angle);
    double x2 = draw_pos.x + size * cos(angle + angleOffset);
    double y2 = draw_pos.y + size * sin(angle + angleOffset);
    double x3 = draw_pos.x + size * cos(angle - angleOffset);
    double y3 = draw_pos.y + size * sin(angle - angleOffset);

    DrawTriangle(static_cast<int>(x1), static_cast<int>(y1),
                    static_cast<int>(x2), static_cast<int>(y2),
                    static_cast<int>(x3), static_cast<int>(y3),
                    color, TRUE);

}
