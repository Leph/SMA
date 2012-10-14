cmake_minimum_required(VERSION 2.6)
project(projetOgre3D)
include_directories("/home/onslaught/Dev/SMA/ogre_src_v1-8-1/OgreMain/include/")
include_directories("/home/onslaught/Dev/SMA/ogre_src_v1-8-1/build/include/")
include_directories("/home/onslaught/Dev/ois-v1-3/include/")
SET(SOURCES
main.cpp
Application.cpp
InputListener.cpp
)
add_executable ( SMA ${SOURCES} )
SET(ogre_lib
libOgreMain.so
libOgrePaging.so
libOgreProperty.so
libOgreRTShaderSystem.so
libOgreTerrain.so
)
target_link_libraries(
SMA
${ogre_lib}
${ois_lib}
)