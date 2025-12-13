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