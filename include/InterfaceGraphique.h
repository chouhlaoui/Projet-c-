#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/freeglut.h>

#include <string>
using namespace std;

#include "Monde.h"
extern Monde* monde;

void Initialise(int, char**, int , int, int, int);
void LoadAllTextures();
GLuint LoadTexture(const char*);

void LancerSimulation();

void Display();
void Render();
void SetupProjection();
void SetupModelView();

void RenderGrid();
void DrawQuad(float, float, float, float);

void RenderInfoBox();
void SetupUIRendering();
void ResetUIRendering();

void RenderText(float, float, string );
void SetupTextRendering();
void ResetTextRendering();

void keyboard(unsigned char, int, int);
void mouseWheel(int, int, int, int);

void Terminate();