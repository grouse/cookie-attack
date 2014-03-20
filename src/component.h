#ifndef COMPONENT_H
#define COMPONENT_H


namespace JEngine {
	class Entity;

	class Component {
		public:
			Component(unsigned int t) : type(t) {};
			virtual ~Component() {}

			static const unsigned int 
				VELOCITY = 0,
				SHAPE = 1,
				TEXTURE = 2,
				DIRECTION = 3,
				COLLISION = 4,
				NUM_TYPES = 5;

			
			const unsigned int type;
			unsigned int owner;

			virtual bool canAttach(Entity&) = 0;
	};
}

#endif
