CC=~/emsdk-portable/emscripten/1.37.9/em++
OSG_INCLUDE=-I/home/kornerr/b/osg_web/include -I/home/kornerr/p/OpenSceneGraph/include
OSG_LIB=/home/kornerr/b/osg_web/lib
LIBS=-losgViewer -losgDB -losgdb_osg -losgdb_serializers_osg -losgGA -losgText -losgUtil -losg -lOpenThreads

all: main.cpp
	$(CC) main.cpp -O2 -s USE_SDL=2 --preload-file box.osgt -o web.html $(OSG_INCLUDE) -L$(OSG_LIB) $(LIBS)

