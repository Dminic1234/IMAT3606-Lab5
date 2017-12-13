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
	//inputFile >> textFile;
	inputFile.open(textFile);
	if (inputFile.is_open())
	{
		std::getline(inputFile, s);
		ss.str(s);
		ss.ignore(17); //ignore the first 17 chars to get number of cubes
		ss >> iNumElements;
		v_playerCubes.resize(iNumElements);
		//iNumElements *= 3;
		std::cout << "Elements: " << iNumElements << std::endl;
		//Resize the vector to the correct size
		g_inVector.resize(iNumElements);
		
		ss.clear();

		for (int i = 0; i < iNumElements; i++)
		{

			//use a stringstream to get int values
			getline(inputFile, s);
			ss.clear();
			ss.str(s);
			ss >> x >> y >> z;
			pos = glm::vec3(x, y, z);
			getline(inputFile, s);
			ss.clear();
			ss.str(s);
			ss >> w >> x >> y >> z;
			orient = glm::quat(w, x, y, z);
			getline(inputFile, s);
			ss.clear();
			ss.str(s);
			ss >> x >> y >> z;
			scale = glm::vec3(x, y, z);
			v_playerCubes[i].addComponent(new TransformComponent(pos, orient, scale));
			/*if (iCounter == 0)
			{
				ss >> x >> y >> z;
				std::cout << ss.str() << std::endl;
				pos = glm::vec3(x, y, z);
			}
			if (iCounter == 1)
			{
				ss >> w >> x >> y >> z;
				orient = glm::quat(w, x, y, z);
			}
			if (iCounter == 2)
			{
				ss >> x >> y >> z;
				scale = glm::vec3(x, y, z);
				v_playerCubes[i].addComponent(new TransformComponent(pos, orient, scale));
				iCounter = -1;
			}*/
			//ss >> g_inVector[i];
			
			
			//iCounter++;

		}
		/*for (std::vector<int>::const_iterator i = g_inVector.begin(); i != g_inVector.end(); ++i)
		{
			std::cout << *i << std::endl;
		}*/
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
	//m_engineInterfacePtr->drawCube(m_playerCube.getComponent<TransformComponent>()->getModelMatrix());
	//m_engineInterfacePtr->drawCube(m_playerCube2.getComponent<TransformComponent>()->getModelMatrix());
	/*for (int i = 0; i < 5; i++)
	{
		m_engineInterfacePtr->drawCube(g_inVector.front);
	}*/
	for (int i = 0; i < v_playerCubes.size(); i++)
	{
		m_engineInterfacePtr->drawCube(v_playerCubes[i].getComponent<TransformComponent>()->getModelMatrix());
	}
	
}

