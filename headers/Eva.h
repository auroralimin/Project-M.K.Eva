#pragma once

#include "Vec2.h"
#include "GameObject.h"
#include "AnimationFSM.h"

/***************************************************************************//**
 * The representation of the game main character object.
 * Eva used the game engine to implement a lot of actions, including moving and
 * changing class.
 ******************************************************************************/
class Eva : public GameObject
{
	public:
		/**
		 * Enum to represent eva's classes.
		 */
        enum Classes {
            BASE = 0, DECKER, GUNSLINGER
		};

		/**
		 * Default initializes an empty AnimationFSM, and initializes member
		 * variables with default values.
		 */
		Eva();

		/**
		 * Initializes Eva with parameters.
		 * @param x position of eva in the x axis
		 * @param y position of eva in the y axis
		 * @param files[] a array of strings paths to the animation sprite sheets
		 * @param frameCount number of frames for the spritesheets
		 * @param frameTime duration of each frame
		 */
		Eva(Vec2 pos, std::string *files, int frameCount = 1, float frameTime = 1.0f, int moveSpeed = 3);

		/**
		 * Sets the player pointer back to nullptr.
		 */
		~Eva();

		/**
		 * Renders the current animation.
		 */
		void Render();

		/**
		 * Sets the current animation based on input and updates sprites.
		 * @param dt time elapsed between th current and the last frame
		 */
		void Update(float dt);

		/**
		 * Returns if eva's hp reach 0 or below.
		 * @return returns true if eva's hp reached 0 or below, returns false
		 * otherwise
		 */
		bool IsDead();

		/**
		 * Reacts to a collision.
		 * @param other reference define reaction to the collision
		 */
		void NotifyCollision(GameObject &other);

		/**
		 * Returns if this class is the class indicated by className.
		 * @param className name of the class to be tested
		 * @return if className is equal to this class' name then returns true,
		 * returns false otherwise
		 */
		bool Is(std::string className);

		/**
		 * Reduces eva's hp.
		 * @param dmg value that will be reduced from eva's hp
		 */
		void TakeDamage(int dmg = 1);

		/**
		 * Changes the file from which a given animation sprite will be created
		 * and resets the sprite.
		 * @param index an int argument containing the array file position
		 * @param file new sprite file
		 */
		void SetAnimationFile(int index, std::string file);

		/**
		 * Sets the frameTime and resets all sprites to accomodate the new
		 * frameTime.
		 * @param time value to be attributed to frameTime
		 */
		void SetFrameTime(float time);

		/**
		 * Sets the frameCount and resets all sprites to accomodate the new
		 * frameCount.
		 * @param count value to be attributed to frameCount
		 */
		void SetFrameCount(int count);

		/**
		 * Changes the fileset from which all animations sprites will be created.
		 * @param index an int argument containing the array file position
		 * @param pClass a enum Classes value to represent the class
		 */
		void SetAnimationFileSet(Classes pClass);

		/**
		 * static pointer to the player to be used in interactions.
		 */
		static Eva* player;

	private:
		const std::string classes[3] = {"BASE", "DECKER", "GUN"};
		std::string *files;
		float frameTime;
		int moveSpeed;
		AnimationFSM evaAnimations;
        int currentClass;

		void SetClass(Classes c);
};

