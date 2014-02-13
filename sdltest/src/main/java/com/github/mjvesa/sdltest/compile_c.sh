#!/bin/sh
emcc  sdltest.c -o sdltest.js -s LEGACY_GL_EMULATION=1 -s EXPORTED_FUNCTIONS="['_init','_drawframe']"
