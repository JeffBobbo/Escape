#include "main.h"

#include <iostream>
#include <sstream>
#include <iomanip>

#include <thread>
#include <chrono>

#include <cstring>

#include "gli.h"

#include "util.h"
#include "input.h"
#include "controls.h"

#include "object/player.h"

#include "visage/allvisage.h"
#include "colour.h"
#include "imageloader.h"

// fps stuff
int64_t frame = 0;
millis_t timebase = 0;
// extern stuff
millis_t elapsed = 0, last, delta;
Level* level;
bool drawBoundingVolumes = false;
bool drawBoxes = false;
bool drawPaths = false;


int screenWidth = 640;
int screenHeight = 480;

const double TILE_SIZE = 64.0;
//VisagePolygon* phasepointer = nullptr;
//GUILabel* label = nullptr;
GUIWindow* root = nullptr;
FontManager fontManager;

void draw()
{
  last = elapsed;
  elapsed = glutGet(GLUT_ELAPSED_TIME);
  delta = elapsed - last;
  // cap delta time at 20fps
  if (delta > 20)
    delta = 20;

  glClear(GL_COLOR_BUFFER_BIT);

  // fps update
  ++frame;
  if (elapsed - timebase > 1000)
  {
    double fps = frame * (1000.0 / (elapsed - timebase));
    timebase = elapsed;
    frame = 0;
    std::stringstream ss;
    ss << TITLE;
    if (level && level->getName().size())
      ss << " - " << level->getName();
    ss << " - FPS: " << /*std::setprecision(2) <<*/ fps;
    glutSetWindowTitle(ss.str().c_str());
    timebase = elapsed;
    frame = 0;
  }

  // setup the projection matrix
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-screenWidth/TILE_SIZE/2.0, screenWidth/TILE_SIZE/2.0, -screenHeight/TILE_SIZE/2.0, screenHeight/TILE_SIZE/2.0, -1.0, 0.0);

  // and switch back to model view to arrange our scene
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();


  if (level)
  {
    if (level->completed())
    {
      Exit* e = level->getExit();
      std::string next = e->getNext();
      if (next.size())
      {
        delete level;
        level = Level::fromName(next);
        if (level == nullptr)
        {
          std::cerr << "Failed to load level " << next << std::endl;
          glutLeaveMainLoop();
          return;
        }
      }
      else
      {
        // exit
        glutLeaveMainLoop();
        return;
      }
    }
    level->idle();
    level->cleanup();
    level->draw();
  }

  // draw gui stuff on top
  glLoadIdentity();
  glColor4f(1.0, 1.0, 1.0, 1.0);
  glMatrixMode(GL_PROJECTION);

  glLoadIdentity();
  glOrtho(0.0, screenWidth, screenHeight, 0.0, -1.0, 1.0);
  glColor4f(1.0, 1.0, 1.0, 1.0);
  input::runEvents();
  if (root)
    root->draw();

  glutSwapBuffers();
}

// TODO: FIX FPS issues
void update()
{
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

  std::string load;
  for (int i = 0; i < argc; ++i)
  {
    const std::string a = argv[i];
    if (a == "-b")
      drawBoxes = true;
    else if (a == "-v")
      drawBoundingVolumes = true;
    else if (a == "-p")
      drawPaths = true;
    else if (a.substr(0, 3) == "-l=")
      load = std::string(a.substr(3));
  }

  glutInit(&argc, argv);
  glutInitWindowPosition(-1, -1);
  glutInitWindowSize(640, 480);
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
  glutCreateWindow(TITLE);

  // enable blending
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  // we're in 2d land, we don't need backface culling
  glDisable(GL_CULL_FACE);
  glDisable(GL_DEPTH_TEST); // don't need this either
  glDisable(GL_LIGHTING);
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
  //glutDisplayFunc(draw);
  // set the idle (update) callback
  glutIdleFunc(draw);

  // kb stuff
  keyboard::registerCallbacks();

  // mouse stuff
  mouse::registerCallbacks();

  // setup controls
  controls::init();

  // load visage data
  //Visage::loadVisages();

  if (load.length())
  {
    std::cout << "Loading level " << load << std::endl;
    if ((level = Level::fromName(load)) == nullptr)
    {
      std::cout << "No such level" << std::endl;
      return 0;
    }
  }
  else
  {
    GUIElement::showMenuMain();
    level = Level::prefabLobby();
  }


  // begin glut loop
  glutMainLoop();

  // we're on the way out

  // save the controls
  controls::save();

  // cleanup
  if (level)
    delete level;

  if (root)
    delete root;

  // free up all the textures
  dropAllTextures();

  return 0;
}
