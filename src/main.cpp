#include "engine.h"

int main(int argc, char* argv[]) {
	JEngine::Engine engine;

	engine.init();
	engine.run();
	
	return 0;
}
