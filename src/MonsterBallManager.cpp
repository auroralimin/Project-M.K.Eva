#include "MonsterBallManager.h"
#include "Game.h"
#include "Config.h"
#include "Eva.h"

#define IDLE 0
#define ATTACK 1
#define WAR 2

MonsterBallManager::MonsterBallManager(int numBall)
{
	for (int i = 0; i < numBall; i++) {
		float x = Config::Rand(0, Game::GetInstance()->GetWinWidth());
		float y = Config::Rand(0, Game::GetInstance()->GetWinHeight());
		Ball* b = new Ball(Vec2(x, y));
		
		/*while (Game::GetInstance()->GetCurrentState().IsCollidingWithWall(b)) {
			std::cout << "m1" << std::endl;
			x = Config::Rand(0, Game::GetInstance()->GetWinWidth());
			y = Config::Rand(0, Game::GetInstance()->GetWinHeight());
			b->box.pos = Vec2(x, y);
		}

		Game::GetInstance()->GetCurrentState().AddObject(b);*/
		ballArray.push_back(*b);
	}
	b = true;
	state = BallManagerState::RESTING;
}

MonsterBallManager::~MonsterBallManager()
{
}

void MonsterBallManager::Render()
{
}

bool MonsterBallManager::IsDead()
{
	return (ballArray.empty());
}

void MonsterBallManager::Update(float dt)
{
	//gambiarra
	if (b) {
		for (size_t i = 0; i < ballArray.size(); i++) {
			Game::GetInstance()->GetCurrentState().AddObject(&ballArray[i]);
		}
		b = false;
	}
	timer.Update(dt);

	if (state == BallManagerState::RESTING) {
		SwitchSprite(IDLE);

		if (timer.Get() >= Config::Rand(1.8, 3.6)) {
			state = BallManagerState::WARNING;
			timer.Restart();
		} 
	} else if (state == BallManagerState::WARNING) {
		SwitchSprite(WAR);

		if(timer.Get() >= 2.0) {
			state = BallManagerState::ATTACKING;
			timer.Restart();
		}
	} else if (state == BallManagerState::ATTACKING) {
		SwitchSprite(ATTACK);

		for (size_t i = 0; i < ballArray.size(); i++) {
			float angle = 2*M_PI*(i+1)/ballArray.size();
			Vec2 pos = Vec2(50, 0);
			ballArray[i].box.pos = Vec2(pos.x*cos(angle) - pos.y*sin(angle), 
				pos.y*cos(angle) + pos.x*sin(angle));

			ballArray[i].box.pos += Eva::player->box.pos; 
		}

		if (timer.Get() >= 1.8) {
			state = BallManagerState::RESTING;
			RandTeleport();
			timer.Restart();
		}
	}
}

void MonsterBallManager::NotifyCollision(GameObject &other, bool movement)
{
	UNUSED_VAR other;
	UNUSED_VAR movement;
}

bool MonsterBallManager::Is(std::string className)
{
	UNUSED_VAR className;
	return false;
}

void MonsterBallManager::TakeDamage(float dmg)
{
	UNUSED_VAR dmg;
}

void MonsterBallManager::SwitchSprite(int sprite)
{
	for (size_t i = 0; i < ballArray.size(); i++) {
		ballArray[i].SetCurrentSprite(sprite);
	}
}

void MonsterBallManager::RandTeleport()
{
	for (size_t i = 0; i < ballArray.size(); i++) {
		do {		
			float x = Config::Rand(0, Game::GetInstance()->GetWinWidth());
			float y = Config::Rand(0, Game::GetInstance()->GetWinHeight());
			ballArray[i].box.pos = Vec2(x, y);
			//ballArray[i].hitbox.pos = Vec2(box.pos.x + 43, box.pos.y + 110);
		} while (ballArray[i].IsInsideWall());
		
	}
}
