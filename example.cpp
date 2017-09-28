/**
 * A simple program experimenting the point in polygon algorithm using C++ and OpenGL.
 * You need to first draw a polygon by clicking points inside the window, it will connect all the consecutive points as line segments.
 * To finish drawing or clear the polygon to redraw, press 'd'.
 * Once finish drawing, a blue point will appear and you can move the blue point by holding the left button of the mouse, or using keyboard i,k,j,l.
 * Polygon is red if the point is inside of it; Otherwise it's black.
 * 
 * Created by Zebin Xu on 9/27/2017
 */
#include <iostream>
#include "polygon.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

int width = 600;
int height = 600;

Point2d thepoint(width / 2, height / 2);
std::vector<Point2d> points;// a list of points of the polygon in order.
bool drawn = false;
Polygon* polygon = NULL;// the class encapsulating the point in polygon algorithm

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    //draw the polygon
    glBegin(GL_LINE_STRIP);

    if (drawn) {
        if (polygon == NULL) {
            polygon = new Polygon(points);
        }
        if (polygon->inPolygon(thepoint)) {
            glColor3f(1.0, 0.0, 0.0);
        } else {
            glColor3f(0.0, 0.0, 0.0);
        }
    } else {
        glColor3f(0.0, 0.0, 0.0);
    }
    for (auto point : points) {
        glVertex2f(point.x, point.y);
    }
    glEnd();

    //draw the point
    if (drawn) {
        glPointSize(4.0);
        glColor3f(0.0, 0.0, 1.0);
        glBegin(GL_POINTS);
        glVertex2f(thepoint.x, thepoint.y);
        glEnd();
    }

    glFlush();
    glutSwapBuffers();
}

void my_init()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    //    glEnable(GL_LINE_SMOOTH);
}

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, (GLdouble) w, 0.0, (GLdouble) h);
}

void idle(void)
{
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'q':
    case 'Q':
        exit(0);
        break;
    case 'i':
    case 'I':
        thepoint.y += 5;
        break;
    case 'k':
    case 'K':
        thepoint.y -= 5;
        break;
    case 'j':
    case 'J':
        thepoint.x -= 5;
        break;
    case 'l':
    case 'L':
        thepoint.x += 5;
        break;
    case 'd':
    case 'D':
        if (!drawn) {
            drawn = true;
            //add a final point, same as the starting point, to close the polygon
            points.push_back(Point2d(points[0]));
        } else {
            points.clear();
            drawn = false;
        }
        break;
    default:
        break;
    }
}

void motion(int x, int y) {
    thepoint.x = x;
    thepoint.y = height - y;
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (!drawn) {
            points.push_back(Point2d(x, height - y));
        }
    }
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Point in Polygon");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMotionFunc(motion);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(idle);

    my_init();
    glutMainLoop();
    
    return 0;
}
