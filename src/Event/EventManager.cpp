#include "EventManager.h"
// Singleton Event Manager instance
EventManager* EventManager::s_Instance = nullptr;
EventManager::EventManager() 
{
	s_Instance = this;
}