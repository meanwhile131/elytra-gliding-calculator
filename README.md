# Compiling
Requirements:
- CMake
- Git

Run in a terminal on Linux or in Git Bash on Windows:
```shell
git clone --recurse-submodules https://github.com/meanwhile131/elytra-gliding-calculator.git
cmake -DCMAKE_BUILD_TYPE=Release -B build
cmake --build build
```

# Running
Requirements:
- Gnuplot
```shell
./infinite_flight
```
in ./build. Check build/log.txt and build/graph.png. These outputs for the latest commit are in the [output branch](https://github.com/meanwhile131/elytra-gliding-calculator/tree/output).

![infinite_flight graph](https://github.com/meanwhile131/elytra-gliding-calculator/blob/output/build/graph.png?raw=true "Graph for infinite_flight.cpp")
