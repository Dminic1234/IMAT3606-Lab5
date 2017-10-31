#include "Game.h"
#include "TransformComponent.h"
#include "ColourComponent.h"
#include <fstream>
#include <sstream>

Game::Game()
{
	m_engineInterfacePtr = nullptr;
	m_inputHandler = new InputHandler(&m_playerCube);

	m_playerBackground.addComponent(new RedComponent);
	m_playerBackground.addComponent(new GreenComponent);
	m_playerBackground.addComponent(new BlueComponent);

	m_playerCube.addComponent(new TransformComponent);
	
	// move the cube
	TransformComponent* temp = m_playerCube.getComponent<TransformComponent>();
	temp->translate(0, 0, -5);
}

void Game::update()
{
	
}

void Game::render()
{
	float redValue = 0, greenValue = 0, blueValue = 0;
	if(m_playerBackground.getComponent<RedComponent>())
		redValue = m_playerBackground.getComponent<RedComponent>()->m_colourValue;
	if (m_playerBackground.getComponent<GreenComponent>())
		greenValue = m_playerBackground.getComponent<GreenComponent>()->m_colourValue;
	if (m_playerBackground.getComponent<BlueComponent>())
		blueValue = m_playerBackground.getComponent<BlueComponent>()->m_colourValue;
	
	// e.g. pass object details to the engine to render the next frame
	m_engineInterfacePtr->renderColouredBackground(redValue, greenValue, blueValue);

	// update the camera (probably don't need to do this each frame)
	m_engineInterfacePtr->setCamera(&m_camera);

	// draw the cube
	m_engineInterfacePtr->drawCube(m_playerCube.getComponent<TransformComponent>()->getModelMatrix());
	
}
