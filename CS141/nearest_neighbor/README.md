### Description.
This is a Python implementation of the Nearest Neighbor problem. The program calculates the closest two points in an array of points via two methods, brute force and divide and conquer, and compares the runtime of each. 

### Usage.
Place all files in the same directory. Requires python3. A shell script which provides a test demonstration, or the program may be run by invoking `python3 nearest_neighbor.py -<bf|dc|both> <inputfile>.txt`. `-bf` invokes it using brute force, `-dc` demonstrates it using divide and conquer only, and `-both` will run both algorithms for direct comparison.

Input files should be formatted as floating-point pairs seperated by a single
space. For example:
```
5.1 8.7
-1.2 3.7
-4.5 -6.1
12.7 14.21
1.6 3.1
7.9 15.13
18.4 -25.3
11.2 -6.3
7.1 -3.9
4.6 2.9
```