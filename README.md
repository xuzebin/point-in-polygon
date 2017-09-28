# Point in Polygon
Experimenting the point-in-polygon algorithm with C++ and OpenGL.

## Runtime
O(N), where N = #sides of polygon(s).

## Build and Run
```
mkdir build && cd build
cmake ..
make

// Run example with single polygon
./Example

// Run example with multiple polygons 
// (i.e. you can draw multiple polygons and test
// if a point is inside of any of the polygons).
./Example2
```

## Examples
![Alt Text](https://github.com/xuzebin/point-in-polygon/raw/master/pip_nyu.gif)
![Alt Text](https://github.com/xuzebin/point-in-polygon/raw/master/pip.gif)
