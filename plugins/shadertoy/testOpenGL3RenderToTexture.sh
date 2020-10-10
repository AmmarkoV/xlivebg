#!/bin/bash

rm gl3Tex

gcc -o gl3Tex  -DUSE_GLEW glx3.c glx_testRenderToTexture.c shader_loader.c matrix4x4Tools.c matrixOpenGL.c -lm -lGL -lGLU -lX11 -lGLEW

./gl3Tex

exit 0
