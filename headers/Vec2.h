#pragma once

class Vec2
{
	public:
		float x, y;

		Vec2(void);
		Vec2(float x, float y);
		float GetModule(void);
		Vec2 Normalize(void);
		float DistanceFromPoint(Vec2 p);
		Vec2 Rotate(float angle);
		float Mag(void);
		Vec2 Norm(void);
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

