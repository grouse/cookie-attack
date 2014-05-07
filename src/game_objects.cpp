#include "game_objects.h"


#include <iostream>
namespace JEngine {

	GameObjects::GameObjects() {}
	
	GameObjects::~GameObjects() {
		for (unsigned int i = 0; i < Component::NUM_TYPES; i++)
			for (auto it  = components[i].begin(); it != components[i].end(); it++) 
				delete (*it);

		for (auto it = entities.begin(); it != entities.end(); it++)
			delete (*it);	
	}

	void GameObjects::trashEntity(Entity* e) {
		trash.push_back(e);
		trash.unique();
	}

	void GameObjects::processTrash() { 
		for (auto it = trash.begin(); it != trash.end(); it++) {
			Entity* e = (*it);
			
			for (unsigned int i = 0; i < Component::NUM_TYPES; i++) {
				if (e->components[i] != 0) {
					components[i].remove(e->components[i]);
				
					delete e->components[i];
					e->components[i] = 0;
				}
			}

			entities.remove(e);
			delete e;
			e = 0;

			it = trash.erase(it);
		}
	}
}
