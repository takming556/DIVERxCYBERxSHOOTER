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

CrashEffect::CrashEffect(
    double init_pos_x,
    double init_pos_y
) :
    Effect(
        init_pos_x,
        init_pos_y
    ),
    emit_pos_x(init_pos_x),
    emit_pos_y(init_pos_y),
    start_clock(DxLib::GetNowCount()),
    end_clock(start_clock + EMIT_TIME),
    move_clock(DxLib::GetNowCount())
{
}

void CrashEffect::update() {
    int elapsed_time = DxLib::GetNowCount() - move_clock;
    if (elapsed_time >= EMIT_INTERVAL && DxLib::GetNowCount() <= end_clock) {
        double arg = DxLib::GetRand(360) / 180.0 * pi;
        double speed = INIT_SPEED;
        int circle_or_triangle = DxLib::GetRand(1);
        if (circle_or_triangle == 1) {
            circles.emplace_back(emit_pos_x, emit_pos_y, arg, speed);
        }
        else {
            triangles.emplace_back(emit_pos_x, emit_pos_y, arg, speed);
        }
        move_clock = DxLib::GetNowCount();
    }

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
    size = 10.0;
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

void CrashEffect::Circle::update() {
    LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;
    double distance = speed * update_delta_time / 1000 / 1000;
    double distance_x = distance * cos(arg);
    double distance_y = distance * sin(arg);
    position->x += distance_x;
    position->y += distance_y;
    last_updated_clock = DxLib::GetNowHiPerformanceCount();

}

void CrashEffect::Circle::draw() {
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
    last_updated_clock(DxLib::GetNowHiPerformanceCount())
{
    angle = DxLib::GetRand(24) / 24.0 * pi;
    size = 10.0;
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

void CrashEffect::Triangle::update() {
    LONGLONG update_delta_time = DxLib::GetNowHiPerformanceCount() - last_updated_clock;
    double distance = speed * update_delta_time / 1000 / 1000;
    double distance_x = distance * cos(arg);
    double distance_y = distance * sin(arg);
    position->x += distance_x;
    position->y += distance_y;
    angle += 1.0 / 12.0 / 48.0 * pi;
    last_updated_clock = DxLib::GetNowHiPerformanceCount();
}

void CrashEffect::Triangle::draw() {
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
