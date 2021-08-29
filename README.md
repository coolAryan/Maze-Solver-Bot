# Maze-Solver-Bot
It is a Robotics Project where a robot is made using Arduino and IR Sensors
The objective is to make Robot Traverse Through The Shortest Path 

In its dry run,it traverse through the whole maze then in its final run it traverse through the Shortest path

In Algorithm Part,
2 Approaches are used either we can use 
```C#
LHR-"Left Hand Rule" 
RHR-"Right Hand Rule"
```
In case of Left Hand Rule,
```
> Always turn left if you can
>If you cannot turn left, go straight
>If you cannot turn left, or go straight, turn right
>If you cannot turn left, go straight, or turn right, turn around because you must be at a dead end
Now in order to achieve shortest path
```
*  LBR = B
*  LBS = R
*  LBL = S
*  SBL = R
*  SBS = B
*  RBL = B
```
For example, from the starting point:

* Start moving
* (L) eft turn is made at found intersection
* Add "L" to list
* Check if last three on list can be shortened: NO, only one turn recorded.
* (B) ack at a found dead end
* Add "B" to list
* Check if last three on list can be shortened: NO, only two turns recorded.
* (L) eft turn again when it finds the initial intersection at which it previously turned left
* Add "L" to list
* Check if last three on list can be shortened: YES.
* Replace "LBL" with "S" traight
* Continue until end point is found.
```
```
**Now The Array Stores The Shortest Path Without any Back Turns or B Hence it Traverses through the Shortest Path**
```
