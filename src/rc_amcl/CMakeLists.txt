cmake_minimum_required(VERSION 2.8.3)
project(rc_amcl)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
	amcl
	move_base
	map_server
	rviz
)

###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if you package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
#	INCLUDE_DIRS include
#	LIBRARIES random_walk
	CATKIN_DEPENDS amcl move_base map_server rviz turtlebot3_simulations rc_simul_worlds
#	DEPENDS traxbot_stingbot
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
# include_directories(include)
#include_directories(
#  include ${catkin_INCLUDE_DIRS}
#)

## Declare a C++ library
# add_library(random_walk
#   src/${PROJECT_NAME}/random_walk.cpp
# )
#add_library(tsbot_drivers
#	src/tsbot_drivers.cpp
#)

## Add cmake target dependencies of the library
## as an example, code may need to be generated before libraries
## either from message generation or dynamic reconfigure
# add_dependencies(random_walk ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

## Declare a C++ executable
#add_executable(traxbot src/traxbot.cpp src/tsbot_drivers.cpp)

## Add cmake target dependencies of the executable
## same as for the library above
# add_dependencies(random_walk_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

## Specify libraries to link a library or executable target against
# target_link_libraries(random_walk_node
#   ${catkin_LIBRARIES}
# )
#target_link_libraries(traxbot ${catkin_LIBRARIES})


#############
## Install ##
#############

# all install targets should use catkin DESTINATION variables
# See http://ros.org/doc/api/catkin/html/adv_user_guide/variables.html

## Mark executable scripts (Python etc.) for installation
## in contrast to setup.py, you can choose the destination
# install(PROGRAMS
#   scripts/my_python_script
#   DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )

## Mark executables and/or libraries for installation
# install(TARGETS random_walk random_walk_node
#   ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#   LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#   RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )

## Mark cpp header files for installation
# install(DIRECTORY include/${PROJECT_NAME}/
#   DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
#   FILES_MATCHING PATTERN "*.h"
#   PATTERN ".svn" EXCLUDE
# )

## Mark other files for installation (e.g. launch and bag files, etc.)
install(FILES
	less_modular-stage_amcl_tiny.launch
	less_modular-stage_amcl_building.launch
	run_amcl_tiny.launch
	run_amcl_building.launch
	amcl_rndw_pioneer.launch
	stage_amcl_tiny.launch
	stage_amcl_building.launch
	stage_amcl_building_2robots.launch
	stage_amcl_building_8robots.launch
	stage_move_base_building.launch
	amcl_rndw_turtlebot3.launch
	gazebo_amcl_building.launch
	gazebo_amcl_building_2robots.launch
	gazebo_amcl_building_8robots.launch
	amcl_S63.launch.launch
	amcl_S63-from_rosbag.launch
	move_base_S63.launch
   DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)

#############
## Testing ##
#############

## Add gtest based cpp test target and link libraries
# catkin_add_gtest(${PROJECT_NAME}-test test/test_random_walk.cpp)
# if(TARGET ${PROJECT_NAME}-test)
#   target_link_libraries(${PROJECT_NAME}-test ${PROJECT_NAME})
# endif()

## Add folders to be run by python nosetests
# catkin_add_nosetests(test)

