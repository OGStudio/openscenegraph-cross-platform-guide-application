
#ifndef OSG_LOGGER_H
#define OSG_LOGGER_H

//#include <mjin2/EnvironmentClient.h>

#include <osg/Notify>
#include <iostream>

//namespace mjin2 {



class OSGLogger : public osg::NotifyHandler
{
    public:
        OSGLogger(/*EnvironmentClient *ec*/)
        {
            osg::setNotifyHandler(this);
            osg::setNotifyLevel(osg::DEBUG_FP);
            //mEC = ec;
        }
        virtual ~OSGLogger()
        {
            osg::setNotifyHandler(0);
        }

        void notify(osg::NotifySeverity severity, const char *message)
        {
            //String msg = MJIN2_STR("OSG/%s %s", severityToStr(severity).c_str(), message);
            //mEC->set("error.last", msg);
            printf("OSG/%s %s", severityToStr(severity).c_str(), message);
        }
        std::string severityToStr(osg::NotifySeverity severity)
        {
            switch (severity)
            {
                case osg::DEBUG_FP:
                    return "V";
                case osg::DEBUG_INFO:
                    return "D";
                case osg::NOTICE:
                case osg::INFO:
                    return "I";
                case osg::WARN:
                    return "W";
                case osg::FATAL:
                case osg::ALWAYS:
                    return "E";
                default:
                    return "D";
            }
        }

    private:
        //EnvironmentClient *mEC;
};

//} // namespace mjin2

#endif // OSG_LOGGER_H

