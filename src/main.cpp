#include "main.h"

#include <iostream>

#include "gli.h"

#include "util.h"
#include "input.h"
#include "controls.h"

#include "object/player.h"

#include "visage/allvisage.h"
#include "colour.h"
#include "image.h"

// fps stuff
int64_t frame = 0, timebase = 0;
// extern stuff
int64_t elapsed = 0, last, delta;
Level* level;
int window;

int screenWidth = 640;
int screenHeight = 480;

const int DEFAULT_WIDTH  = 640;
const int DEFAULT_HEIGHT = 480;
const double TILE_SIZE = 64.0;
VisagePolygon* phasepointer = nullptr;

void draw()
{
  glClear(GL_COLOR_BUFFER_BIT);

  // setup the projection matrix
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-screenWidth/TILE_SIZE/2.0, screenWidth/TILE_SIZE/2.0, -screenHeight/TILE_SIZE/2.0, screenHeight/TILE_SIZE/2.0, -1.0, 0.0);

  // and switch back to model view to arrange our scene
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  // fps update
  ++frame;
  if (elapsed - timebase > 1000)
  {
    double fps = frame * (1000.0 / (elapsed - timebase));
    timebase = elapsed;
    frame = 0;
    char buf[50];
    sprintf(buf, "%s - %s - FPS: %4.2f", title, level->getName().c_str(), fps);
    glutSetWindowTitle(buf);
    timebase = elapsed;
    frame = 0;
  }

  // draw the scene
  level->draw();

  // draw gui stuff on top
  glLoadIdentity();
  glColor4f(1.0, 1.0, 1.0, 1.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0, screenWidth, screenHeight, 0.0, -1.0, 1.0);

  if (level->numPhases())
  {
    bindTexture("img/phase.png");
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(16.0f,           16.0f, 0.0f);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(16.0f + 128.0f,  16.0f, 0.0f);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(16.0f + 128.0f, 32.0f, 0.0f);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(16.0f,          32.0f, 0.0f);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glTranslatef(16 + level->phasePlayer() * 126.0 /(level->numPhases()-1), 26.0, 0.0);
    phasepointer->draw();
  }
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glutSwapBuffers();
}

void update()
{
  last = elapsed;
  elapsed = glutGet(GLUT_ELAPSED_TIME);
  delta = elapsed - last;
  level->idle();
  glutPostRedisplay();
}

void reshape(int width, int height)
{
  screenWidth = width;
  screenHeight = height;

  glViewport(0, 0, width, height); // Reset The Current Viewport

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  glOrtho(-screenWidth/TILE_SIZE/2.0, screenWidth/TILE_SIZE/2.0, -screenHeight/TILE_SIZE/2.0, screenHeight/TILE_SIZE/2.0, -1.0, 0.0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

int main(int argc, char** argv)
{
  seed();

  glutInit(&argc, argv);
  glutInitWindowPosition(-1, -1);
  glutInitWindowSize(640, 480);
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
  window = glutCreateWindow(title);

  // enable blending
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  // we're in 2d land, we don't need backface culling
  glDisable(GL_CULL_FACE);
  glDisable(GL_DEPTH_TEST); // don't need this either
  glShadeModel(GL_FLAT); // dunno what this is

  // background is black
  glClearColor(0.0, 0.0, 0.0, 1.0);
  // background is now sky!
  //glClearColor(0x43 / 255.0, 0xC5 / 255.0, 0xF0 / 255.0, 255.0);

  // tell glut to return from glutMainLoop when closing the application
  // this lets us do proper clean up
  glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);

  glutReshapeFunc(reshape);

  // set the display function callback
  glutDisplayFunc(draw);
  // set the idle (update) callback
  glutIdleFunc(update);

  // kb stuff
  keyboard::registerCallbacks();

  // mouse stuff
  mouse::registerCallbacks();

  // setup controls
  controls::init();

  level = Level::prefabTest();

  phasepointer = VisagePolygon::triangle(8.0, -8.0, 0.0);
  phasepointer->setColour(0x7F7F7FFF);


  // begin glut loop
  glutMainLoop();

  // we're on the way out

  // save the controls
  controls::save();

  // cleanup
  delete level;
  // free up all the textures
  dropAllTextures();

  return 0;
}
