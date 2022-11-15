# Midterm Report

**Group Members**: Nion Schürmeyer, Slaven, Lukas


## Autonomous Exploration

We use the explore_lite package for greedy exploration of the given environment and create 2D map using gmapping. When the robot stops moving for a minute, the map is saved and the exloration is declared finished.

For launching the exploration either launch  `explore_building.launch` or `explore_museum.launch` in the package my `my_robot_control/launch`.


In the building environment the robot does not have a problem to create a complete map. In the museum environment it frequently gets stuck. We are not quite sure why but maybe the openess of the world (no walls surrounding everything) poses a problem for the explore algorithm.

## Navigation




