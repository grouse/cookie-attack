#include "engine.h"

Engine::Engine() {
	quit = true;
}

Engine::~Engine() {

}

int Engine::init() {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cerr << SDL_GetError() << "\n";
		return -1;
	}

	window = SDL_CreateWindow(
		"Pong",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		640,
		480,
		SDL_WINDOW_OPENGL		
	);

	if (window == NULL) {
		std::cerr << SDL_GetError() << "\n";
		SDL_Quit();
		return -1;
	}
	initGL(640, 480);

	quit = false;

	return 0;
}

void Engine::initGL(int w, int h) {
	glcontext = SDL_GL_CreateContext(window);
	
	
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	// Set viewport

	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	GLfloat ratio;
	ratio = (GLfloat)w / (GLfloat)h;
	
	const GLdouble pi = 3.1415926535897932384626433832795;
   	GLdouble fW, fH;
	
	fH = tan(45.0f/ 360*pi)*0.1f;
	fW = fH * ratio;

	glFrustum(-fW, fW, -fH, fH, 0.1f, 100.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Engine::run() {
	SDL_Event e;

	while (!quit) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT)
				exit();
		}
		
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glLoadIdentity();
		glTranslatef(-1.5f, 0.0f, -6.0f);

		glBegin(GL_TRIANGLES);
			glVertex3f(0.0f, 1.0f, 0.0f);
			glVertex3f(-1.0f, 1.0f, 0.0f);
			glVertex3f(1.0f, -1.0f, 0.0f);
		glEnd();

		glTranslatef(3.0f, 0.0f, 0.0f);

		glBegin(GL_QUADS);
			glVertex3f(-1.0f, 1.0f, 0.0f);
			glVertex3f(1.0f, 1.0f, 0.0f);
			glVertex3f(1.0f, -1.0f, 0.0f);
			glVertex3f(-1.0f, -1.0f, 0.0f);
		glEnd();

		SDL_GL_SwapWindow(window);
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	SDL_GL_DeleteContext(glcontext);
}

void Engine::exit() {
	quit = true;
}
