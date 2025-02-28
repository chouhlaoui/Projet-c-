#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/freeglut.h>

#include "InterfaceGraphique.h"

// Paramètres de la caméra
float zoom = 1.0f;
float offsetX = 0.0f, offsetY = 0.0f;

// Taille de la grille
const int ROWS = 10;
const int COLS = 100;
const float CELL_SIZE = 0.1f;

void Initialise(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(900, 900);
    glutCreateWindow("Simulation d'ecosysteme");
    
    glewInit();
    glutDisplayFunc(Display);
    glutKeyboardFunc(keyboard);
    glutMouseWheelFunc(mouseWheel);

    glEnable(GL_DEPTH_TEST);
    glutFullScreen();
}

void LancerSimulation(){
    glutMainLoop();
}

void Display() {
    glClearColor(1.f, 1.f, 1.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Render();
    glutSwapBuffers();
    glutPostRedisplay();
}

void Render() {
    SetupProjection();
    SetupModelView();

    RenderGrid();
    RenderText(0.8f, 0.8f, "Simulation en cours");
}

void SetupProjection() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0 * zoom + offsetX, 1.0 * zoom + offsetX,
            -1.0 * zoom + offsetY, 1.0 * zoom + offsetY, -1, 1);
}

void SetupModelView() {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void RenderGrid() {
    int viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    float aspectRatio = (float)viewport[2] / viewport[3];

    float adjustedCellWidth = CELL_SIZE * aspectRatio / 3.f;
    float adjustedCellHeight = CELL_SIZE;

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            float x = -1.f + j * adjustedCellWidth * 1.1f;
            float y = 1.f - i * adjustedCellHeight * 1.1f;

            glColor3f((i % 10) * 0.1f, (j % 10) * 0.1f, 0.8f);
            DrawQuad(x, y, adjustedCellWidth, adjustedCellHeight);
        }
    }
}

void DrawQuad(float x, float y, float width, float height) {
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y - height);
    glVertex2f(x, y - height);
    glEnd();
}

void RenderText(float x, float y, string text) {
    SetupTextRendering();

    glColor3f(0.f, 0.f, 0.f);
    glRasterPos2f(x, y);

    for (char c : text) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }

    ResetTextRendering();
}

void SetupTextRendering() {
    glDisable(GL_DEPTH_TEST);
    
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, 1, 0, 1);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
}

void ResetTextRendering() {
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    
    glEnable(GL_DEPTH_TEST);
}


void keyboard(unsigned char key, int x, int y) {
    float moveSpeed = 0.1f * zoom;

    switch (key) {
        case 'z': offsetY += moveSpeed; break; // Haut
        case 's': offsetY -= moveSpeed; break; // Bas
        case 'q': offsetX -= moveSpeed; break; // Gauche
        case 'd': offsetX += moveSpeed; break; // Droite
        case 27: exit(0); break; // Échap pour quitter
    }
}

void mouseWheel(int wheel, int direction, int x, int y) {
    if (direction > 0) zoom *= 0.9f;  // Zoom avant
    else zoom *= 1.1f;               // Zoom arrière

}

void Terminate() {
    
}