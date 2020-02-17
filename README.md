# DreamZDash
A Dashboard coded in C++ for the DreamzBox 2.0 Console.


Made By CS29 Dreamz Catcherz


Oregon State University EECS Capstone 2020

# LICENSE
This project complies with multiple licenses listed in the root directory
of this project. Please read and follow all license agreements within the root
of this project. These files comply to the regular expresssion `*LICENSE`

# Description
The DreamZDash takes care of the software layer for console management. This will work upon
the distribution of the Linux used in the console. If a new distribution is created, the project
will be shared elsewhere. Instead, DreamZDash will provide the user with information about
system performance (i.e. battery life, storage, and gamma). It will also provide the launch point
into other game applications like [Maze of Dreamz](https://github.com/TFlexSoom/MazeOfDreamz).
Further information will be in the documentation directory of this project.

# How To Build
## Dependencies
You will need the following dependencies
- CMake 13.2
- doxygen (For contributing)

## Command
The CMakeLists.txt needs to be invoked with cmake.

For using GNU tools (which we recommend) the following command should be used
`cmake -S . -B bin/ -G "Unix Makefiles"`

However, a majority of the developers are using MinGW. This may be invoked
explicitely for the same behaviour
`cmake -S . -B bin/ -G "MinGW Makefiles"`

In the future this will be set up under continuous integration.

# How to Contribute
The master branch will be reserved for completed sprints. The following branches should be used
- develop := The current sprint branch. Pull requests should merge with this.
- issue## := ## represents the issue number the branch should solve.

*Please* do not pull request or push to the master branch. This way anyone pulling from the project
can safely gather their own branch.

## Contact
Tristan Hilbert


hilbertt@oregonstate.edu


CS 29 Dreamz Catcherz
