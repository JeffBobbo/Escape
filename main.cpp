#include "main.h"

#include <iostream>

#include "gli.h"

#include "util.h"
#include "object/player.h"

#include "visage/allvisage.h"
#include "colour.h"

#define STB_IMAGE_IMPLEMENTATION
#include "external/stb_image.h"

// fps stuff
int64_t frame = 0, timebase = 0;
// extern stuff
int64_t elapsed = 0, last, delta;
bool keys[255] = {0};
SceneGraph* graph;
int window;

GLuint tex = 0;
uint8_t* idata = nullptr;
int width, height, bpp;
void draw()
{
  glClear(GL_COLOR_BUFFER_BIT);

  // setup the projection matrix
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

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

  // dirty texture hack
  glEnable(GL_TEXTURE_2D);
  glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f, 0.0f);  glVertex3f(-0.5f, 0.5f, 0.0f);
  glTexCoord2f(0.0f, 1.0f);  glVertex3f(-0.5f, -0.5f, 0.0f);
  glTexCoord2f(1.0f, 1.0f);  glVertex3f(0.5f, -0.5f, 0.0f);
  glTexCoord2f(1.0f, 0.0f);  glVertex3f(0.5f, 0.5f, 0.0f);
  glEnd();
  glDisable(GL_TEXTURE_2D);
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

void loadImage(const char* const name)
{
  /*

  std::vector<uint8_t> image;
  uint32_t w, h;
  uint32_t e = lodepng::decode(image, w, h, name);
  if (e)
  {
    std::cout << "Failed to load image: " << lodepng_error_text(e) << std::endl;
    return 0;
  }
  size_t u2 = 1;
  while (u2 < w)
    u2 *= 2;
  size_t v2 = 1;
  while (v2 < h)
    v2 *= 2;

  //double u3 = static_cast<double>(w) / u2;
  //double v3 = static_cast<double>(h) / v2;
  std::vector<uint8_t> image2(u2*v2*4);
  for (size_t y = 0; y < h; ++y)
  {
    for (size_t x = 0; x < w; ++x)
    {
      for (size_t c = 0; c < 4; ++c)
        image2[4 * u2 * y + 4 * x + c] = image[4 * w * y + 4 * x + c];
    }
  }
 */
  idata = stbi_load(name, &width, &height, &bpp, 4);

  glGenTextures(1, &tex);
  glBindTexture(GL_TEXTURE_2D, tex);
  glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, idata);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 16.0f);
}

int main(int argc, char** argv)
{
  std::cout << "Woaahhhh" << std::endl;
  seed();

  glutInit(&argc, argv);
  glutInitWindowPosition(-1, -1);
  glutInitWindowSize(500, 500);
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

  loadImage("img/hazard.png");

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
    ps->setColours(fromInt(0xFFAF00FF), fromInt(0xFF000000));
    ps->lifeMin = 5000;
    ps->lifeMax = 7000;
    ps->sizeStart = 5.0f;
    ps->sizeEnd = 0.0f;
    vc->add(ps);
    o->setVisage(vc);
    o->x = -0.75;
    o->y = 0.75;
    graph->insert(SceneGraph::Level::BACKGROUND, o);
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
  stbi_image_free(idata);

  return 0;
}
