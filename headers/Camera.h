#pragma once
#include "GameObject.h"
#include "Vec2.h"

/***************************************************************************//**
 * Static class that implements the game camera mechanism.
 * This mechanism can follow the player or can be relative to the map.
 ******************************************************************************/
class Camera
{
	public:
		/** 
		 * Contains the camera position.
		 */
		static Vec2 pos;

		/** 
		 * Contains the camera movement speed.
		 */
		static Vec2 speed;


		/** 
		 * Makes the camera follow a given object.
		 * @param *newFocus a GameObject pointer to the object to be followed
		 */
		static void Follow(GameObject *newFocus);

		/** 
		 * Makes the camera stop following its targeted object.
		 */
		static void Unfollow(void);

		/** 
		 * Updates the camera.
		 * It can be done either by following a targeted object or
		 * by moving according to inputs and considering the limits of the map.
		 */
		static void Update(float dt, int mapWidth, int mapHeight);

	private:
		static GameObject *focus;
};

