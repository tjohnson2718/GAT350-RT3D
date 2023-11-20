#pragma once

namespace nc
{

	class Editor
	{
	public:
		void ProcessGui(class Scene* scene);

	private:
		class Object* m_selected = nullptr;
	};
}