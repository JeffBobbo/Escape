#include "main.h"

#include <iostream>

#include "gli.h"

#include "util.h"
#include "object/player.h"

#include "visage/allvisage.h"
#include "colour.h"

// fps stuff
int64_t frame = 0, timebase = 0;
// extern stuff
int64_t elapsed = 0, last, delta;
bool keys[255] = {0};
SceneGraph* graph;
int window;

int screenWidth = 640;
int screenHeight = 480;

const int DEFAULT_WIDTH  = 640;
const int DEFAULT_HEIGHT = 480;
const double TILE_SIZE = 64.0;

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
    sprintf(buf, "%s - FPS: %4.2f", title, fps);
    glutSetWindowTitle(buf);
    timebase = elapsed;
    frame = 0;
  }

  // draw the scene
  graph->draw();

  glutSwapBuffers();
}

void update()
{
  last = elapsed;
  elapsed = glutGet(GLUT_ELAPSED_TIME);
  delta = elapsed - last;
  graph->idle();
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
  //glClearColor(0.0, 0.0, 0.0, 1.0);
  // background is now sky!
  glClearColor(0x43 / 255.0, 0xC5 / 255.0, 0xF0 / 255.0, 255.0);

  graph = new SceneGraph();
  // create objects
  {
    Object* o = new Object();
    VisagePolygon* vp = VisagePolygon::triangle(1.6, 0.6, 0.0);
    vp->setColour(0x007F00FF);
    o->setVisage(vp);
    o->x = -0.2;
    o->y = -(1.0 - 0.3 - 0.3);
    graph->insert(SceneGraph::Level::SCENARY, o);
  }
  {
    Object* o = new Object();
    VisagePolygon* vp = VisagePolygon::triangle(2.0, 0.6, 1.0);
    vp->setColour(0x00FF1FFF);
    o->setVisage(vp);
    o->y = -(1.0 - 0.3 - 0.3);
    graph->insert(SceneGraph::Level::SCENARY, o);
  }
  {
    Object* o = new Object();
    VisageTexture* vt = new VisageTexture("img/hazard.png");
    o->setVisage(vt);
    graph->insert(SceneGraph::Level::SCENARY, o);
  }
    {
    Object* o = new Object();
    VisageTexture* vt = new VisageTexture("img/SpaceBase1.png");
    o->setVisage(vt);
    o->y = 0.5;
    graph->insert(SceneGraph::Level::SCENARY, o);
  }
  {
    Object* o = new Object();
    VisagePolygon* vp = VisagePolygon::triangle(2.0, 0.4, 0.4);
    vp->setColour(0x00AF1FFF);
    o->setVisage(vp);
    o->y = -(1.0 - 0.3 - 0.2);
    graph->insert(SceneGraph::Level::SCENARY, o);
  }
  {
    Object* o = new Object();
    VisageComplex* vc = new VisageComplex();
    VisagePolygon* vp = VisagePolygon::circle(0.1, 32);
    vp->setColour(0xFFFFFFFF);
    {
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
    }
    {
      Animatrix* oscale0 = new Animatrix();
      oscale0->start = 0;
      oscale0->end = 1000;
      oscale0->loop = 2000;
      oscale0->startScaleX = oscale0->startScaleY = 1.0;
      oscale0->endScaleX = oscale0->endScaleY = 1.3;
      vp->addAnimatrix(oscale0);
      Animatrix* oscale1 = new Animatrix();
      oscale1->start = 1000;
      oscale1->end = 2000;
      oscale1->loop = 2000;
      oscale1->startScaleX = oscale1->startScaleY = 1.3;
      oscale1->endScaleX = oscale1->endScaleY = 1.0;
      vp->addAnimatrix(oscale1);
    }
    vc->add(vp);
    ParticleSystem* ps = new ParticleSystem(1000, 150);
    ps->loadParticleImage("img/particles/soft_glow_alpha_128.png");
    ps->setColours(fromInt(0xFFAF00FF), fromInt(0xFF000000));
    ps->lifeMin = 5000;
    ps->lifeMax = 7000;
    ps->sizeStart = 0.25f;
    ps->sizeEnd = 0.0f;
    vc->add(ps);
    o->setVisage(vc);
    o->x = -0.75;
    o->y = 0.75;
    graph->insert(SceneGraph::Level::SCENARY, o);
  }
  {
    Object* o = new Wall(2.0, 0.3, 0.0, -0.85);
    graph->insert(SceneGraph::Level::FOREGROUND, o);
  }
  {
    Object* o = new Object();
    VisagePolygon* vp = VisagePolygon::square(1.0);
    vp->setColour(0x00BCFF7F);
    o->setVisage(vp);
    o->x = 1/3.0;
    o->y = -0.5;
    graph->insert(SceneGraph::Level::NPC, o);
  }
  {
    Object* o = new Object();
    VisagePolygon* vp = VisagePolygon::square(1.0);
    vp->setColour(0xBC00007F);
    o->setVisage(vp);
    o->x = -1/3.0;
    o->y = -0.5;
    graph->insert(SceneGraph::Level::EFFECTS, o);
  }
  graph->insert(SceneGraph::Level::PLAYER, new Player());

  // tell glut to return from glutMainLoop when closing the application
  // this lets us do proper clean up
  glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);

  glutReshapeFunc(reshape);

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
  delete graph;

  return 0;
}
