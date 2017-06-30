CLASS main.h
    PART INCLUDE
        #include <osg/Geode>
        #include <osg/Geometry>
        #include <osg/NodeVisitor>
    PART DECL
        // This class forces the use of VBO.
        class VBOSetupVisitor : public osg::NodeVisitor
        {
            public:
                VBOSetupVisitor() :
                    osg::NodeVisitor(osg::NodeVisitor::TRAVERSE_ALL_CHILDREN) { }

                virtual void apply(osg::Geode &geode)
                {
                    for (unsigned int i = 0; i < geode.getNumDrawables(); ++i)
                    {
                        osg::Geometry *geom =
                            dynamic_cast<osg::Geometry*>(geode.getDrawable(i));
                        if (geom)
                        {
                            geom->setUseVertexBufferObjects(true);
                        }
                    }
                    NodeVisitor::apply(geode);
                }
        };
    PART IMPL
        // Use VBO and EBO instead of display lists. CRITICAL for web (Emscripten)
        // to skip FULL_ES2 emulation flag.
        VBOSetupVisitor vbo;
        scene->accept(vbo);
