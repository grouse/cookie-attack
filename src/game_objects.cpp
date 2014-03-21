#include "game_objects.h"

namespace JEngine {

	GameObjects::GameObjects() {}
	
	GameObjects::~GameObjects() {
		for (unsigned int i = 0; i < Component::NUM_TYPES; i++)
			for (auto it  = components[i].begin(); it != components[i].end(); it++) 
				delete (*it);

		for (auto it = entities.begin(); it != entities.end(); it++)
			delete (*it);	
	}
}
