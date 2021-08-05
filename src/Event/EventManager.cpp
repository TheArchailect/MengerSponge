#include "EventManager.h"
// Singleton Event Manager instance
EventManager* EventManager::s_Instance = nullptr;
EventManager::EventManager() 
{
	std::cout << "EventManager constructor" << std::endl;
	s_Instance = this;
}