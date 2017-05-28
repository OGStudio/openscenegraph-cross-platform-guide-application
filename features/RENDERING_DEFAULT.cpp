CLASS main.h
    PART IMPL
        // Use single thread: CRITICAL for mobile and web.
        mViewer->setThreadingModel(osgViewer::ViewerBase::SingleThreaded);
        // Create manipulator: CRITICAL for mobile and web.
        mViewer->setCameraManipulator(new osgGA::TrackballManipulator);
