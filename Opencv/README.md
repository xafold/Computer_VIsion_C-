
## Building OpenCV from Source Using CMake:

1. Clonning the the OpenCV and OpenCV_contrib:
   
```
git clone https://github.com/opencv/opencv.git
git clone https://github.com/opencv/opencv_contrib.git
```

2. Then opening the directory of the opencv clonned repo:

```
cd opencv
mkdir build
```

3. Installing the CMake from the command line:
   
```
sudo pacman -S cmake
```

4. Adding the directory of the Opencv folder (i.e clonned repo) in the space "Where is the source code" i.e `/home/xafold/opencv` and adding the folder location where source to be build i.e `/home/xafold/opencv/build` in "Where to build the binaries".

5. Then the appropriate Makefiles generator needs to be selected for this process we can use **Unix Makefiles**.
   
6. After all this we need to click **Configure** button and after it finished configuring we need to select some few modules and dependencies like:
   * `WITH_VTK`: should be enabled.
   * `WITH_OPENJPEG`, `WITH_JPEG`, `BUILD_OPENJPEG`, `BUILD_JPEG`: should be enabled.
   * `WITH_EIGEN`: should be enabled. <br>
  It configures the CMake project based on the settings and optionsspecified in the GUI or through command-line arguments. This includes setting up compiler options, library paths, and other project-specific settings.

7. We also need to build with OpenCV extra modules so we have alrrady clonned the opencv_contrib repo in locallly. So we then provide the path of opencv_contrib/modules i.e `/home/xafold/opencv_contrib/modules` in the `OPENCV_EXTRA_MODULES_PATH`.

8. Finally, we need to click **Generate** button to generates the actual build files of OpenCV required for chosen build system (e.g., Makefiles, Visual Studio solution files ). These files are created in the build directory that we specify in the GUI.
   
9. After that we go to the folder i.e `/home/xafold/opencv/build` where build files are located for OpenCV and enter the command:

    ```
    cmake --build .
    ```