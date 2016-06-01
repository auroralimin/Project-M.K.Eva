#pragma once

#include "Vec2.h"

/***************************************************************************//**
 * It is an abstraction of a rectangle.
 ******************************************************************************/
class Rect
{
	public:
		/**
		 * Contains the retangle position.
		 */
		Vec2 pos;

		/**
		 * Contains the retangle dimention (x = width and y = height).
		 */
		Vec2 dim;


		/**
		 * Initialises all Vec2 attributes with 0.0.
		 */
		Rect(void);

		/**
		 * Initialises all attributes given the arguments received.
		 * @param pos a Vec2 argument contaning the Rect position
		 * @param dim a Vec2 argument contaning the Rect dimention
		 */
		Rect(Vec2 pos, Vec2 dim);

		/**
		 * Sums position with the given Vec2.
		 * @param v a Vec2 argument that will be added a position
		 */
		void SumWithVec2(Vec2 v);

		/**
		 * Checks if the retangle is inside a given area.
		 * @param area a Vec2 argument representating an area.
		 */
		bool IsInside(Vec2 area);

		/**
		 * Gets retangle center.
		 * @return A vec2 containing coordinates to the retangle center
		 */
		Vec2 GetCenter(void);

		/*
		 * Renders a red filled rectangle to represent the rect instance.
		 */
		void RenderFilledRect(void);
};

