#define GL_GLEXT_PROTOTYPES 1

#include <stdio.h>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <Glut/glut.h>
#else
#include <GL/gl.h>
#include <GL/glut.h>
#endif

/* Override a few functions */

static void (*real_glGenBuffers) (GLsizei, GLuint *) = 0;
static void (*real_glCompileShader) (GLuint) = 0;
static void (*real_glUseProgram) (GLuint) = 0;

void
glGenBuffers(GLsizei a, GLuint *b)
{
    printf("wrap_glGenBuffers\n");
    real_glGenBuffers(a, b);
}

void
glCompileShader(GLuint a)
{
    printf("wrap_glCompileShader\n");
    real_glCompileShader(a);
}

void
glUseProgram(GLuint a)
{
    printf("wrap_glUseProgram\n");
    real_glUseProgram(a);
}

extern void *eglGetProcAddressEMSCRIPTEN(const char *name);

static void
init_indirect()
{
    *((void **)&real_glGenBuffers) = eglGetProcAddressEMSCRIPTEN("glGenBuffers");
    *((void **)&real_glCompileShader) = eglGetProcAddressEMSCRIPTEN("glCompileShader");
    *((void **)&real_glUseProgram) = eglGetProcAddressEMSCRIPTEN("glUseProgram");

    printf("real glGenBuffers: %p glCompileShader: %p glUseProgram: %p\n", real_glGenBuffers, real_glCompileShader, real_glUseProgram);
    printf("wrap glGenBuffers: %p glCompileShader: %p glUseProgram: %p\n", glGenBuffers, glCompileShader, glUseProgram);
}

#define GLES_INDIRECT_TEST 1
#undef GL_GLEXT_PROTOTYPES

#include "hello_world_gles.c"
