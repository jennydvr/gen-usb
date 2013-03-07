//
//  draftsman.cpp
//  gen-usb
//
//  Created by Jenny Valdez on 06/03/13.
//  Copyright (c) 2013 Jenny Valdez & Luis Vieira. All rights reserved.
//

#include "draftsman.h"

using namespace std;

#define LIMIT 100.0
#define CENTER (LIMIT - LIMIT - 1)

vector<float> dataset;

void drawText(float pos[], string text)
{
    // Setear las matrices de proyeccion y vista para render 2D
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    
    // Dibujar el texto
    glColor3f(0, 0, 0);
    glRasterPos2i(pos[0], pos[1]);
    
    for (int i = 0; i != text.length(); ++i)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, text[i]);
    
    // Restaurar las matrices
	glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

void createBox(float x, float y, float width, float height)
{
    // Dibujar caja
    glColor3f(1, 0, 0);
    
    glBegin(GL_POLYGON);
    glVertex2f(x, y);
    glVertex2f(x, y + height);
    glVertex2f(x + width, y + height);
    glVertex2f(x + width, y);
    glEnd();
    
    // Dibujar bordes
    glColor3f(0, 0, 0);
    
    glBegin(GL_LINE_STRIP);
    glVertex2f(x, y - 1);
    glVertex2f(x, y + height);
    glVertex2f(x + width, y + height);
    glVertex2f(x + width, y - 1);
    glEnd();
}

void createCoordinate()
{
    glColor3f(0, 0, 0);
    
    glBegin(GL_LINES);
    // horizontal lines
    glVertex2f(-1, 0);
    glVertex2f(LIMIT, 0);
    
    // vertical lines
    glVertex2f(0, -1);
    glVertex2f(0, LIMIT);
    glEnd();
}

void createLine(float label, int index)
{
    glColor3f(0, 0, 0);
    
    glBegin(GL_LINES);
    
    glVertex2f(0 + 2 * index, -1);
    glVertex2f(0 + 2 * index, 1);
    
    glEnd();
}

void createHistogram(int len, vector<float> data, vector<string> labels)
{
    float x = 0, y = 0, width = 2;
    
    for (int i = 0; i != len; ++i)
    {
        x = i * width;
        createBox(x, y, width, data[i]);
        
        //float pos[] = {x + 1, y - 1};
        //drawText(pos, labels[i]);
    }
}

void draw()
{
    float frequencies[] = {10.0, 15.0, 13.0, 9.0, 7.0, 10.};
    string labels[] = {"1", "2", "3", "4", "5", "6"};
    int len = 6;
    
    createHistogram(len, vector<float>(frequencies, frequencies + 6), vector<string>(labels, labels + 6));
}

void setup()
{
    glClearColor(1, 1, 1, 1);
    gluOrtho2D(CENTER, LIMIT, CENTER, LIMIT);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    glPushMatrix();
    
    glScalef(0.9, 0.9, 0);
    glTranslatef(5, 5, 0);
    
    draw();
    createCoordinate();
    
    glPopMatrix();
    
    glFlush();
}

void plot(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(200, 100);
    glutInitWindowSize(400, 300);
    glutCreateWindow("Histograma");
    glutDisplayFunc(display);
    
    setup();
    glutMainLoop();
}
