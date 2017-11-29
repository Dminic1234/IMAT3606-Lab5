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
	m_playerCube2.addComponent(new TransformComponent);

	loadLevel("assets/levels/myCubeLevel.txt");
	// move the cube
	/*TransformComponent* temp = m_playerCube.getComponent<TransformComponent>();
	temp->translate(0, 0, -5);
	TransformComponent* temp2 = m_playerCube2.getComponent<TransformComponent>();
	temp2->translate(2, 0, -5);*/
}

void Game::update()
{
	
}
void Game::loadLevel(std::string textFile)
{
	std::ifstream inputFile;
	std::getline(inputFile, s);
	std::stringstream ss;
	ss.str(s);
	//ss.ignore(17); //ignore the first 17 chars to get number of cubes
	ss >> iNumElements;
	//Resize the vector to the correct size
	g_inVector.resize(5);
	ss.clear();

	for (int i = 0; i < 5; i++)
	{
		//use a stringstream to get int values
		getline(inputFile, s);
		ss.clear();
		ss.str(s);
		ss >> g_inVector[i];
		for (std::vector<int>::const_iterator i = g_inVector.begin(); i != g_inVector.end(); ++i)
		{
			std::cout << *i << std::endl;
		}
	}


	/*ss.str(s);
	ss >> x >> y >> z;
	std::cout << x << "  " << y << "  " << z << std::endl;
	glm::vec3 pos(x, y, z);*/

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
	m_engineInterfacePtr->drawCube(m_playerCube2.getComponent<TransformComponent>()->getModelMatrix());
}

