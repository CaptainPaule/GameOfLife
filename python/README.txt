#######
Caution
#######

Please don't remove this file, otherwise the setup.py script will not work correctly.



##################
Build Instructions
##################

The python interface will build automatically when building the root project fiber with CMake.

For instance:

$ mkdir fiber_build
$ cd fiber_build
$ cmake ../fiber
$ make



#######################
Installation (optional)
#######################

Warning: This step should be done only from the build directory.

$ python setup.py install --user



###########
Basic Tests
###########

The basic_tests.py script in the /bin directory will only work correctly after the installation step (above) and only
from the installation directory.

$ python basic_tests.py

or from ipython:

$ %run basic_tests.py



####################
Wrapping a C++ Class
####################

A C++ class wrapper in cython consists of two definition files and one implementation file, whereas definition files 
have the ending .pxd and are located in the include directory and implementation files have the ending .pyx and are 
located in the src directory (relative to the /python directory). One of the definition files contains the 
API for the C++ class that has to be wrapped, and the other definition file contains the cython class definition for 
the wrapper itself. The implementation file is self-explanatory. The wrapper smf for the C++ class SMF_SSFM is simple
and can serve as an example for beginners. 
To add the new files into the build system, one has only to extend the /python/src/CMakeLists.txt file. At least one 
example can be found there.
Dont't forget to write a basic test for the new wrapper in the /python/test/basic_tests.py file.



#######################
How CMake builds Cython
#######################

First the ReplicatePythonSourceTree.cmake script replicates the /bin and /src directories and all Python scripts from
the source directory /python into the build directory. Then CMake continues with the actually build process.
The UseCython.cmake file contains the main functionality to build Cython, used from the CMake script in /python/src. 
The function cython_add_module first calls the function compile_pyx, that produces a .cxx file from the cython files.
Then it calls the CMake function python_add_module, that builds and links the just produced .cxx file and the C++
class, that has to be wrapped. The build process finishes with linking the new build python module with the ArrayFire 
and Python libraries.