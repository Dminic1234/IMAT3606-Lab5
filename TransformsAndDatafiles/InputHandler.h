#pragma once
#include <map>
#include "GameObject.h"
#include <vector>
#include "TransformComponent.h"


class InputCommand
{
public:
	virtual ~InputCommand() {}
	virtual void execute(GameObject& playerBackground) = 0;
};

class RotateRightCommand : public InputCommand
{
	void execute(GameObject& m_playerCube) override{
		if (m_playerCube.getComponent<TransformComponent>())
		{
			m_playerCube.getComponent<TransformComponent>()->OnMessage("Rotate right");
		}
	}
};

class RotateLeftCommand : public InputCommand
{
	void execute(GameObject& m_playerCube) override{
		if (m_playerCube.getComponent<TransformComponent>())
		{
			m_playerCube.getComponent<TransformComponent>()->OnMessage("Rotate left");
		}
	}
};

class TranslateRightCommand : public InputCommand
{
	void execute(GameObject& m_playerCube) override {
		if (m_playerCube.getComponent<TransformComponent>())
		{
			m_playerCube.getComponent<TransformComponent>()->OnMessage("Translate right");
		}
	}
};

class TranslateLeftCommand : public InputCommand
{
	void execute(GameObject& m_playerCube) override {
		if (m_playerCube.getComponent<TransformComponent>())
		{
			m_playerCube.getComponent<TransformComponent>()->OnMessage("Translate left");
		}
	}
};

//e.g. class RotateLeftCommand : public InputCommand


struct InputHandler
{	
	GameObject* m_playerCube;

	std::map<int, InputCommand*> m_controlMapping;

	InputHandler(GameObject* playerCube) : m_playerCube(playerCube)
	{
		// the idea will be to map the keys directly from a config file that can be loaded in
		// and changed on the fly
		//A Z S X
		//TransformComponent::rotate(0.1f, glm::vec3(1, 1, 1));
		//m_playerCube->getComponent<TransformComponent>();
		m_controlMapping[65] = new RotateLeftCommand;
		m_controlMapping[90] = new RotateRightCommand;
		m_controlMapping[83] = new TranslateLeftCommand;
		m_controlMapping[88] = new TranslateRightCommand;
	}

	void handleInputs(const std::vector<bool>& keyBuffer)
	{
		for(const auto& mapEntry : m_controlMapping)
		{
			if(keyBuffer[mapEntry.first])
			{
				mapEntry.second->execute(*m_playerCube);
			}
		}

	}
};
