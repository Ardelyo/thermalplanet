#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glad/glad.h>

#ifdef _WIN32
#include <windows.h>
#endif

PFNGLCLEARCOLORPROC glClearColor;
PFNGLCLEARPROC glClear;
PFNGLVIEWPORTPROC glViewport;
PFNGLENABLEPROC glEnable;
PFNGLGENBUFFERSPROC glGenBuffers;
PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;
PFNGLBINDBUFFERPROC glBindBuffer;
PFNGLBINDVERTEXARRAYPROC glBindVertexArray;
PFNGLBUFFERDATAPROC glBufferData;
PFNGLMAPBUFFERPROC glMapBuffer;
PFNGLUNMAPBUFFERPROC glUnmapBuffer;
PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray;
PFNGLDELETEBUFFERSPROC glDeleteBuffers;
PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays;
PFNGLDELETEPROGRAMPROC glDeleteProgram;
PFNGLCREATESHADERPROC glCreateShader;
PFNGLSHADERSOURCEPROC glShaderSource;
PFNGLCOMPILESHADERPROC glCompileShader;
PFNGLGETSHADERIVPROC glGetShaderiv;
PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
PFNGLCREATEPROGRAMPROC glCreateProgram;
PFNGLATTACHSHADERPROC glAttachShader;
PFNGLLINKPROGRAMPROC glLinkProgram;
PFNGLGETPROGRAMIVPROC glGetProgramiv;
PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;
PFNGLDELETESHADERPROC glDeleteShader;
PFNGLUSEPROGRAMPROC glUseProgram;
PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv;

static void* get_proc(const char *name) {
    void *p = (void *)wglGetProcAddress(name);
    if(p == 0 ||
        (p == (void*)0x1) || (p == (void*)0x2) || (p == (void*)0x3) ||
        (p == (void*)-1) )
    {
        HMODULE module = LoadLibraryA("opengl32.dll");
        p = (void *)GetProcAddress(module, name);
    }
    return p;
}

int gladLoadGLLoader(GLADloadproc load) {
    GLADloadproc loader = load ? load : get_proc;

    // Load OpenGL functions
    glClearColor = (PFNGLCLEARCOLORPROC)loader("glClearColor");
    glClear = (PFNGLCLEARPROC)loader("glClear");
    glViewport = (PFNGLVIEWPORTPROC)loader("glViewport");
    glEnable = (PFNGLENABLEPROC)loader("glEnable");
    glGenBuffers = (PFNGLGENBUFFERSPROC)loader("glGenBuffers");
    glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)loader("glGenVertexArrays");
    glBindBuffer = (PFNGLBINDBUFFERPROC)loader("glBindBuffer");
    glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)loader("glBindVertexArray");
    glBufferData = (PFNGLBUFFERDATAPROC)loader("glBufferData");
    glMapBuffer = (PFNGLMAPBUFFERPROC)loader("glMapBuffer");
    glUnmapBuffer = (PFNGLUNMAPBUFFERPROC)loader("glUnmapBuffer");
    glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)loader("glVertexAttribPointer");
    glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)loader("glEnableVertexAttribArray");
    glDisableVertexAttribArray = (PFNGLDISABLEVERTEXATTRIBARRAYPROC)loader("glDisableVertexAttribArray");
    glDeleteBuffers = (PFNGLDELETEBUFFERSPROC)loader("glDeleteBuffers");
    glDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC)loader("glDeleteVertexArrays");
    glDeleteProgram = (PFNGLDELETEPROGRAMPROC)loader("glDeleteProgram");
    glCreateShader = (PFNGLCREATESHADERPROC)loader("glCreateShader");
    glShaderSource = (PFNGLSHADERSOURCEPROC)loader("glShaderSource");
    glCompileShader = (PFNGLCOMPILESHADERPROC)loader("glCompileShader");
    glGetShaderiv = (PFNGLGETSHADERIVPROC)loader("glGetShaderiv");
    glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)loader("glGetShaderInfoLog");
    glCreateProgram = (PFNGLCREATEPROGRAMPROC)loader("glCreateProgram");
    glAttachShader = (PFNGLATTACHSHADERPROC)loader("glAttachShader");
    glLinkProgram = (PFNGLLINKPROGRAMPROC)loader("glLinkProgram");
    glGetProgramiv = (PFNGLGETPROGRAMIVPROC)loader("glGetProgramiv");
    glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)loader("glGetProgramInfoLog");
    glDeleteShader = (PFNGLDELETESHADERPROC)loader("glDeleteShader");
    glUseProgram = (PFNGLUSEPROGRAMPROC)loader("glUseProgram");
    glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC)loader("glGetUniformLocation");
    glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC)loader("glUniformMatrix4fv");

    return 1;
}

int gladLoadGL(void) {
    return gladLoadGLLoader(get_proc);
}
