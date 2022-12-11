# Install script for directory: /home/nion/cog_rob_project/src/rc_amcl

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/nion/cog_rob_project/build/rc_amcl/catkin_generated/installspace/rc_amcl.pc")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/rc_amcl/cmake" TYPE FILE FILES
    "/home/nion/cog_rob_project/build/rc_amcl/catkin_generated/installspace/rc_amclConfig.cmake"
    "/home/nion/cog_rob_project/build/rc_amcl/catkin_generated/installspace/rc_amclConfig-version.cmake"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/rc_amcl" TYPE FILE FILES "/home/nion/cog_rob_project/src/rc_amcl/package.xml")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/rc_amcl" TYPE FILE FILES
    "/home/nion/cog_rob_project/src/rc_amcl/less_modular-stage_amcl_tiny.launch"
    "/home/nion/cog_rob_project/src/rc_amcl/less_modular-stage_amcl_building.launch"
    "/home/nion/cog_rob_project/src/rc_amcl/run_amcl_tiny.launch"
    "/home/nion/cog_rob_project/src/rc_amcl/run_amcl_building.launch"
    "/home/nion/cog_rob_project/src/rc_amcl/amcl_rndw_pioneer.launch"
    "/home/nion/cog_rob_project/src/rc_amcl/stage_amcl_tiny.launch"
    "/home/nion/cog_rob_project/src/rc_amcl/stage_amcl_building.launch"
    "/home/nion/cog_rob_project/src/rc_amcl/stage_amcl_building_2robots.launch"
    "/home/nion/cog_rob_project/src/rc_amcl/stage_amcl_building_8robots.launch"
    "/home/nion/cog_rob_project/src/rc_amcl/stage_move_base_building.launch"
    "/home/nion/cog_rob_project/src/rc_amcl/amcl_rndw_turtlebot3.launch"
    "/home/nion/cog_rob_project/src/rc_amcl/gazebo_amcl_building.launch"
    "/home/nion/cog_rob_project/src/rc_amcl/gazebo_amcl_building_2robots.launch"
    "/home/nion/cog_rob_project/src/rc_amcl/gazebo_amcl_building_8robots.launch"
    "/home/nion/cog_rob_project/src/rc_amcl/amcl_S63.launch.launch"
    "/home/nion/cog_rob_project/src/rc_amcl/amcl_S63-from_rosbag.launch"
    "/home/nion/cog_rob_project/src/rc_amcl/move_base_S63.launch"
    )
endif()

