
/*
This file is part of OpenSceneGraph cross-platform guide:
  https://github.com/OGStudio/openscenegraph-cross-platform-guide

Copyright (C) 2017 Opensource Game Studio

This software is provided 'as-is', without any express or implied
warranty.  In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgment in the product documentation would be
   appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/

#include <osg/Program>

// Display red colour.
static const char shaderFragment[] =
    "void main() {                             \n"
    "  gl_FragColor = vec4(0.5, 0.3, 0.3, 1.0);\n"
    "}                                         \n";
// Pass geometry vertices to fragment shader.
static const char shaderVertex[] =
    "void main() {                                              \n"
    "  gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;  \n"
    "}                                                          \n";

osg::Program *createShaderProgram(
    const std::string &vertexShader,
    const std::string &fragmentShader)
{
    // Load shaders.
    osg::Shader *vs = new osg::Shader(osg::Shader::VERTEX, vertexShader);
    osg::Shader *fs = new osg::Shader(osg::Shader::FRAGMENT, fragmentShader);
    // Compile shaders and compose shader program.
    osg::Program *prog = new osg::Program;
    prog->addShader(vs);
    prog->addShader(fs);
    return prog;
}

