## Compiling the C++ project using the CMakeLists and Makefile

1. First create a project folder i.e source code folder where we have source code `main.cpp`, required library source code `my_lib.cpp` and header file for that library `my_lib.hpp`
   
2. Then, we create a `CMakeLists.txt` which will include following:
   *  `cmake_minimum_required(VERSION 3.10)` minimum version required for CMake to generate build files.

    * `project(...)` statement includes name of project i.e `hello_world`, versioned at 1.0, and is in C++.

    * We create a library called `mylib`, it consists `my_lib.cpp` and `my_lib.hpp`. We then create our executable main, it consists of file `main.cpp`. We then link main with our library mylib. The `PRIVATE` keyword means that this linking is not transitive: (mylib is not exposed to other binaries that link against main). It is less important forexecutable, for libraries that depend on other libraries we use PRIVATE so downstream users are not burdened with unnecessary libraries.
  
3. Then create the build directory by using
    ```
    mkdir build
    cd build
    ```

4. Then we run following command to make the build of the source code in the **build** directory
    ```
    cmake ..
    ```

5. After creating the build of the project source code and building using `cmake ..` we can see following files and folder in the build folder 
   ```
   CMakeFiles/     cmake_install.cmake      CMakeCache.txt    libmylib.a       main       Makefile
   ```
   * We don't need to do anything on `CMakeFiles/` and `CMakeCache.txt` since 
   * `cmake_install.cmake` is the install script of our project it is needed when we are developing our own libraries.
   * `Makefile` is text file for the `make` tool to digest. `make` will read this file and compile our source code. They are generated automatically when we run `cmake ..` in the build directory.

6. Then we run `make` which will create `main` executable and `libmylib.a` file and we then run `main` executable using command
    ```
    ./main
    ```
    this will run our code from `main.cpp` with all the libraries included as executable `main`.

# References

- [Build With Cmake](https://vnav.mit.edu/labs/lab1/cmake.html)
- [A Simple make file Tutorial](https://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/)
- [CMake: the devil you know](https://medium.com/@atkinssamuel/cmake-the-devil-you-know-9be0e963e5d6)