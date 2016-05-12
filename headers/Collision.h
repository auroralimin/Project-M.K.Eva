#include <cmath>
#include <algorithm>

#include "Rect.h"

class Collision {
	public:
		// Observação: IsColliding espera ângulos em radianos!
		// Para usar graus, forneça a sua própria implementação de Rotate,
		// ou transforme os ângulos no corpo de IsColliding.
		static inline bool IsColliding(Rect& a, Rect& b, float angleOfA, float angleOfB)
		{
			Vec2 A[] =
			{
				Vec2(a.pos.x, a.pos.y + a.dim.y),
				a.pos + a.dim,
				Vec2(a.pos.x + a.dim.x, a.pos.y),
				a.pos
			};

			Vec2 B[] =
			{
				Vec2(b.pos.x, b.pos.y + b.dim.y),
				b.pos + b.dim,
				Vec2(b.pos.x + b.dim.x, b.pos.y),
				b.pos
			};

			for (auto& v : A)
				v = (v - a.GetCenter()).Rotate(angleOfA) + a.GetCenter();

			for (auto& v : B)
				v = (v - b.GetCenter()).Rotate(angleOfB) + b.GetCenter();

			Vec2 axes[] =
			{
				(A[0] - A[1]).Norm(),
				(A[1] - A[2]).Norm(),
				(B[0] - B[1]).Norm(),
				(B[1] - B[2]).Norm()
			};

			for (auto& axis : axes)
			{
				float P[4];

				for (int i = 0; i < 4; ++i)
					P[i] = A[i].Dot(axis);

				float minA = *std::min_element(P, P + 4);
				float maxA = *std::max_element(P, P + 4);

				for (int i = 0; i < 4; ++i)
					P[i] = B[i].Dot(axis);

				float minB = *std::min_element(P, P + 4);
				float maxB = *std::max_element(P, P + 4);

				if (maxA < minB || minA > maxB)
					return false;
			}

			return true;
		}
};

