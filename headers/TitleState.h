#include "State.h"
#include "Sprite.h"
#include "Text.h"
#include "Timer.h"
#include "Cutscene.h"

class TitleState : public State
{
	public:
		TitleState(void);
		void Update(float dt);
		void Render(void);
		void Pause(void);
		void Resume(void);
        bool IsCollidingWithWall(GameObject *obj);
        void CheckMovementCollisions(void);

	private:
        Cutscene cutscene, titleFadeIn;
		Sprite title, msg;
		Timer timer;
};

