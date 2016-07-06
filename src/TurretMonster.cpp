#include "TurretMonster.h"
#include "Eva.h"
#include "Bullet.h"
#include "Game.h"
#include "Config.h"
#include "Timer.h"
#include "Animation.h"
#include "InputManager.h"

#define TURRET_ANIMATIONS 1

TurretMonster::TurretMonster(Room *room, Vec2 pos, GameObject *focus) :
    focus(focus)
{
    this->room = room;
    std::string files[TURRET_ANIMATIONS] = {
        "sprites/monsters/turret/SpriteSheetStationaryTurret.png"};
    int frameCounts[TURRET_ANIMATIONS] = {20};
    float frameTimes[TURRET_ANIMATIONS] = {0.1};
    animations = AnimationFSM(TURRET_ANIMATIONS, files, frameCounts, frameTimes);

    box.pos = pos;
    box.dim = Vec2(animations.GetCurrentWidth(), animations.GetCurrentHeight());
    hitbox.dim = Vec2(box.dim.x/2, box.dim.y/4);
    hitbox.pos = Vec2(box.pos.x + box.dim.x/4, box.pos.y + box.dim.y/1.5);
    attackHitbox.dim = Vec2(box.dim.x/2, box.dim.y/1.5);
    attackHitbox.pos = Vec2(box.pos.x + box.dim.x/4, box.pos.y + box.dim.y/4);
    hp = 100;
    rotation = 0;
}

void TurretMonster::Update(float dt)
{
    static Timer timer = Timer();
    InputManager &manager = InputManager::GetInstance();

    if (manager.KeyPress(H_KEY)) { // temporary suicide button
        TakeDamage(8000);
    }

    if (timer.Get() >= 2.5f) {
        ShootPattern1();
        timer.Restart();
    }

    animations.Update(dt);
    timer.Update(dt);
}

void TurretMonster::NotifyCollision(GameObject &other, bool movement)
{
    UNUSED_VAR movement;

    if (other.Is("Bullet") || other.Is("Attack")) {
        Bullet &bullet = (Bullet &)other;
        if (!bullet.targetsPlayer) {
            TakeDamage(10);
        }
    }
}

bool TurretMonster::Is(std::string className)
{
    return ("TurretMonster" == className);
}

void TurretMonster::TakeDamage(float dmg)
{
    hp -= dmg;
    std::cout << "turret: " << hp << std::endl;
    if (IsDead()) {
        Game::GetInstance()->GetCurrentState().AddObject(new Animation(
            box.GetCenter(), 0, "sprites/monsters/turret/penguindeath.png", 5,
            0.3, true));
        //ShootPattern2();
    }
}

void TurretMonster::ShootPattern1(void)
{
    const int nBullets = 3;
    Vec2 evaPos = focus->box.GetCenter();
    float angle = 0;

    evaPos -= box.GetCenter();
    angle = atan2(evaPos.y, evaPos.x);
    float anglesOffsets[nBullets] = {0.0, 0.3, -0.3};

    for (int i = 0; i < nBullets; ++i)
        Game::GetInstance()->GetCurrentState().AddObject(
            new Bullet(box.GetCenter(), angle + anglesOffsets[i], 200, 1000,
                       "sprites/monsters/projectiles/BlueBombSpritesheet.png",
                       Vec2(-10, -10), Vec2(20, 20), 8, 0.3, true));
}

void TurretMonster::ShootPattern2(void)
{
    for (int i = 0; i < 15; i++) {
        Bullet *b =
            new Bullet(box.GetCenter(), 2 * M_PI * (i + 1) / 15, 200, 1000,
                       "sprites/monsters/projectiles/GreatEnergyBallSpriteSheet.png",
                       Vec2(-35, -35), Vec2(70, 70), 4, 0.3, true);

        Game::GetInstance()->GetCurrentState().AddObject(b);
    }
}

