#pragma once

#include "Vector.h"

namespace aengine {

	class Mathf {
	public:
		/// <summary>
		/// Based on angle tangent returns a vectorf
		/// with scale of 1 for the corresponding angle.
		/// </summary>
		static Vectorf tanToVector(float tangent);

		/// <summary>
		/// Returns -1 or 1 depending on sign of val
		/// </summary>
		static int sign(float val);

		static float clamp(float value, float min, float max);

		static float clampMin(float value, float min);

		static float clampMax(float value, float max);

		static float repeat(float value, float min, float max);

		static float remainder(float value, float divider);
	};
}