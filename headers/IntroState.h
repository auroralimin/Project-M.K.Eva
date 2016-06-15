#pragma once

#include "State.h"
#include "LevelMap.h"
#include "GameObject.h"

/***************************************************************************//**
 * Intro level managment state.
 ******************************************************************************/
class IntroState : public State
{
	public:
		/**
		 * Initialises a Intro State loading intro map and Eva character.
		 */
		IntroState(void);

		/**
		 * Sets room based on EVa position on the map.
		 * @param dt time elapsed between th current and the last frame
		 */
		void Update(float dt);

		/**
		 * Renders map room and state list of objects.
		 */
		void Render(void);

		/**
		 * Do nothing. It is necessary to inherit from State.
		 */
		void Pause(void);

		/**
		 * Do nothing. It is necessary to inherit from State.
		 */
		void Resume(void);

		/**
		 * Checks if some object is colliding with the current room wall.
		 */
		bool IsCollidingWithWall(GameObject* o);

        void UpdateArray(float dt);

		void CheckMovementCollisions();
	private:
		LevelMap map;
};

