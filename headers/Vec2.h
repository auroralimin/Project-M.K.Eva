#pragma once

/***************************************************************************//**
 * It is an abstraction of a 2D vector
 ******************************************************************************/
class Vec2
{
	public:
		/**
		 * Saves Vec2 x coordinate.
		 */
		float x;

		/**
		 * Saves Vec2 y coordinate.
		 */
		float y;


		/**
		 * Initialises both coordinates with zero.
		 */
		Vec2(void);

		/**
		 * Initialises both coordinates with given values.
		 * @param x a float argument with coordinate x value
		 * @param y a float argument with coordinate y value
		 */
		Vec2(float x, float y);

		/**
		 * Calculates the vector module.
		 * @return Returns vector mudule
		 */
		float GetModule(void);

		/**
		 * Calculates the vector normal.
		 * @return Returns the normal vector
		 */
		Vec2 Normalize(void);

		/**
		 * Calculates the vector distance from a given vector.
		 * @param p a Vec2 argument with the vector that the distance will be calculated
		 * @return Returns the distance between the vectors
		 */
		float DistanceFromPoint(Vec2 p);

		/**
		 * Calculates the vector rotation.
		 * @param angle a float argument with the rotation
		 * @return Returns the rotated vector
		 */
		Vec2 Rotate(float angle);

		/**
		 * Calculates the vector magnitude.
		 * @return Returns the vector magnitude
		 */
		float Mag(void);

		/**
		 * Calculates the vector norm.
		 * @return Returns the norm vector
		 */
		Vec2 Norm(void);

		/**
		 * Calculates the dot product between this vector and the given vector
		 * @param p a Vec2 argument with the other vector
		 * @return Returns the product result
		 */
		float Dot(Vec2 p);

		Vec2 operator+(const Vec2& v)
		{
			return Vec2(x + v.x, y + v.y);
		}

		Vec2 operator+=(const Vec2& v)
		{
			x += v.x, y += v.y;
			return *this;
		}

		Vec2 operator-(const Vec2& v)
		{
			return Vec2(v.x - x, v.y - y);
		}

		Vec2 operator-=(const Vec2& v)
		{
			x -= v.x, y -= v.y;
			return *this;
		}

		Vec2 operator*(const Vec2& v)
		{
			return Vec2(x*v.x, y*v.y);
		}

		Vec2 operator*(const float n)
		{
			return Vec2(x*n, y*n);
		}

		Vec2 operator*=(const Vec2& v)
		{
			x *= v.x, y *= v.y;
			return *this;
		}

		Vec2 operator*=(const float n)
		{
			x *= n, y *= n;
			return *this;
		}

		Vec2 operator/(const float n)
		{
			return Vec2(x/n, y/n);
		}

		Vec2 operator/=(const float n)
		{
			x /= n, y /= n;
			return *this;
		}
};

