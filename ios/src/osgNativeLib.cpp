
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

#include "osgNativeLib.h"

#include "AppLogging.h"
#include "AppRendering/AppRenderingPlatformIOS.h"
#include "Platform/PlatformIOS.h"

// TODO: Move to AppScene.
#include <osgDB/ReadFile>

namespace osgNativeLib {

// TODO: Extract?
class App {
    public:
        App()
        {
            logging = new AppLogging;
            rendering = new AppRenderingPlatformIOS;
        }
        ~App()
        {
            delete rendering;
            delete logging;
        }

    public:
        AppLogging *logging;
        AppRenderingPlatformIOS *rendering;
};

// Init OSG plugins.
// TODO: Move to AppScene, since this macro deals with resources?
USE_OSGPLUGIN(osg2)
USE_SERIALIZER_WRAPPER_LIBRARY(osg)

// Create application instance.
App app;

UIView *init(int width, int height, float scale, UIView *parentView)
{
    return app.rendering->setupWindow(width, height, scale, parentView);
}

void frame()
{
    app.rendering->frame();
}

void loadModel(const std::string &path)
{
    // TODO.
    // app.scene->load
}

} // namespace osgNativeLib.

