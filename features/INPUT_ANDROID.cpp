CLASS main.h
    PART IMPL
        void moveMouse(float x, float y)
        {
            mViewer->getEventQueue()->mouseMotion(x, y);
        }
        void pressMouse(bool down, float x, float y)
        {
            if (down)
                mViewer->getEventQueue()->mouseButtonPress(x, y, 2 /* MMB */);
            else
                mViewer->getEventQueue()->mouseButtonRelease(x, y, 2 /* MMB */);
        }
