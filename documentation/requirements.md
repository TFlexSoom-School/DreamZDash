# Requirements for DreamZDash

## Introduction
This document is a simple list of requirements for the DreamZDash. These requirements must be met as a release by
May 15th at the lates.

## Requirements
- [ ] Shall interface through the Bluetooth controller.
- [ ] Shall launch a game
- [ ] Shall show a battery life
- [ ] Shall display images and graphics
- [ ] Shall show changeable settings
- [ ] Shall modify settings based on user input
- [ ] Shall provide a software power switch
- [ ] A player should be able to use the DreamZBox 2.0 controller without discomfort
- [ ] Shall look aesthetically pleasing
- [ ] Shall use readable text
- [ ] Should remain simple and intuitive
- [ ] Should have use without explanation
- [ ] Should answer all potential user questions
- [ ] May include a throbber for loading content
- [ ] Shall pre-load images for games
- [ ] Shall display at correct resolution for potential devices
- [ ] May protect against setting changes harming battery life
- [ ] Shall have 3 modes
- [ ] Will have an unreachable terminal mode
- [ ] Shall have a startup mode consisting of DreamZDash
- [ ] Shall have a Game Mode consisting of games like Maze of Dreamz
- [ ] Upon failure the Game Mode shall fall back to DreamZDash
- [ ] Shall store conﬁgurations and chosen settings in non-volatile memory
- [ ] Shall store user downloads in non-volatile memory 
- [ ] Shall keep all memory stored on this system 
- [ ] Should not allow other devices to access this data
- [ ] Maze of Dreamz and DreamZDash shall be compiled and compressed into a singular ﬁle

## Explanation
These requirements are not necessarily ordered in any such way. There is no need to verify every requirement.
However, verifying each requirement through tested code would increase application integrity. Verification
currently is put into use cases, but verification code should be considered. Overall these requirements have
already been sorted into features. The features will be listed on GitHub and Below.

# Features

## Introduction
These features are abstractions from the official design document. These embody the requirements listed above.
They work together to accomplish the task for the Dashboard of the DreamzBox 2.0 accurately.

## Feature Lists
These are organized into:
- Title
- Description := What the feature should do
- Targets := Names of Modules within the project this feature surrounds




### DreamZDash-Util: Loader
Many of the components in the DreamZDash software system load something. A singular object which works
to load pieces of data and blocking minimally (i.e. buffering) would be very useful in the project. This
should have an interface according to a directory which is concurrently loaded in byte form. The loader 
should not decode the information, but only load it. A cacheing system is also possible with this 
black box description.
#### Targets
src/DreamZDash-Util/Loader.hpp
src/DreamZDash-Util/Loader.cpp

### DreamZDash-Util: Data Store
This represents for some of the DreamZDash processes a necessary form of IPC. Having a standard object
or template would be useful to provide simplicity to their interfaces. This needs to cache given byte
strings and communicate them to another process.
#### Targets
- src/DreamZDash-Util/DataStore.hpp
- src/DreamZDash-Util/DataStore.cpp



### DreamZKernel
To prevent the application from failing without recovery, the application should use multiple processes.
A singular process should start these other processes (this feature is Coupled with DreamZModes).

#### Targets
src/DreamZKernel.cpp

### DreamZKernel: DreamZModes
These modes surround the possible states of the software. This means a singular process must orchestrate
what state the DreamZDash is in. Consider this state transition `Off => Video => Dashboard => Game`. This
feature is Coupled with DreamZKernel.

#### Targets
- src/DreamZKernel.cpp




