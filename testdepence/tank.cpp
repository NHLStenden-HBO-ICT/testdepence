#include "pch.h"
#include "tank.h"

#include "pch.h"
#include "tank.h"
#include <mutex>

Tank::Tank(
    float pos_x,
    float pos_y,
    allignments allignment,
    Sprite* tank_sprite,
    Sprite* smoke_sprite,
    float tar_x,
    float tar_y,
    float collision_radius,
    int health,
    float max_speed,
    vec2 siz)
    : position(pos_x, pos_y),
    allignment(allignment),
    target(tar_x, tar_y),
    health(health),
    collision_radius(collision_radius),
    max_speed(max_speed),
    force(0, 0),
    reload_time(1),
    reloaded(false),
    speed(0),
    active(true),
    current_frame(0),
    tank_sprite(tank_sprite),
    smoke_sprite(smoke_sprite)
{
    this->size = siz;
    //second part is half size /size /2
    //this->hitBox = DirectX::BoundingBox(DirectX::XMFLOAT3(position.x, position.y, 0), DirectX::XMFLOAT3(collision_radius, collision_radius, 0));
}

Tank::~Tank()
{
}

void Tank::tick()
{
    //runtime vec2 == cach miss
    //due to dynamic memory each tick and each tick will a potenial growing devide between the object and this value
    direction = vec2(0, 0); // is null nog erger

    //branch miss since this will only happen in about frame 1900
    if (target != position)
    {
        direction = (target - position).normalized();
    }
    speed = direction + force;
    //micro optima but we can calulate maxspeed at compile time
    position += speed * max_speed * 0.5f;
    
    //Update reload time
    if (--reload_time <= 0.0f)
    {
        reloaded = true;
    }
    //empty vec2
    force = vec2(0.f, 0.f);

    //Target reached?
    if (current_route.size() > 0)
    {
        vec2 diff = (position - target);
        if (std::sqrt(diff.x * diff.x + diff.y * diff.y) < 10.1) {
            target = *current_route[0] * 16;
            current_route.erase(current_route.begin());
        }
    }
}


//Start reloading timer
void Tank::reload_rocket()
{
    reloaded = false;
    reload_time = 200.0f;
}

void Tank::deactivate()
{
    active = false;
}

//Remove health
bool Tank::hit(int hit_value)
{
    health -= hit_value;

    if (health <= 0)
    {
        this->deactivate();
        return true;
    }

    return false;
}
//void Tank::set_route(std::vector<vec2> route)
//{
//    if (route.size() > 0)
//    {
//        current_route = route;
//        target = current_route.at(0);
//        current_route.erase(current_route.begin());
//    }
//    else
//    {
//        target = position;
//    }
//}


void Tank::set_route(std::vector<vec2*> route)
{
    if (route.size() > 0)
    {
        current_route = route;
        target = *current_route.at(0) * 16;
        current_route.erase(current_route.begin());
        if (id > 610) {
            int stophere = 10;
        }
    }
    else
    {
        target = position;
    }
}


//The old draw system
//This version just needs to return the sprite upon a drawcall
//Draw the sprite with the facing based on this tanks movement direction
void Tank::draw(Surface* screen)
{
    vec2 direction = (target - position).normalized();
    //tank_sprite->set_frame(((abs(direction.x) > abs(direction.y)) ? ((direction.x < 0) ? 3 : 0) : ((direction.y < 0) ? 9 : 6)) + (current_frame / 3));
    //data used to draw the sprite
    //tank_sprite->draw(screen, (int)position.x - 7 + HEALTHBAR_OFFSET, (int)position.y - 9);
}

int Tank::compare_health(const Tank& other) const
{
    return ((health == other.health) ? 0 : ((health > other.health) ? 1 : -1));
}

//Add some force in a given direction
void Tank::push(vec2 direction, float magnitude)
{
    force += direction * magnitude;
}