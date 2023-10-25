#include "ModelComponent.h"
#include "Framework/Actor.h"
#include "Framework/Resource/ResourceManager.h"

namespace nc
{
	CLASS_DEFINITION(ModelComponent)

	bool ModelComponent::Initialize()
	{
		//if (!modelName.empty()) model = GET_RESOURCE(Model, modelName);

		return true;
	}

	void ModelComponent::Update(float dt)
	{
	}

	void ModelComponent::Draw(Renderer& renderer)
	{
		//m_model->Draw(renderer, m_owner->transform);
	}

	void ModelComponent::Read(const json_t& value)
	{
		READ_DATA(value, modelName);
	}
}
