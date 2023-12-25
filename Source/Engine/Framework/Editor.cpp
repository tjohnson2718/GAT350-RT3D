#include "Editor.h"
#include "Scene.h"
#include "Components/CameraComponent.h"
namespace nc
{
	void Editor::Update()
	{
		if (ImGui::IsKeyPressed(ImGuiKey_GraveAccent)) m_active = !m_active;
	}

	void Editor::ProcessGui(Scene* scene)
	{
		if (!m_active) return;

		// set seperator widget to yellow to stand out
		ImGui::PushStyleColor(ImGuiCol_SeparatorActive, ImVec4{ 1, 1, 0, 1 });

		// Show Resources
		ImGui::Begin("Resources");

		//models
		if (ImGui::CollapsingHeader("Models"))
		{
			auto resources = GET_RESOURCES(Model);
			for (auto& resource : resources)
			{
				if (ImGui::Selectable(resource->name.c_str(), resource.get() == m_selected)) m_selected = resource.get();
			}
		}

		// Shaders
		if (ImGui::CollapsingHeader("Shaders"))
		{
			auto resources = GET_RESOURCES(Shader);
			for (auto& resource : resources)
			{
				if (ImGui::Selectable(resource->name.c_str(), resource.get() == m_selected)) m_selected = resource.get();
			}
		}

		// materials
		if (ImGui::CollapsingHeader("Materials"))
		{
			auto resources = GET_RESOURCES(Material);
			for (auto& resource : resources)
			{
				if (ImGui::Selectable(resource->name.c_str(), resource.get() == m_selected)) m_selected = resource.get();
			}
		}

		// textures
		if (ImGui::CollapsingHeader("Textures"))
		{
			auto resources = GET_RESOURCES(Texture);
			for (auto& resource : resources)
			{
				if (ImGui::Selectable(resource->name.c_str(), resource.get() == m_selected)) m_selected = resource.get();
			}
		}
		ImGui::End();

		// show scene
		ImGui::Begin("Scene");
		scene->ProcessGui();
		ImGui::Separator();

		// show actors
		int index = 0;
		for (auto& actor : scene->m_actors)
		{
			bool done = false;
			ImGui::PushID(index++);

			// rename actor if m_rename is set to an actor
			if (actor.get() == m_rename)
			{
				// set the keyboard to enter input to the InputText
				if (ImGui::IsWindowFocused() && !ImGui::IsAnyItemActive() && !ImGui::IsMouseClicked(0))
					ImGui::SetKeyboardFocusHere(0);

				// create name string from actor name, name string is mutable (can be changed)
				char name[32];
				strcpy_s(name, 32, actor->name.c_str());
				// get input and set new name after return is pressed, clear m_rename to nullptr when done
				if (ImGui::InputText("", name, 32, ImGuiInputTextFlags_EnterReturnsTrue))
				{
					actor->name = name;
					m_rename = nullptr;
				}
			}
			else if (ImGui::Selectable(actor->name.c_str(), actor.get() == m_selected))
			{
				m_selected = actor.get();
			}

			// set rename when selected actor is double-clicked
			if (actor.get() == m_selected && ImGui::IsMouseDoubleClicked(0))
			{
				m_rename = actor.get();
			}

			// show popup menu when actor is right clicked
			if (ImGui::BeginPopupContextItem(actor->name.c_str(), ImGuiPopupFlags_MouseButtonRight))
			{
				if (ImGui::MenuItem("Duplicate"))
				{
					// get the raw pointer of the clone of the actor
					auto newActor = dynamic_cast<Actor*>(actor->Clone().release());
					// check if there is a trailing number on the actor being cloned
					int number = StringUtils::GetTrailingNumber(actor->name);
					// increment the number if a number existed else add "1" to the name
					newActor->name = (number != -1) ? StringUtils::RemoveTrailingNumber(actor->name) + std::to_string(++number) : actor->name + "1";
					m_selected = newActor;

					// add new clone after the actor cloned
					scene->Add(std::unique_ptr<Actor>(newActor), actor.get());
					done = true;
				}
				if (ImGui::MenuItem("Delete"))
				{
					// remove actor
					scene->Remove(actor.get());
					m_selected = nullptr;
					done = true;
				}
				ImGui::EndPopup();
			}
			ImGui::PopID();

			// if done with right-click operation, exit showing actors
			if (done) break;
		}

		// actor creation
		ImGui::BeginChild("ActorCreate");
		if (ImGui::BeginPopupContextWindow())
		{
			auto cameras = scene->GetComponents<CameraComponent>();
			auto camera = (!cameras.empty()) ? cameras[0] : nullptr;

			// create various actors that are prototypes, the actors need to be loaded in the scene file and set as prototypes
			// the "empty" actor does not need a prototype as it creates a basic actor
			// the idea was to add components to the empty actor (add component is not implemented)
			if (ImGui::MenuItem("Create Empty"))
			{
				auto actor = CREATE_CLASS(Actor);
				actor->name = StringUtils::CreateUnique(actor->GetClassName());
				if (camera)	actor->transform.position = camera->m_owner->transform.position + camera->m_owner->transform.Forward() * 3.0f;
				actor->Initialize();
				m_selected = actor.get();
				scene->Add(std::move(actor));
			}
			if (ImGui::MenuItem("Sphere"))
			{
				auto actor = CREATE_CLASS_BASE(Actor, "Sphere");
				actor->name = StringUtils::CreateUnique(actor->name);
				if (camera)	actor->transform.position = camera->m_owner->transform.position + camera->m_owner->transform.Forward() * 3.0f;
				actor->Initialize();
				m_selected = actor.get();
				scene->Add(std::move(actor));

			}
			if (ImGui::MenuItem("Cube"))
			{
				auto actor = CREATE_CLASS_BASE(Actor, "Cube");
				actor->name = StringUtils::CreateUnique(actor->name);
				if (camera)	actor->transform.position = camera->m_owner->transform.position + camera->m_owner->transform.Forward() * 3.0f;
				actor->Initialize();
				m_selected = actor.get();
				scene->Add(std::move(actor));
			}
			if (ImGui::MenuItem("Camera"))
			{
				auto actor = CREATE_CLASS_BASE(Actor, "Camera");
				actor->name = StringUtils::CreateUnique(actor->name);
				if (camera)	actor->transform.position = camera->m_owner->transform.position + camera->m_owner->transform.Forward() * 3.0f;
				actor->Initialize();
				m_selected = actor.get();
				scene->Add(std::move(actor));
			}
			if (ImGui::MenuItem("Light"))
			{
				auto actor = CREATE_CLASS_BASE(Actor, "Light");
				actor->name = StringUtils::CreateUnique(actor->name);
				if (camera)	actor->transform.position = camera->m_owner->transform.position + camera->m_owner->transform.Forward() * 3.0f;
				actor->Initialize();
				m_selected = actor.get();
				scene->Add(std::move(actor));
			}
			ImGui::EndPopup();
		}
		ImGui::EndChild();
		ImGui::End();

		// show selected actor details in the inspector
		ImGui::Begin("Inspector");
		if (m_selected)
		{
			m_selected->ProcessGui();
		}

		// need to pop the style at the end
		ImGui::PopStyleColor();

		ImGui::End();
	}
}

