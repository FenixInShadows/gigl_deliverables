#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <iostream>
#include <string>
#include <chrono>
#include "macro.h"
#include "TreeSegment.h"

using namespace std;

#include "l_tree.generated.h"

LTree* active_tree = nullptr;

double camera_x, camera_y;
double camera_x_min, camera_x_max, camera_y_min, camera_y_max;
double camera_speed = 500.0; // speed of camera movement

Range2D image_range;
Range2D window_range;

void InitCamera(const Range2D& range)
{
	camera_x = 0.5 * (range.left + range.right);
	if (range.span_x <= WIN_WIDTH)
	{
		camera_x_min = camera_x;
		camera_x_max = camera_x;
	}
	else
	{
		camera_x_min = range.left + 0.5 * WIN_WIDTH;
		camera_x_max = range.right - 0.5 * WIN_WIDTH;
	}
	camera_y = 0.5 * (range.bottom + range.top);
	if (range.span_y <= WIN_HEIGHT)
	{
		camera_y_min = camera_y;
		camera_y_max = camera_y;
	}
	else
	{
		camera_y_min = range.bottom + 0.5 * WIN_HEIGHT;
		camera_y_max = range.top - 0.5 * WIN_HEIGHT;
	}
}

void MoveCameraLeft(double dx)
{
	camera_x -= dx;
	if (camera_x < camera_x_min)
		camera_x = camera_x_min;
}

void MoveCameraBottom(double dy)
{
	camera_y -= dy;
	if (camera_y < camera_y_min)
		camera_y = camera_y_min;
}

void MoveCameraRight(double dx)
{
	camera_x += dx;
	if (camera_x > camera_x_max)
		camera_x = camera_x_max;
}

void MoveCameraTop(double dy)
{
	camera_y += dy;
	if (camera_y > camera_y_max)
		camera_y = camera_y_max;
}

void UpdateWindowRange()
{
	window_range = Range2D(camera_x - 0.5 * WIN_WIDTH, camera_y - 0.5 * WIN_HEIGHT, camera_x + 0.5 * WIN_WIDTH, camera_y + 0.5 * WIN_HEIGHT, WIN_WIDTH, WIN_HEIGHT);
}

void DrawImage()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(window_range.left, window_range.right, window_range.bottom, window_range.top, -1.0, 1.0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if (active_tree)
		active_tree->Draw();
}

int main(int argc, char *argv[])
{
	int seed;
	cout << "input seed: ";
	cin >> seed;
	

	int n;
	cout << "Input the expansion depth n" << endl;
	cin >> n;

	int unit_len;
	cout << "Input the unit segment length" << endl;
	cin >> unit_len;


	// SDL initialization
	SDL_Init(SDL_INIT_VIDEO);  // Initialize Graphics (for OpenGL)
	// Create a window (offsetx, offsety, width, height, flags)
	SDL_Window* window = SDL_CreateWindow("L_System_Tree", 100, 100, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_OPENGL);
	// Create a context to draw in
	SDL_GLContext context = SDL_GL_CreateContext(window);

	// Some initial set ups for OpenGL
	glShadeModel(GL_SMOOTH);
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glClearDepth(1.0);
	glViewport(0, 0, WIN_WIDTH, WIN_HEIGHT);
	glColorMaterial(GL_FRONT, GL_AMBIENT);
	glEnable(GL_COLOR_MATERIAL);
	float material_ambient[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);

	// timing
	auto old_time = chrono::high_resolution_clock::now();

	// generate the intial dungeon
	RandInit(seed);
	cout << "Tree #" << seed << endl;
	image_range = MkNoConstraintRange2D();
	//active_tree = GenerateDetermLTree(n, unit_len);
	//active_tree = GenerateNDLTree(n, unit_len);
	active_tree = GenerateAdvNDLTree(n, unit_len);
	InitCamera(image_range);
	UpdateWindowRange();

	// Event loop
	SDL_Event windowEvent;
	
	while(true)
	{	
		auto new_time = chrono::high_resolution_clock::now();
		std::chrono::duration<double> elapsed_time = new_time - old_time;		
		double dt = elapsed_time.count();
		old_time = new_time;

		if (SDL_PollEvent(&windowEvent))
		{
			// Quit from window
			if (windowEvent.type == SDL_QUIT)
				break;

			// Key Released
			if (windowEvent.type == SDL_KEYUP)
			{
				if (windowEvent.key.keysym.sym == SDLK_ESCAPE)	// quit
					break;
				if (windowEvent.key.keysym.sym == SDLK_RETURN)	// generate a new dungeon
				{
					if (active_tree)
						delete active_tree;
					seed = GetRandInt();
					RandInit(seed);
					cout << "Tree #" << seed << endl;
					image_range = MkNoConstraintRange2D();
					//active_tree = GenerateDetermLTree(n, unit_len);
					//active_tree = GenerateNDLTree(n, unit_len);
					active_tree = GenerateAdvNDLTree(n, unit_len);
					InitCamera(image_range);
					UpdateWindowRange();
				}				
			}			
			else
			if (windowEvent.type == SDL_KEYDOWN)	// move camera
			{
				switch (windowEvent.key.keysym.sym)
				{								
				case SDLK_j: // camera goes left
					MoveCameraLeft(camera_speed*dt);
					UpdateWindowRange();
					break;
				case SDLK_k: // camera goes bottom
					MoveCameraBottom(camera_speed*dt);
					UpdateWindowRange();
					break;
				case SDLK_l: // camera goes right
					MoveCameraRight(camera_speed*dt);
					UpdateWindowRange();
					break;
				case SDLK_i: // camera goes top
					MoveCameraTop(camera_speed*dt);
					UpdateWindowRange();
					break;
				}
			}
		}

		// Draw pixel in memory
		DrawImage();		
		
		// Double buffering
		SDL_GL_SwapWindow(window);
	}

	// SDL Clean-up
	SDL_GL_DeleteContext(context);	
	SDL_Quit();

	if (active_tree)
		delete active_tree;

	return 0;
}