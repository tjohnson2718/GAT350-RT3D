#include "LightComponent.h"
#include "Framework/Actor.h"
#include "Core/StringUtils.h"

namespace nc
{
	CLASS_DEFINITION(LightComponent)

	bool LightComponent::Initialize()
	{
		return true;
	}

	void LightComponent::Update(float dt)
	{
	}

	void LightComponent::SetProgram(const res_t<Program> program, const std::string& name)
	{
		
		program->SetUniform(name + ".type", type);
		program->SetUniform(name + ".position", m_owner->transform.position);
		program->SetUniform(name + ".direction", m_owner->transform.Forward());
		program->SetUniform(name + ".color", color);
		program->SetUniform(name + ".intensity", intensity);
		program->SetUniform(name + ".range", range);
		program->SetUniform(name + ".innerAngle", glm::radians(innerAngle));
		program->SetUniform(name + ".outerAngle", glm::radians(outerAngle));

		if (castShadow)
		{
			glm::mat4 bias = glm::mat4(
				glm::vec4(0.5f, 0.0f, 0.0f, 0.0f),
				glm::vec4(0.0f, 0.5f, 0.0f, 0.0f),
				glm::vec4(0.0f, 0.0f, 0.5f, 0.0f),
				glm::vec4(0.5f, 0.5f, 0.5f, 1.0f));

			program->SetUniform("shadowVP", bias * GetShadowMatrix());
			program->SetUniform("shadowBias", shadowBias);
		}
	}

	void LightComponent::ProcessGui()
	{
		const char* types[] = { "Point", "Directional", "Spot" };
		ImGui::Combo("Type", (int*)(&type), types, 3);

		if (type == Spot)
		{
			ImGui::DragFloat("Inner Angle", &innerAngle, 1, 0, outerAngle);
			ImGui::DragFloat("Outer Angle", &outerAngle, 1, innerAngle, 90);
		}

		ImGui::ColorEdit3("Color", glm::value_ptr(color));
		ImGui::DragFloat("Intensity", &intensity, 0.1f, 0, 10);
		if (type != Directional) ImGui::DragFloat("Range", &range, 0.1f, 0.1f, 50);

		ImGui::Checkbox("Cast Shadow", &castShadow);
		if (castShadow)
		{
			ImGui::DragFloat("Shadow Size", &shadowSize, 0.1f, 1, 60);
			ImGui::DragFloat("Shadow Bias", &shadowBias, 0.001f, 0, 1);
		}

	}

	glm::mat4 LightComponent::GetShadowMatrix()
	{
		glm::mat4 projection = glm::ortho(-shadowSize * 0.5f, shadowSize * 0.5f, -shadowSize * 0.5f, shadowSize * 0.5f, 0.1f, 50.0f);
		glm::mat4 view = glm::lookAt(m_owner->transform.position, m_owner->transform.position + m_owner->transform.Forward(), glm::vec3{ 0, 1, 0 });

		return projection * view;
	}

	void LightComponent::Read(const nc::json_t& value)
	{
		// read json file
		std::string lightTypeName;
		READ_NAME_DATA(value, "lightType", lightTypeName);
		if (StringUtils::IsEqualIgnoreCase(lightTypeName, "point")) type = eType::Point;
		else if (StringUtils::IsEqualIgnoreCase(lightTypeName, "directional")) type = eType::Directional;
		else if (StringUtils::IsEqualIgnoreCase(lightTypeName, "spot")) type = eType::Spot;

		READ_DATA(value, color);
		READ_DATA(value, intensity);
		READ_DATA(value, range);
		READ_DATA(value, innerAngle);
		READ_DATA(value, outerAngle);
		READ_DATA(value, castShadow);
	}
}