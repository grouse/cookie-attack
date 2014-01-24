#include "component_manager.h"

namespace JEngine {
	ComponentManager::ComponentManager() {}
	ComponentManager::~ComponentManager() {}

	void ComponentManager::addComponent(Component* c) {
		components.push_back(c);
	}

	std::list<Component*> ComponentManager::getComponents(unsigned int c) {
		std::list<Component*> result;
		for (std::list<Component*>::iterator it = components.begin(); it != components.end(); it++) {
			if ((*it)->type == c) 
				result.push_back((*it));
		}	

		return result;
	}
}
