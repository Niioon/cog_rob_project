# Install script for directory: /home/nion/cog_rob_project/src/rc_gmapping

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/nion/cog_rob_project/install")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/nion/cog_rob_project/build/rc_gmapping/catkin_generated/installspace/rc_gmapping.pc")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/rc_gmapping/cmake" TYPE FILE FILES
    "/home/nion/cog_rob_project/build/rc_gmapping/catkin_generated/installspace/rc_gmappingConfig.cmake"
    "/home/nion/cog_rob_project/build/rc_gmapping/catkin_generated/installspace/rc_gmappingConfig-version.cmake"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/rc_gmapping" TYPE FILE FILES "/home/nion/cog_rob_project/src/rc_gmapping/package.xml")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/rc_gmapping" TYPE FILE FILES
    "/home/nion/cog_rob_project/src/rc_gmapping/gmapping_from_rosbag.launch"
    "/home/nion/cog_rob_project/src/rc_gmapping/octomap_gmapping.launch"
    "/home/nion/cog_rob_project/src/rc_gmapping/octomap_gmapping_from_rosbag.launch"
    "/home/nion/cog_rob_project/src/rc_gmapping/stage_gmapping_building.launch"
    "/home/nion/cog_rob_project/src/rc_gmapping/stage_gmapping_exploration_building.launch"
    "/home/nion/cog_rob_project/src/rc_gmapping/gazebo_gmapping_building.launch"
    "/home/nion/cog_rob_project/src/rc_gmapping/gazebo_gmapping_exploration_building.launch"
    "/home/nion/cog_rob_project/src/rc_gmapping/coppelia_1robot_gmapping_exploration.launch"
    "/home/nion/cog_rob_project/src/rc_gmapping/coppelia_2robots-r1_gmapping_exploration-r2_random_walk.launch"
    )
endif()

