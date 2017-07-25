Table of contents
=================

* [Overview](#overview)
* [Structure](#structure)
* [How to build](#build)

<a name="overview"/>

Overview
========

This is a sample application for [OpenSceneGraph cross-platform guide](http://github.com/OGStudio/openscenegraph-cross-platform-guide).

It displays provided model with simple GLSL shaders.

<a name="structure"/>

Structure
=========

* `functions.h` file:

| Signature | Description | Implementation notes |
| --------- | ----------- | -------------------- |
| `std::string logLevelToString(osg::NotifySeverity severity)` | Convert OpenSceneGraph logging level to string representation | N/A |
| `std::string printfString(const char *fmt, ...)` | Construct a string using printf-like syntax | Maximum string length is 1024 bytes long including trailing zero |
| `void platformLog(const char *message)` | Log message using platform specific tools | <ul><li>Android:</li> Translates to `__android_log_write(ANDROID_LOG_ERROR, "OSG", message)` <li>Others</li> Translates to `std::cout << message << std::endl`</ul> |
| `void setupCamera(osg::Camera *cam, osg::GraphicsContext *gc, double fovy, int width, int height)` | Configure camera with common defaults | Only used under desktop and ios *TODO* Why not use it everywehre? |
| <ul><li>`osg::GraphicsContext *createGraphicsContext(const std::string &title, int x, int y, int width, int height)`</li> Desktop <li>`osg::GraphicsContext *createGraphicsContext(int width, int height, float scale, UIView *parentView)`</li> iOS</ul> | Create graphics context for desktop and iOS. Not used in Android and Web, because their graphics contexts are created with non-OpenSceneGraph tools |

<a name="build"/>

How to build
============

The full process of building sample application for desktop, mobile, and web
is available in [OpenSceneGraph cross-platform guide](http://github.com/OGStudio/openscenegraph-cross-platform-guide).

