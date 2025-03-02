#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/freeglut.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <iostream>
#include <vector>
#include <string>
#include<windows.h>
using namespace std;

#include "InterfaceGraphique.h"
#include "Mouton.h"
#include "Loup.h"
#include "Herbe.h"

// Paramètres
float zoom = 1.0f;
float offsetX = 0.0f, offsetY = 0.0f;
const float CELL_SIZE = 0.1f;
int FPS = 10;
bool pause = false;

Monde* monde = nullptr;

// Textures
const char map[] = {'M', 'L', 'H', 'S'};
vector<GLuint> textures;

void Initialise(int argc, char** argv, int nb_ligne, int nb_colonne, int nb_mouton, int nb_loup) {
    monde = new Monde(nb_ligne, nb_colonne, nb_mouton, nb_loup);
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(900, 900);
    glutCreateWindow("Simulation d'ecosysteme");
    
    glewInit();
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    LoadAllTextures();
    
    glutDisplayFunc(Display);
    glutKeyboardFunc(keyboard);
    glutMouseWheelFunc(mouseWheel);

    glDisable(GL_DEPTH_TEST);
    glutFullScreen();
}

void LoadAllTextures() {
    vector<string> textureFiles = {
        "Textures/Mouton.png",
        "Textures/Loup.png",
        "Textures/Herbe.png",
        "Textures/Sels.png"
    };

    for (const auto& file : textureFiles) {
        GLuint textureID = LoadTexture(file.c_str());
        if (textureID) {
            textures.push_back(textureID);
            cout << "Texture chargee : " << file << endl;
        } else {
            cerr << "Erreur : Texture non chargee " << file << endl;
        }
    }
}


GLuint LoadTexture(const char* filename) {
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    int width, height, nrChannels;
    unsigned char* data = stbi_load(filename, &width, &height, &nrChannels, 4);
    GLenum format = (nrChannels == 4) ? GL_RGBA : GL_RGB;

    if (!data) {
        cerr << "Erreur de chargement de l'image : " << filename << endl;
        return 0;
    } else {
        cout << "Texture chargee : " << filename << " (" << width << "x" << height << ")" << " -> ID " << textureID<< endl;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    stbi_image_free(data);
    glBindTexture(GL_TEXTURE_2D, 0);

    return textureID;
}

void LancerSimulation(){
    glutMainLoop();
}

void Display() {
    glClearColor(0.45f, 0.7f, 0.45f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Render();
    glutSwapBuffers();
    glutPostRedisplay();
}

void Render() {
    SetupProjection();
    SetupModelView();

    if (!pause) monde->tourSuivant();
    RenderGrid();
    RenderInfoBox();
    Sleep(1000.0/FPS);
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

    glEnable(GL_TEXTURE_2D);
    
    Sprite**** tab = monde->tableau();
    Sprite* sprite = nullptr;
    int textureIndex, i;
    
    for (int x = 0; x < monde->nombreDeLignes(); x++) {
        for (int y = 0; y < monde->nombreDeColonnes(); y++) {
            sprite = nullptr;

            for (int z = 0; z < 2; z++) {
                if (tab[x][y][z] != nullptr) {
                    sprite = tab[x][y][z];
                    
                    i = 0;
                    while(map[i] != sprite->getSymbole()) i++;
                    textureIndex = i;
                    
                    glBindTexture(GL_TEXTURE_2D, textures[textureIndex]); 
                    glEnable(GL_TEXTURE_2D);

                    float coord_x = -1.f + y * adjustedCellWidth;
                    float coord_y = 1.f - x * adjustedCellHeight;
            
                    DrawQuad(coord_x, coord_y, adjustedCellWidth, adjustedCellHeight);
                }
            }
        }
    }

    glDisable(GL_TEXTURE_2D);
}

void DrawQuad(float x, float y, float width, float height) {
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex2f(x, y);
        glTexCoord2f(1.0f, 0.0f); glVertex2f(x + width, y);
        glTexCoord2f(1.0f, 1.0f); glVertex2f(x + width, y - height);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(x, y - height);
    glEnd();
}


void RenderInfoBox() {
    SetupUIRendering();

    glColor3f(0.45f, 0.8f, 0.45f);
    glBegin(GL_QUADS);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(1.0f, 0.0f);
        glVertex2f(1.0f, 0.1f);
        glVertex2f(0.0f, 0.1f);
    glEnd();

    SetupTextRendering();
    
    float startX = 0.05f;
    float startY = 0.07f;
    float columnSpacing = 0.25f;

    RenderText(startX, startY, "Tour : " + to_string(monde->nombreTour()));
    RenderText(startX + columnSpacing, startY, "Moutons : " + to_string(Mouton::getNbMouton()));
    RenderText(startX + 2 * columnSpacing, startY, "Loups : " + to_string(Loup::getNbLoup()));
    RenderText(startX + 3 * columnSpacing, startY, "Herbe : " + to_string(Herbe::getNbHerbe()));

    RenderText(startX, startY - 0.05f, "Zoom : " + to_string(zoom));
    RenderText(startX + columnSpacing, startY - 0.05f, "Offset X : " + to_string(offsetX));
    RenderText(startX + 2 * columnSpacing, startY - 0.05f, "Offset Y : " + to_string(offsetY));
    RenderText(startX + 3 * columnSpacing, startY - 0.05f, "Tour/Seconde : " + to_string(FPS));

    ResetTextRendering();
}

void SetupUIRendering() {

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, 1, 0, 1);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
}

void ResetUIRendering() {
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}


void RenderText(float x, float y, string text) {
    SetupTextRendering();
    glRasterPos2f(x, y);
    for (char c : text) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
    ResetTextRendering();
}

void SetupTextRendering() {
    
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, 1, 0, 1);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glColor3f(0.f, 0.f, 0.f);
}

void ResetTextRendering() {
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    
    glColor3f(1.0f, 1.0f, 1.0f);
}


void keyboard(unsigned char key, int x, int y) {
    float moveSpeed = 0.1f * zoom;

    switch (key) {
        case 'z': offsetY += moveSpeed; break; // Haut
        case 's': offsetY -= moveSpeed; break; // Bas
        case 'q': offsetX -= moveSpeed; break; // Gauche
        case 'd': offsetX += moveSpeed; break; // Droite
        case 'p': pause = !pause; break;
        case '+': if(FPS<50)FPS++; break;
        case '-': if(FPS>1) FPS--; break;
        case 27: exit(0); break; // Échap pour quitter
    }
}

void mouseWheel(int wheel, int direction, int x, int y) {
    if (direction > 0)
    {
        // Zoom avant
        if (zoom > 0.1f) zoom -= 0.1f;
    }
    else
    {
        // Zoom arrière
        zoom += 0.1f;
    }
}

void Terminate() {
    delete monde;
}