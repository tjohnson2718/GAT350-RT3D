#pragma once
#include "Core/Json.h"
#include "MathUtils.h"
#include <glm/glm/glm.hpp>
#include <glm/glm/gtx/transform.hpp>
#include <glm/glm/gtx/euler_angles.hpp>
#include <glm/glm/gtc/type_ptr.hpp>

namespace nc
{
	class Transform
	{
	public:
		glm::vec3 position{ 0 };
		glm::quat rotation{ glm::vec3{ 0 } };
		glm::vec3 scale{ 1 };

		glm::vec3 euler{ 0 };

	public:
		Transform() = default;
		Transform(const glm::vec3& position, const glm::quat& rotation = glm::vec3{ 0 }, glm::vec3 scale = glm::vec3{1}) :
			position{ position },
			rotation{ rotation },
			scale{ scale },
			euler{ QuaternionToEuler(rotation) }
		{}

		glm::mat4 GetMatrix() const
		{
			glm::mat4 ms = glm::scale(scale);
			glm::mat4 mr = glm::mat4_cast(rotation);
			glm::mat4 mt = glm::translate(position);
			glm::mat4 mx = mt * ms * mr;

			return mx;
		}

		glm::vec3 Forward() { return rotation * glm::vec3{ 0, 0, 1 }; }
		glm::vec3 Right() { return rotation * glm::vec3{ 1, 0, 0 }; }
		glm::vec3 Up() { return rotation * glm::vec3{ 0, 1, 0 }; }

		void ProcessGui();

		void Read(const json_t& value);
	};
}