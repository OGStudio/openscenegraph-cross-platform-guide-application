
#ifndef OSGSDL_VBO_SETUP_VISITOR_H
#define OSGSDL_VBO_SETUP_VISITOR_H

#include <osg/Geode>
#include <osg/Geometry>
#include <osg/NodeVisitor>

class VBOSetupVisitor : public osg::NodeVisitor
{
    public:
        VBOSetupVisitor() : osg::NodeVisitor(osg::NodeVisitor::TRAVERSE_ALL_CHILDREN) { }

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

#endif // OSGSDL_VBO_SETUP_VISITOR_H

