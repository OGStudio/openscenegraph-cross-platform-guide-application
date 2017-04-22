
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

#ifndef OPENSCENEGRAPH_CROSS_PLATFORM_GUIDE_LOGGER_H
#define OPENSCENEGRAPH_CROSS_PLATFORM_GUIDE_LOGGER_H

#include "Logging.h"
#include "LogLevelConversion.h"

// Contains NotifyHandler, which we use to get OpenSceneGraph notifications.
#include <osg/Notify>

#ifdef ANDROID
    // Provides __android_log_write().
    #include <android/log.h>
#else // ANDROID
    // Provides printf().
    #include <iostream>
#endif // ANDROID

// This class prints OpenSceneGraph notifications to stdout.
class Logger : public osg::NotifyHandler
{
    public:
        Logger() { }
        virtual ~Logger() { }

        // Override NotifyHandler::notify() to receive OpenSceneGraph notifications.
        void notify(osg::NotifySeverity severity, const char *message)
        {
            std::string finalMessage =
                printfString(
                    "OSG/%s %s\n",
                    logLevelToString(severity).c_str(),
                    message);
            // Simply print each notification to stdout.
#ifdef ANDROID
            __android_log_write(ANDROID_LOG_ERROR, "OSG", finalMessage.c_str());
#else // ANDROID
            printf(finalMessage.c_str());
#endif // ANDROID
        }
};

#endif // OPENSCENEGRAPH_CROSS_PLATFORM_GUIDE_LOGGER_H

