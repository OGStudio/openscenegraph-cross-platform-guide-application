
#ifndef OSGSDL_WEB_APPLICATION_H
#define OSGSDL_WEB_APPLICATION_H

#include "OSGLogger.h"

#include <osgDB/ReadFile>
#include <osgGA/TrackballManipulator>
#include <osgViewer/Viewer>
#include <SDL2/SDL.h>
#include <iostream>

/*
// osgt loader plugin.
USE_OSGPLUGIN(osg2)
USE_SERIALIZER_WRAPPER_LIBRARY(osg)
*/

class WebApplication
{
    public:
        WebApplication()
        {
            logger = new OSGLogger;
            viewer = new osgViewer::Viewer;
            viewer->setThreadingModel(osgViewer::ViewerBase::SingleThreaded);
            viewer->setCameraManipulator(new osgGA::TrackballManipulator);
        }
        ~WebApplication() { }

        void frame()
        {
            static int i = 0;
            if (++i > 10)
                return;
            printf("WebApplication.01.frame\n");
            viewer->frame();
            printf("WebApplication.02.frame\n");
        }
        bool handleEvent(SDL_Event &e)
        {
            osgGA::EventQueue &queue =  *(gw->getEventQueue());
            switch (e.type)
            {
                case SDL_MOUSEMOTION:
                    queue.mouseMotion(e.motion.x, e.motion.y);
                    return true;
                case SDL_MOUSEBUTTONDOWN:
                    queue.mouseButtonPress(e.button.x, e.button.y, e.button.button);
                    printf("OSGSDL. Application. Mouse button down\n");
                    return true;
                case SDL_MOUSEBUTTONUP:
                    queue.mouseButtonRelease(e.button.x, e.button.y, e.button.button);
                    printf("OSGSDL. Application. Mouse button up\n");
                    return true;
                case SDL_KEYUP:
                    queue.keyRelease(
                        (osgGA::GUIEventAdapter::KeySymbol)e.key.keysym.scancode);
                    return true;
                case SDL_KEYDOWN:
                    queue.keyPress(
                        (osgGA::GUIEventAdapter::KeySymbol)e.key.keysym.scancode);
                    return true;
                default:
                    break;
            }
            return false;
        }
        void loadScene(const std::string &fileName)
        {
            // Only run once.
            static bool firstRun = true;
            if (!firstRun) {
                return;
            }
            firstRun = false;
            
            static const char gFragmentShader[] =
                "void main() {                             \n"
                "  gl_FragColor = vec4(0.5, 0.3, 0.3, 1.0);\n"
                "}                                         \n";
            static const char gVertexShader[] =
                "void main() {                                                          \n"
                "    gl_Position   = gl_ModelViewProjectionMatrix * gl_Vertex;          \n"
                "}                                                                      \n";

            printf("WebApplication.01.loadScene\n");
            // Build shaders.
            osg::Shader *vshader = new osg::Shader(osg::Shader::VERTEX, gVertexShader);
            osg::Shader *fshader = new osg::Shader(osg::Shader::FRAGMENT, gFragmentShader);
            printf("WebApplication.02.loadScene\n");
            osg::Program *prog = new osg::Program;
            prog->addShader(vshader);
            prog->addShader(fshader);
            printf("WebApplication.03.loadScene\n");
            // Load node.
            osg::Node *node = osgDB::readNodeFile(fileName);
            printf("WebApplication.04.loadScene\n");
            // Assign shaders to the node.
            node->getOrCreateStateSet()->setAttribute(prog);
            printf("WebApplication.05.loadScene\n");
            // Display the node.
            viewer->setSceneData(node);
            printf("WebApplication.06.loadScene\n");
        }
        void setEmbeddedWindowSize(int width, int height)
        {
            gw = viewer->setUpViewerAsEmbeddedInWindow(0, 0, width, height);
            viewer->realize();
        }

    private:
        osg::ref_ptr<OSGLogger> logger;
        osg::ref_ptr<osgViewer::Viewer> viewer;
        osg::ref_ptr<osgViewer::GraphicsWindowEmbedded> gw;
};

#endif // OSGSDL_APPLICATION_H

