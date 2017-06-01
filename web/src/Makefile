OSG_INCLUDE=-I/home/kornerr/p/osg_sdl/osg/include
OSG_LIB=/home/kornerr/p/osg_sdl/osg/lib
#OSG_INCLUDE=-I/home/kornerr/b/osg_web/include -I/home/kornerr/p/OpenSceneGraph/include
#OSG_LIB=/home/kornerr/b/osg_web/lib
CC = ~/emsdk-portable/emscripten/1.37.9/em++
LIBS=-losgViewer -losgDB -losgdb_osg -losgdb_serializers_osg -losgGA -losgText -losgUtil -losg -lOpenThreads
#LIBS=-losg
all: main.cpp
	$(CC) main.cpp -O2 -s FULL_ES2=1 -s USE_SDL=2 --preload-file box.osgt -o main.html $(OSG_INCLUDE) -L$(OSG_LIB) $(LIBS)
