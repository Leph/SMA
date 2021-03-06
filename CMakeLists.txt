cmake_minimum_required(VERSION 2.6)
 
project(SMA)
 
if(EXISTS "/usr/local/lib/OGRE/cmake")
    set(CMAKE_MODULE_PATH "/usr/local/lib/OGRE/cmake/;${CMAKE_MODULE_PATH}")
    set(OGRE_SAMPLES_INCLUDEPATH "/usr/local/share/OGRE/samples/Common/include/") 
elseif(EXISTS "/usr/lib/OGRE/cmake")
    set(CMAKE_MODULE_PATH "/usr/lib/OGRE/cmake/modules/;${CMAKE_MODULE_PATH}")
    set(OGRE_SAMPLES_INCLUDEPATH "/usr/lib/OGRE/samples/Common/include/") 
elseif(EXISTS "/usr/share/OGRE/cmake")
    set(CMAKE_MODULE_PATH "/usr/share/OGRE/cmake/modules/;${CMAKE_MODULE_PATH}")
    set(OGRE_SAMPLES_INCLUDEPATH "/usr/share/OGRE/samples/Common/include/") 
else ()
    message(SEND_ERROR "Failed to find module path.")
endif()
 
find_package(OGRE REQUIRED)
 
find_package(OIS REQUIRED)
 
if(NOT OIS_FOUND)
	message(SEND_ERROR "Failed to find OIS.")
endif()
 
# Find Boost
if (NOT OGRE_BUILD_PLATFORM_IPHONE)
	if (WIN32 OR APPLE)
		set(Boost_USE_STATIC_LIBS TRUE)
	else ()
		# Statically linking boost to a dynamic Ogre build doesn't work on Linux 64bit
		set(Boost_USE_STATIC_LIBS ${OGRE_STATIC})
	endif ()
	if (MINGW)
		# this is probably a bug in CMake: the boost find module tries to look for
		# boost libraries with name libboost_*, but CMake already prefixes library
		# search names with "lib". This is the workaround.
		set(CMAKE_FIND_LIBRARY_PREFIXES ${CMAKE_FIND_LIBRARY_PREFIXES} "")
	endif ()
	set(Boost_ADDITIONAL_VERSIONS "1.44" "1.44.0" "1.42" "1.42.0" "1.41.0" "1.41" "1.40.0" "1.40" "1.39.0" "1.39" "1.38.0" "1.38" "1.37.0" "1.37" )
	# Components that need linking (NB does not include header-only components like bind)
	set(OGRE_BOOST_COMPONENTS thread date_time)
	find_package(Boost COMPONENTS ${OGRE_BOOST_COMPONENTS} QUIET)
	if (NOT Boost_FOUND)
		# Try again with the other type of libs
		set(Boost_USE_STATIC_LIBS NOT ${Boost_USE_STATIC_LIBS})
		find_package(Boost COMPONENTS ${OGRE_BOOST_COMPONENTS} QUIET)
	endif()
	find_package(Boost QUIET)
 
	# Set up referencing of Boost
	include_directories(${Boost_INCLUDE_DIR})
	add_definitions(-DBOOST_ALL_NO_LIB)
	set(OGRE_LIBRARIES ${OGRE_LIBRARIES} ${Boost_LIBRARIES})
endif()
 
include_directories( 
    ${OIS_INCLUDE_DIRS}
    ${OGRE_INCLUDE_DIRS}
    ${OGRE_SAMPLES_INCLUDEPATH}
)
 
set(EXECUTABLE_OUTPUT_PATH bin)
 
file(GLOB_RECURSE
    SOURCE_FILES
    src/*
)
 
add_executable(SMA ${SOURCE_FILES})

target_link_libraries(SMA ${OGRE_LIBRARIES} ${OIS_LIBRARIES})
 
