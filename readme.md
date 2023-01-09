
# To run the .cpp file, make sure the following 2 things:

1. The file contains a function called "main"

2. Use the CMD to compile code "g++ name.cpp -o exeName"

3. Use the CMD to run code "./exeName"



# To run the CMakeLists project file:

### 1. With Clion

1. Click  the "Menu column -> Tool -> CMake -> Unload CMake project" to detach the current CMake target (unbind the default target) .
2. Click your target CMakeLists file and then run "Menu column -> Tool -> CMake -> Reload CMake project"

### 2. With terminal / bash only

1. type the following commands in the terminal (in the folder of each project)

```bash
mkdir build
cd build
cmake ..
make
```