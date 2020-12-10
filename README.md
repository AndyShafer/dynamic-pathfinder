# Dynamic Pathfinder

This project was made for my senior project. It does pathfinding through simple geometry consisting of line segments. What makes this project special, is while most pathfinding programs assume that the obstacles are static, this one can work in a dynamic environment. The endpoints of the line segment can independently move at a constant velocity. This project includes a library that handles the pathfinding, an editor that allows you to create environments and visuallize paths, and a web app that demonstrates the algorithm.

## Building

To build, execute <code>make all</code> from the project directory.

## Notes

* The pathfinding algorithm uses a timestep to approximate the shortest path. A smaller timestep will result in more optimal paths but can increase the computation time by a very large amount.
* The web app has an option to show the path as you modify the environment. This results in the path being recalculated with each change and can slow down the application if a small timestep is also being used.
