#pragma once

#include <ContainerTypes.h>
#include <Sprite.h>
#include <Hull.h>
#include <vector>
#include <DirectXCollision.h>
#include "Sprite.h"
//#include <TerrainM.h>
//this is a tank
//some call is ifv
//but it depends on the role within the army 
//just like a method
//when i name a method minus and within it i do a additon
//well it isn't a minus at all!!!

enum allignments
{
    BLUE,
    RED,
    NOTHING
};
class Tank
{


    //collison and drawing is based on minmax
public:
    Tank(float pos_x, float pos_y, allignments allignment, Sprite* tank_sprite, Sprite* smoke_sprite, float tar_x, float tar_y, float collision_radius, int health, float max_speed, vec2 siz);

    ~Tank();
    //add replacer for durface
    void tick();
    //was const
    //vec2 should exist
    vec2 get_position() const { return position; };

    vec2 direction = vec2(0, 0);
    float get_collision_radius() const { return collision_radius; };
    bool rocket_reloaded() const { return reloaded; };
    void set_route(std::vector<vec2*> route);
    void reload_rocket();

    void deactivate();
    bool hit(int hit_value);
    void draw(Surface* screen);

    int id;
    int compare_health(const Tank& other) const;

    void push(vec2 direction, float magnitude);
    //collision is done by min max
    //will be optimized
    vec2 position;

    vec2 speed;
    vec2 target;
    vec2 size;
    //DirectX::BoundingBox hitBox = DirectX::BoundingBox(DirectX::XMFLOAT3(0, 0, 0), DirectX::XMFLOAT3());
    //QuadTree ointertest;

    std::vector<vec2*> current_route;

    int health;

    float collision_radius;
    vec2 force;

    float max_speed;
    float reload_time;

    bool reloaded;
    bool active;

    //quadTreeData* localContainer = nullptr;
    allignments allignment;

    int current_frame;
    Sprite* tank_sprite;
    Sprite* smoke_sprite;
};

