#ifdef _WIN32
// reduce the crud we get from windows
#define WIN32_LEAN_AND_MEAN
// we don't want min and max macros from windows.h (ugh... why)
#define NOMINMAX
#include <windows.h>
#include "../external/GL/freeglut.h"
#else
#include <GL/gl.h>
#include <GL/freeglut.h>
#endif
