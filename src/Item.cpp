#include "Item.h"
#include "Config.h"

Item::Item(std::string name, Vec2 pos) : sp("img/item/" + name + ".png"),
    name(name), isDead(false)
{
    box.pos = hitbox.pos = pos;
    box.dim.x = hitbox.dim.x = sp.GetWidth();
    box.dim.y = hitbox.dim.y = sp.GetHeight();
}

void Item::Render(void)
{
    sp.Render(box.pos.x - box.dim.x / 2, box.pos.y - box.dim.y / 2);
}

void Item::Update(float dt)
{
    UNUSED_VAR dt;
    //do nothing
}

bool Item::IsDead(void)
{
    return isDead;
}

void Item::NotifyCollision(GameObject &other, bool movement)
{
    UNUSED_VAR movement;
    if (other.Is("Eva")){
        std::cout << "Picked up: " << name << std::endl;
        isDead = true;
    }
}

bool Item::Is(std::string className)
{
    return (className == name);
}

void Item::TakeDamage(float dmg)
{
    UNUSED_VAR dmg;
    //do nothing
}

