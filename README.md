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

The structure contains description and implementation notes for each entity.

* `functions.h` file
   * `std::string logLevelToString(osg::NotifySeverity severity)`
       * Convert OpenSceneGraph logging level to string representation
   * `std::string printfString(const char *fmt, ...)`
       * Construct a string using printf-like syntax
       * Maximum string length is 1024 bytes long including trailing zero
   * `void platformLog(const char *message)`
       * Log message using platform specific tools
       * Android uses `__android_log_write(ANDROID_LOG_ERROR, "OSG", message)`
       * Others use `std::cout << message << std::endl`
   * `void setupCamera(osg::Camera *cam, osg::GraphicsContext *gc, double fovy, int width, int height)`
       * Configure camera with common defaults
       * Only used under desktop and iOS
       * **TODO** Does it make sense to use it for for others?
   * Desktop: `osg::GraphicsContext *createGraphicsContext(const std::string &title, int x, int y, int width, int height)` / iOS: `osg::GraphicsContext *createGraphicsContext(int width, int height, float scale, UIView *parentView)`
       * Create graphics context using OpenSceneGraph functionality
       * Only used for desktop and iOS. Android and Web do not use the function, because their graphics contexts are created outside OpenSceneGraph

<a name="build"/>

How to build
============

The full process of building sample application for desktop, mobile, and web
is available in [OpenSceneGraph cross-platform guide](http://github.com/OGStudio/openscenegraph-cross-platform-guide).

