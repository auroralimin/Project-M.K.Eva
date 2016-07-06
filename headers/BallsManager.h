#pragma once

#include <vector>

#include "BallMonster.h"
#include "Timer.h"

class BallsManager : public GameObject
{
  public:
    BallsManager(Room *room, GameObject *focus);
    BallMonster **AddBall(void);
    void Render();
    bool IsDead();
    void Update(float dt);
    void NotifyCollision(GameObject &other, bool movement);
    bool Is(std::string className);
    void TakeDamage(float dmg = 1);

  private:
    enum BallsState { RESTING, WARNING, ATTACKING };

    Room *room;
    GameObject *focus;
    unsigned int currentState;
    std::vector<BallMonster *> ballArray;
    Timer timer;

    void SetCurrentState(int state);
    void RandTeleport();
    void ClearDeadBalls();
};

