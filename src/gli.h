#ifdef _WIN32
// reduce the crud we get from windows
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
// windows.h is scrubby and probably just defined macros for max and min
// however, this breaks the C++ versions provided by <algorithm>
// so undefine them.
#ifdef max
#undef max
#endif
#ifdef min
#undef min
#endif
#include "../external/GL/freeglut.h"
#else
#include <GL/gl.h>
#include <GL/freeglut.h>
#endif
