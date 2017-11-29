#pragma once
#include "IEngineCore.h"
#include "InputHandler.h"
#include "GameObject.h"
#include "Camera.h"

class Game
{
public:
	Game();
	IEngineCore* m_engineInterfacePtr;

	InputHandler* m_inputHandler;

	void update();
	void render();

	void loadLevel(std::string levelFile);

private:
	GameObject m_playerBackground;
	GameObject m_playerCube;
	GameObject m_playerCube2;
	std::vector<GameObject> v_playerCubes;
	std::string s;//stores line froma text file
	float x, y, z;
	std::vector<int> g_inVector;
	int iNumElements;
	Camera m_camera;
};
