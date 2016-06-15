#include "MonsterBallManager.h"
#include "Game.h"
#include "Config.h"

MonsterBallManager(int numBall)
{
	for (int i = 0; i < numBall; i++) {
		float x = Config::Rand(0, Game::GetInstance()->GetWinWidth());
		float y = Config::Rand(0, Game::GetInstance()->GetWinHeight());
		Ball* b = new Ball(Vec2(x, y));
		
		while (b.IsInsideWall) {
			x = Config::Rand(0, Game::GetInstance()->GetWinWidth();
			y = Config::Rand(0, Game::GetInstance()->GetWinHeight());
			b->box.pos = Vec2(x, y);
		}

		Game::GetInstance()->GetCurrentState().AddObject(b);
		ballArray.emplace_back(b);
	}
}

~MonsterBallManager()
{
}

void Render()
{
}

bool IsDead()
{
}

void Update(float dt)
{
}

void NotifyCollision(GameObject &other, bool movement)
{
}

bool Is(std::string className)
{
}

void TakeDamage(float dmg = 1)
{
}
