#pragma once
#include <vector>
#include <memory>

#include "GameObject.h"

class State
{
	public:
		State(void);
		virtual ~State() {};
		virtual void Update(float dt) = 0;
		virtual void Render(void) = 0;
		virtual void Pause(void) = 0;
		virtual void Resume(void) = 0;
		virtual void AddObject(GameObject *obj);
		bool IsPopRequested(void);
		bool IsQuitRequested(void);

	protected:
		bool popRequested, quitRequested;
		std::vector<std::unique_ptr<GameObject>> objectArray;

		virtual void UpdateArray(float dt);
		virtual void RenderArray(void);
};

