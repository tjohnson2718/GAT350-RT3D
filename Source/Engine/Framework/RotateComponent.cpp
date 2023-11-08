#include "RotateComponent.h"
#include "Actor.h"

namespace nc
{
	CLASS_DEFINITION(RotateComponent);

	bool RotateComponent::Initialize()
	{
		return true;
	}

	void RotateComponent::Update(float dt)
	{
		glm::quat rotation = EulerToQuaternion(euler * dt);
		m_owner->transform.rotation = m_owner->transform.rotation * rotation;
	}

	void RotateComponent::ProcessGui()
	{
		ImGui::DragFloat("x", &euler.x);
		ImGui::DragFloat("y", &euler.y);
		ImGui::DragFloat("z", &euler.z);
	}

	void RotateComponent::Read(const json_t& value)
	{
		// I don't know what to read in here
		READ_DATA(value, euler);
	}
}