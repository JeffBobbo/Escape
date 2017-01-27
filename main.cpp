#include "main.h"

#include <iostream>
#include <cmath>

#include <GL/freeglut.h>
#include <GL/gl.h>

#include "util.h"

#include "visage/polygon.h"

// extern stuff
uint64_t frame = 0, elapsed = 0, timebase = 0, last, delta;
bool keys[255] = {0};
std::vector<Object* > objects;
Player* player;
int window;

void draw()
{
  ++frame;
  if (elapsed - timebase > 1000)
  {
    double fps = frame * 1000.0 / (elapsed - timebase);
    timebase = elapsed;
    frame = 0;
    char buf[50];
    sprintf(buf, "%s - FPS: %4.2f", title, fps);
    glutSetWindowTitle(buf);
    timebase = elapsed;
    frame = 0;
  }

  glClear(GL_COLOR_BUFFER_BIT);

  // background is black
  //glClearColor(0.0, 0.0, 0.0, 1.0);
  // background is now sky!
  glClearColor(0x43 / 255.0, 0xC5 / 255.0, 0xF0 / 255.0, 255.0);
  for (auto obj : objects)
    obj->draw();

  player->move();
  player->draw();
  glutSwapBuffers();
}

void update()
{
  last = elapsed;
  elapsed = glutGet(GLUT_ELAPSED_TIME);
  delta = elapsed - last;
  glutPostRedisplay();
}

void mouse(const int button, const int state, const int x, const int y)
{
  (void)button;
  (void)state;
  (void)x;
  (void)y;
}


void keyboard(const unsigned char key, const int x, const int y)
{
  (void)x;
  (void)y;
  keys[key] = true;
}
void release(const unsigned char key, const int x, const int y)
{
  (void)x;
  (void)y;
  keys[key] = false;
}

int main(int argc, char** argv)
{
  seed();

  glutInit(&argc, argv);
  glutInitWindowPosition(-1, -1);
  glutInitWindowSize(500, 500);
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
  window = glutCreateWindow(title);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glShadeModel(GL_FLAT);
  glEnable(GL_LINE_SMOOTH);
  glLineWidth(1.5);
  glHint(GL_LINE_SMOOTH_HINT, GL_DONT_CARE);

  // create objects
  {
    Object* o = new Object();
    VisagePolygon* vp = VisagePolygon::triangle(1.6, 0.6, 0.0);
    vp->setColour(0x007F00FF);
    o->setVisage(vp);
    o->x = -0.2;
    o->y = -(1.0 - 0.3 - 0.3);
    objects.push_back(o);
  }
  {
    Object* o = new Object();
    VisagePolygon* vp = VisagePolygon::triangle(2.0, 0.6, 1.0);
    vp->setColour(0x00FF1FFF);
    o->setVisage(vp);
    o->y = -(1.0 - 0.3 - 0.3);
    objects.push_back(o);
  }
  {
    Object* o = new Object();
    VisagePolygon* vp = VisagePolygon::triangle(2.0, 0.4, 0.4);
    vp->setColour(0x00AF1FFF);
    o->setVisage(vp);
    o->y = -(1.0 - 0.3 - 0.2);
    objects.push_back(o);
  }
  {
    Object* o = new Object();
    VisagePolygon* vp = VisagePolygon::circle(0.1, 32);
    vp->setColour(0xFFFFFFFF);
    Animatrix* oflash0 = new Animatrix();
    oflash0->start = 0;
    oflash0->end = 500;
    oflash0->loop = 1000;
    oflash0->startColour = 0xFF0000FF;
    oflash0->endColour = 0xFFFF00FF;
    vp->addAnimatrix(oflash0);
    Animatrix* oflash1 = new Animatrix();
    oflash1->start = 500;
    oflash1->end = 1000;
    oflash1->loop = 1000;
    oflash1->startColour = 0xFFFF00FF;
    oflash1->endColour = 0xFF0000FF;
    vp->addAnimatrix(oflash1);
    o->setVisage(vp);
    //o->rotation = 180.0;
    o->x = -0.75;
    o->y = 0.75;
    objects.push_back(o);
  }
  {
    Object* o = new Wall(2.0, 0.3, 0.0, -0.85);
    objects.push_back(o);
  }
  {
    Object* o = new Object();
    VisagePolygon* vp = VisagePolygon::square(1.0);
    vp->setColour(0x00BCFF7F);
    o->setVisage(vp);
    o->x = 1/3.0;
    o->y = -0.5;
    objects.push_back(o);
  }
  {
    Object* o = new Object();
    VisagePolygon* vp = VisagePolygon::square(1.0);
    vp->setColour(0xBC00007F);
    o->setVisage(vp);
    o->x = -1/3.0;
    o->y = -0.5;
    objects.push_back(o);
  }
  player = new Player();

  // tell glut to return from glutMainLoop when closing the application
  // this lets us do proper clean up
  glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);

  // set the display function callback
  glutDisplayFunc(draw);
  // set the idle (update) callback
  glutIdleFunc(update);

  // kb stuff
  glutIgnoreKeyRepeat(1);
  glutKeyboardFunc(keyboard);
  glutKeyboardUpFunc(release);

  // mouse stuff
  glutMouseFunc(mouse);

  // begin glut loop
  glutMainLoop();

  // cleanup
  for (Object* s : objects)
    delete s;

  return 0;
}
