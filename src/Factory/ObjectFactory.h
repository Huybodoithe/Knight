#pragma once
#include "GameObjet.h"
#include <map>
#include <string>
#include <functional>
using namespace std;

class ObjectFactory
{
public:
	GameObject* CreateObject(string type, Properties* props) ;
	static ObjectFactory* GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new ObjectFactory(); }

	void RegisterType(string className, function < GameObject* (Properties* props)> type);

private:
	ObjectFactory() {}
	static ObjectFactory* s_Instance;
	map<string, function<GameObject* (Properties* props)>> m_TypeRegistry;

};

template <class Type>
class Registrar
{
public:
	Registrar(string className)
	{
		ObjectFactory::GetInstance()->RegisterType(className, [](Properties* props)->GameObject* {return new Type(props);});
	}
};