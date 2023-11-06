#include "Transform.h"
#include "Renderer/Gui.h"

namespace nc
{
	void Transform::ProcessGui()
	{
		ImGui::DragFloat3("Position", glm::value_ptr(position), 0.1f);
		if (ImGui::DragFloat3("Rotation", glm::value_ptr(euler), 0.1f))
		{
			rotation = EulerToQuaternion(euler);
		}
		ImGui::DragFloat3("Scale", glm::value_ptr(scale));
	}

	void Transform::Read(const json_t& value)
	{
		READ_DATA(value, position);
		READ_DATA(value, scale);
		READ_NAME_DATA(value, "rotation", euler);

		rotation = EulerToQuaternion(euler);
	}
}