### DreamZDash-HardwareStatus
The Hardware Status process takes care of communicating with the hardware for all drivers excluding input.
The objective for this process is to provide a beneficial way to share the status information with the
Display process. This should be done with Inter Process Communication. The data also will need decoding.
#### Targets
- src/DreamZDash-HardwareStatus/*


### DreamZDash-HardwareStatus: Status Loader
The status loader should use the Loader dependency to load information from drivers. The drivers will be
the programs associated with the:
- Wifi Radio
- Battery
#### Targets
- src/DreamZDash-HardwareStatus/StatusLoader.hpp
- src/DreamZDash-HardwareStatus/StatusLoader.cpp

### DreamZDash-HardwareStatus: Port Data Decoder
The Port Data Decoder is the decoding process (a->b) of the loaded information from the hardware drivers
(see Status Loader). This does imply coupling. Additionally the Port Data Decoder will have to choose
an adequate way to decode the information.
#### Targets
- src/DreamZDash-HardwareStatus/PortDataDecoder.hpp
- src/DreamZDash-HardwareStatus/PortDataDecoder.cpp

### DreamZDash-HardwareStatus: Data Store
The Data Store represents the caching and sharing of decoded information. Information is not time
dependent. The goal is to provide accurate information rather than speedy information. I don't think
this is the decision of this object, however, the data store should only lock and update when
a change occurs. This should also consider using the Data Store Util as a parent.
#### Targets
- src/DreamZDash-HardwareStatus/HSDataStore.hpp
- src/DreamZDash-HardwareStatus/HSDataStore.cpp




### GLM (Game Library Manager)
The Game Library Manager or GLM is a process which dictates the available games to the user. The
process will collect the information on the data to send to the Display process. Notice that the
display process will communicate collected data to the Configuration Manager Process. This will
mean some slight coupling there. IMO this process will decide the format of the encoded data.
#### Targets
- src/GLM/*

### GLM : Game FStat Loader
The Game FStat Loader is a loader using the loader dependency. There should be metadata files
associated witht he games. These should include the game name, thumbnail, authors, and exe
pathname perhaps. I would recommend JSON objects for this. I also know people like XAML and
ini files aswell. In any case this will load these types of files as a loader.
#### Targets
- src/GLM/GameFStatLoader.hpp
- src/GLM/GameFStatLoader.cpp

### GLM : Metadata and Image Decoder
See Game FStat Loader. The metadata and image decoder may also be a loader depending on the
way it's input is sending the thumbnail. It's goal is to provide the image and metadata, decoded
in a friendly way for the display. That's all I will say.
#### Targets
- src/GLM/MetaDec.hpp
- src/GLM/MetaDec.cpp

### GLM: Data Store
The Data store for the Game Library Manager will need to lock often and write fast. I would
recommend buffering the data or writing in pieces so the process can communicate data while
still leaving some of the data available to read. This problem will be weird to solve, however
the Data Store Util may also be used to begin with.
#### Targets
- src/GLM/GLMDataStore.hpp
- src/GLM/GLMDataStore.cpp



### DreamZDash-Display
The DreamZDash-Display process works to display all the information collected from other 
processes. It also works to receive and respond to input from the player. The display will
have some difficulty when architected. It should consider what happens if no data loads.
The display will need to communicate as well as possible in all scenarios. We're not going
to solve the halting proble here, but we can respect inputs. It might help to do some research.


Also this will need the use of a graphics framework like QT or SDL. Some multimedia service
to access graphics (See View Orchestration)
#### Targets
- src/DreamZDash-Display/*

### DreamZDash-Display: Asset Cache
The asset cache is a loader and will most likely use the loader dependency. However it should
only have to load once. If it has to load more than once, then it should consider a very 
decent cacheing system. The display is a very time sensitive piece of software and needs
to respond really fast. Doing whatever is necessary to mitigate load times will help.
#### Targets
- src/DreamZDash-Display/AssetCache.hpp
- src/DreamZDash-Display/AssetCache.cpp

### DreamZDash-Display: Input Handle
The Input Handle is an object which will possible load from drivers. The loader framework was
once again envisioned, but this is a weird one. It may help to only live out a read only stream.
In either case, the input will need to send the data directly to View Orchestration when recieved.
#### Targets
- src/DreamZDash-Display/InputHandle.hpp
- src/DreamZDash-Display/InputHandle.cpp

### DreamZDash-Display: View Orchestration
The View Orchestration is actually pretty monolithic and might need some decomposition. In any
case it handles all drawing of "views" for the user. There is a lot of places this could go. 
I will leave it up to the architect how this will be programmed. In any case it will receive
inputs when necessary and constantly be asked to draw.
#### Targets
- src/DreamZDash-Display/ViewOrchestration.hpp
- src/DreamZDash-Display/ViewOrchestration.cpp
- src/DreamZDash-Display/ViewOrchHelpers/*

### DreamZDash-Display: Console System Broadcaster
This is also pretty up in the air. According to the design document, this should send a
call of somesort to the configuration manager. This is for when the display needs to change
brightness or launch a game. This could also be done through the operating system (exec call
perhaps?). In any case this will definitely need some Inter Process Communication.
#### Targets
- src/DreamZDash-Display/ConsoleSystemBroadcaster.hpp
- src/DreamZDash-Display/ConsoleSystemBroadcaster.cpp




### DreamZDash-ConfigurationManager
The Configuration manager takes care of fulfilling all of the user's previously set settings.
This could include gamma, dark-mode (rofl), or WiFi being turned on. Most of these will have
to be fulfilled through communication with the Operating System. This also may require further
distro editting. In any case it should store and work with the data created from the user.
#### Targets
- src/DreamZDash-ConfigurationManager/*

### DreamZDash-ConfigurationManager: Console Configuration Handler 
This object will take care of communicating with the operating system to change the specified
settings. It will take care of the settings changed by the user and the past settings loaded
from the loader (see Broadcast Channel and Configuration Loader).
#### Targets
- src/DreamZDash-ConfigurationManager/ConsoleConfHandler.hpp
- src/DreamZDash-ConfigurationManager/ConsoleConfHandler.cpp

### DreamZDash-ConfigurationManager: Configuration Loader
The configuration loader is a loader and a saver unlike other loaders. Instead, it will actually
store information periodically. It will definitely use the loader dependency. The loader should
not have storage capability so that will be added on by this child. The data should not need
decoding since the files are project created.
#### Targets
- src/DreamZDash-ConfigurationManager/ConfigurationLoader.hpp
- src/DreamZDash-ConfigurationManager/ConfigurationLoader.cpp

### DreamZDash-ConfigurationManager: Broadcast Channel
The broadcast channel handles system calls carried from the view manager. It will then propagate
those changes to the Configuration Manager in a way it can understand. It also might have to send
information to the game launcher instead (in case of a game launch). This object has a large amount
of coupling, but this object's objective is for interprocess communication.
#### Targets
- src/DreamZDash-ConfigurationManager/BroadcastChannel.hpp
- src/DreamZDash-ConfigurationManager/BroadcastChannel.cpp

    ### DreamZDash-ConfigurationManager: Game Launcher
    The Game Launcher launches the executable gathered from the broadcast channel. This will start a seperate
    process and send the processID to the Kernel. Then most processes will exit upon this occurence, but the
    Kernel should handle this.
    #### Targets
    - src/DreamZDash-ConfigurationManager/GameLauncher.hpp
    - src/DreamZDash-ConfigurationManager/GameLauncher.cpp





