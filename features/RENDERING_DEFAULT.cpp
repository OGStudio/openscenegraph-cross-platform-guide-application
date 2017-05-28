CLASS main.h
    PART INCLUDE
        #include <osgGA/TrackballManipulator>
    PART CONSTRUCT
        // Use single thread: CRITICAL for mobile and web.
        mViewer->setThreadingModel(osgViewer::ViewerBase::SingleThreaded);
        // Create manipulator: CRITICAL for mobile and web.
        mViewer->setCameraManipulator(new osgGA::TrackballManipulator);
    PART IMPL
        void frame()
        {
            mViewer->frame();
        }
