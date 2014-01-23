#ifndef COMPONENT_H
#define COMPONENT_H


namespace JEngine {
	class Entity;

	class Component {
		public:
			Component(unsigned int t) : type(t) {};

			static const unsigned int 
				POSITION = 0,
				SHAPE = 1,
				TEXTURE = 2,
				NUM_TYPES = 3;

			
			const unsigned int type;
			Entity* owner;

			virtual bool canAttach(Entity&) = 0;
	};
}

#endif
