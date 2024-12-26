
# Brief

... more



# How to run?

### Step 1
Install arm compiler by the following CMD :

```bash
sudo apt install gcc-aarch64-linux-gnu g++-aarch64-linux-gnu
```

### Step 2
Setup the `soc-sdk` directory in `CMakeLists.txt` to include both libraries and header files.

### Step 3
Go to the folder `cross-compile` and run the following system script :

```bash
./build.sh
# ./build.sh rm    # this CMD will remove all files in build folder first and compile code next
```

and the compilation and executable file will be automatically done and generated.

### Step 4
Move the `build` folder to sophon device:

```bash
scp -r build/ linaro@192.168.110.225:/home/linaro/algo
```

and setup the `LD_LIBRARY_PATH` in `bashrc` file:

```bash
echo 'export LD_LIBRARY_PATH=/home/linaro/algo/build/lib:$LD_LIBRARY_PATH' >> ~/.bashrc
source ~/.bashrc
```

### Step 5
And finally, the executable file can be run on the device.

```bash
./build/exe
```


# Other References

... more

