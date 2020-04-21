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
You *MUST* build this software on a Unix based machine. I cannot currently test on a Mac, but
if you are proficient in homebrew, you may download the dependencies yourself and try to use
CMake. Alternatively, every student at Oregon State University has access to 
[VMware for free](https://it.engineering.oregonstate.edu/download-software-your-personal-computer-or-laptop#ui-accordion-jquery-ui-filter-header-8),
so I would suggest downloading the software and running a distribution of 
[Debian](https://cdimage.debian.org/debian-cd/current/amd64/iso-cd/debian-10.3.0-amd64-netinst.iso).
I will write the following Step-By-Step guide assuming you have a fresh installation of Debian.


## Dependencies
You will need the following dependencies
- CMake 13.2
- doxygen (For contributing)
- SFML Libraries

## Step By Step

### Setting up Debian
I had no idea Debian was so minimal when I first started using it. Depending on the version
chosen by the user, it can be missing some important tools.
[Digital Ocean has some nice tutorials](https://www.digitalocean.com/community/tutorials/initial-server-setup-with-debian-9)
if you're interested, but here are some suggested steps to set up your Operating System.

1. Open up the application: __terminal__
2. Run the commands: `su` | This will enable an admin bash shell.
3. `apt-get update` | This will update the package manager index
4. `apt-get install sudo` | This will install the sudo command
5. `usermod -aG sudo USERNAME` : Replace `USERNAME` with the user you set up with the Operating System (Not Root)


This will add the user as an admin user, so you do not have to run everything in the admin bash shell. This caused me
so many problems early in development.


6. `exit` | Return from the admin shell.
7. Log out and Logback in (optional but recommended). | This will make sure sudo is set up correctly. 


### Installing Dependencies
On a fresh installation of Debian, one still needs to install all of the necessary tools for developing in C++ with SFML and CMake.
The instructions below focus on acquiring each package.

1. Open up the application __terminal__
2. Run the commands: `sudo apt-get install build-essential` | This will install all the common developer tools like C++ and Make.
3. `sudo apt-get install cmake` | This will install CMake
4. `sudo apt-get install libsfml-dev` | This will install SFML
5. (If you don't have git) `sudo apt-get install git` | This will install the git CLI.

Once those are installed, you should be good to go!

### Cloning the Repository
To clone the repository you should be able to use the following link 
[https://github.com/TFlexSoom/DreamZDash.git](https://github.com/TFlexSoom/DreamZDash.git) to install all of the source code.
This should work in the following command:


`git clone https://github.com/TFlexSoom/DreamZDash.git`


*Note: You may want to create a new directory to store all of your git projects.*


`mkdir NAME_OF_DIRECTORY`


### Building the Repository
We will be using CMake to build the repository. Make sure you `cd DreamZDash` before following the further instructions.

## Build Commands
The Simplest way to build is to use `./build.sh` which does all the configuration of CMake and the copying of assets.

However, the following may be done manually:

The CMakeLists.txt needs to be invoked with cmake.

For using GNU tools (which we recommend) the following command should be used
`cmake -S src/ -B build/ -G "Unix Makefiles"`

Then change directories to the `build/` directory aka `cd ./build` and run the `make` tool.

In the future this will be set up under continuous integration.

### Running The Project
Once built with make, the binary will reside in `PROJECT_ROOT/build/DreamZDash-Display/DreamZDash-Display.out` which can
be executed by your hearts content

### Cleaning the project
CMake does nto come with a cleaning tool. So when you are finished, go ahead and `rm -rf build` or whatever you set the build
directory to for CMake.

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
