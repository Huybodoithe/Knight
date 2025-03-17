#include "ObjectFactory.h"
#include "Warrior.h"
#include "Enemy.h"

ObjectFactory* ObjectFactory::s_Instance = nullptr;

GameObject* ObjectFactory::CreateObject(string type, Properties* props)
{
	GameObject* object = nullptr;

	auto it = m_TypeRegistry.find(type);
	if (it != m_TypeRegistry.end()) object = it->second(props);

	return object;
}

void ObjectFactory::RegisterType(string className, function<GameObject* (Properties* props)> type)
{
	m_TypeRegistry[className] = type;
}
