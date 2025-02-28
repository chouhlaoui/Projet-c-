#include <string>
using namespace std;

void Initialise(int, char**);

void LancerSimulation();

void Display();
void Render();
void SetupProjection();
void SetupModelView();

void RenderGrid();
void DrawQuad(float, float, float, float);

void RenderText(float, float, string );
void SetupTextRendering();
void ResetTextRendering();

void keyboard(unsigned char, int, int);
void mouseWheel(int, int, int, int);

void Terminate();