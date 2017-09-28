/**
 * A simple program experimenting the point in polygon algorithm using C++ and OpenGL.
 * example2.cpp supports multiple polygons.
 * To run: ./Example2
 *
 * 1. Draw each polygon by clicking points inside the window, 
 *   it will connect all the consecutive points as line segments.
 * 2. Press 'c' to close the polygon (i.e., finishing drawing the current polygon);
 *    You can start drawing another poygon using the same way in 1.
 * 3. Press 'd' if you are done drawing all the polygons, 
 *    a blue point will appear and it will follow your cursor, or you can control the point using keyboard i,k,j,l.
 *    If the point is in any of the polygons, that polygon will turn red, otherwise they are black。
 * 4. Press 'x' to clear the polygons and restart.
 *
 * Created by Zebin Xu on 9/27/2017
 */
#include <iostream>
#include <vector>
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
bool drawn = false;//flag indicating if all drawing are done in order to start detection
Polygon* polygon = NULL;
std::vector<Polygon*> polygons;//supporting drawing multiple polygons

void draw_polygon(Polygon& polygon) {
    glBegin(GL_LINE_STRIP);
    for (auto &point : polygon.points) {
        glVertex2i(point.x, point.y);
    }
    glEnd();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    //draw the polygon
    glBegin(GL_LINE_STRIP);
    for (auto &polygon : polygons) {
        if (drawn && polygon->inPolygon(thepoint)) {
            glColor3f(1.0, 0.0, 0.0);
        } else {
            glColor3f(0.0, 0.0, 0.0);
        }
        draw_polygon(*polygon);
    }
    glEnd();


    //render the current drawing polygon (unclosed)
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINE_STRIP);
    for (auto &point : points) {
        glVertex2i(point.x, point.y);
    }
    glEnd();

    //draw the point
    if (drawn) {
        glPointSize(4.0);
        glColor3f(0.0, 0.0, 1.0);
        glBegin(GL_POINTS);
        glVertex2i(thepoint.x, thepoint.y);
        glEnd();
    }

    glFlush();
    glutSwapBuffers();
}

void my_init()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glEnable(GL_LINE_SMOOTH);
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
        //finish all the drawings (and may close the final polygon is it is not closed yet) 
        //and start the point in polygons detection
        if (!drawn) {
            drawn = true;
            //if not closed, add a final point, same as the starting point, to close the polygon
            if (points.size() != 0) {
                points.push_back(Point2d(points[0]));
            }
            polygons.push_back(new Polygon(points));
            points.clear();
        }
        break;
    case 'c':
    case 'C':
        //Close the current polygon and start drawing a new polygon
        points.push_back(Point2d(points[0]));
        polygons.push_back(new Polygon(points));
        points.clear();
        break;
    case 'x':
    case 'X':
        //Clear all the polygon(s)
        polygons.clear();
        drawn = false;
    default:
        break;
    }
}

void passiveMotion(int x, int y) {
    if (x >= 0 && y >= 0 && x <= width && y <= height) {
        thepoint.x = x;
        thepoint.y = height - y;
    }
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
    glutCreateWindow("Point in Polygons");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutPassiveMotionFunc(passiveMotion);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(idle);

    my_init();
    glutMainLoop();
    
    return 0;
}
