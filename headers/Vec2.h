#pragma once

class Vec2
{
	public:
		float x, y;

		Vec2(void);
		Vec2(float x, float y);
		float getModule(void);
		Vec2 normalize(void);
		float distanceFromPoint(Vec2 p);
		Vec2 rotate(float angle);
		float mag(void);
		Vec2 norm(void);
		float dot(Vec2 p);

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

