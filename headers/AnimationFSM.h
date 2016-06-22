#pragma once
#include <vector>
#include <memory>

#include "Sprite.h"

/***************************************************************************//**
 * An animation Finite state machine abstraction.
 ******************************************************************************/
class AnimationFSM
{
	public:
		/**
		 * Initializes a FSM instance setting the values to default.
		 */
        AnimationFSM(int nAnimations);

		/**
		 * Initializes a FSM instance given the arguments.
		 * @param files[] an array of string containing the sprites file paths
		 * @param frameCont a int argument containing the animations frameCount
		 * @param frameTime a int argument containing the animations frameTime
		 */
        AnimationFSM(int nAnimations, std::string files[], int frameCount[],
                     float frameTime[]);

		/**
		 * Renders the sprite according to the current state.
		 * @param x a int argument containing the x of the render position
		 * @param y a int argument containing the y of the render position
		 */
		void Render(int x, int y);

		/**
		 * Updates the sprites so the animation happens.
		 * @param dt time passed between frames
		 */
		void Update(float dt);

		/**
		 * Sets the current state of the animation.
		 * @param state the state to become the current state
		 */
        void SetCurrentState(int state);

		/**
		 * Returns the current state of the animation.
		 * @return returns the value of the current state
		 */
        int GetCurrentState(void);

		/**
		 * Sets a animation sprite from the animation vector.
		 * @param index position of animation in the vector
		 * @param file file to be opened
		 * @param frameCount number of frames
		 * @param frameTime duration of each frame
		 */
        void SetAnimation(int index, std::string file, int frameCount,
                          float frameTime);

		/**
		 * Returns the width of a frame.
		 * @return returns sprite width/frameCount
		 */
		int GetCurrentWidth(void);

		/**
		 * Returns the height of a frame.
		 * @return returns sprite height
		 */
		int GetCurrentHeight(void);

        void SetNAnimations(int nAnimations);

	private:
        int nAnimations;
        int currentState;
		std::vector<std::unique_ptr<Sprite>> animationsArray;
};

