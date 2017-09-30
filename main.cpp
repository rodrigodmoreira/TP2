#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include "physics.h"
#include "draw.h"
#include "player.h"

#define FPS 60

using namespace std;

int keyState[300];
Camera cam;

void init()
{
  glClearColor (1.0, 1.0, 1.0, 1.0);
  //glShadeModel (GL_FLAT);

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
}

void draw_callback()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glColor4f(0,0,1,1);
  drawPlane(0,-20,0,100);

  glColor4f(1,0,0,1);
  drawWireCube(0,-20,-50,10);

  glColor4f(1,0.5,0.5,1);
  drawWireCube(50,-20,0,10);

  glColor4f(1,1,0,1);
  drawWireCube(-50,-20,0,10);

  glColor4f(1,0,1,1);
  drawWireCube(0,-20,50,10);

  glutSwapBuffers();
}

void update_callback(int)
{
  calculatePhysics(keyState,cam);

  glutPostRedisplay();

  glutTimerFunc(((double)1000)/FPS,update_callback,0); 
}

void reshape_callback(int w, int h)
{
  glViewport (0, 0, (GLsizei) w, (GLsizei) h);
  
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();
  
  gluPerspective(65.0, (GLfloat) w/(GLfloat) h, 1, 1000.0);
  //glOrtho(0, w, 0, h, -1.0, 1.0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void keyPress_callback(unsigned char key, int x, int y)
{
  if(key==27) exit(0);
  keyState[(int)key]=1;

  if(keyState['w'])
  {
    cam.dir={0,0,-1,0}; // olha pra frente
    cam.spd=1; // anda pra frente
    /*gluLookAt(cam.spd*cam.dir.x, cam.spd*cam.dir.y, cam.spd*cam.dir.z,
        0, 0, -2,
        0, 1, 0);*/
  }
  if(keyState['s'])
  {
    cam.dir={0,0,-1,0}; // olha pra frente
    cam.spd=1; // anda pra trás
    /*gluLookAt(0, 0, 1,
        0, 0, -2,
        0, 1, 0);*/
  }
  if(keyState['a'])
  {
    cam.dir={-1,0,0,0};
    cam.spd=0;
    /*gluLookAt(0, 0, 0,
        -2, 0, 0,
        0, 1, 0);*/
  }
  if(keyState['d'])
  {
    cam.dir={1,0,0,0};
    cam.spd=0;
    /*gluLookAt(0, 0, 0,
        2, 0, 0,
        0, 1, 0);*/
  }
  if(keyState['+'])
  {
    cam.dir={0,0,-1,0};
    gluLookAt(0, 0, -1,
        0, 0, -2,
        0, 2, 0);
  }

  gluLookAt(0,0,0,
            cam.dir.x,cam.dir.y,cam.dir.z,
            0,1,0);

  //if(keyState['w'] || keyState['s'] || keyState['a'] || keyState['d'])
  
}

void keyRelease_callback(unsigned char key, int x, int y)
{
  keyState[(int)key]=0;
}

int main(int argc, char** argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize (1366, 768);
  glutInitWindowPosition (0, 0);
  glutCreateWindow ("TP2");
  glutFullScreen();
  init();

  glutDisplayFunc(draw_callback);
  glutReshapeFunc(reshape_callback);
  glutKeyboardFunc(keyPress_callback);
  glutKeyboardUpFunc(keyRelease_callback);
  glutTimerFunc(0,update_callback,0);

  glutMainLoop();
  return 0;
}
