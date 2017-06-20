CC=~/emsdk-portable/emscripten/1.37.9/em++
#OSG_INCLUDE=-I/home/kornerr/b/osg_web/include -I/home/kornerr/p/OpenSceneGraph/include
#OSG_LIB=/home/kornerr/b/osg_web/lib
OSG_INCLUDE=-I/home/kornerr/b/osg_ems_pr/include -I/home/kornerr/p/OSG_EMS_PR/include
OSG_LIB=/home/kornerr/b/osg_ems_pr/lib
LIBS=-losgViewer -losgDB -losgdb_osg -losgdb_serializers_osg -losgGA -losgText -losgUtil -losg -lOpenThreads

all: src/main.cpp
	$(CC) src/main.cpp -O2 -s USE_SDL=2 --preload-file box.osgt -o web.html $(OSG_INCLUDE) -L$(OSG_LIB) $(LIBS) -Isrc

