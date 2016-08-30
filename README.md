# L-CAD
### Project Goal:
L-CAD is a Logic Design / Simulation Package, for aiding the design of logic Systems. Ultimatly the goals for this project are for it to function as a stand in replacement for propetory solutions provided by companies like Xilinx and Altera, providing everything neccercary for designing a HDL system right up to the point where the system must be compiled and uploaded to a chip. 

The targeted end users for this project are students. This project aims to help their studies with a free (as in speech) comprehensive toolset for examining logic systems and understanding their behaviour. This project will likely also be useful for engineers or programmers looking to debug their systems, however the higher levels of polish typical in professional development environments are not currently a high priority for this project.

Several of the planned features are designed to make this software beginer freindly, namely the project will use visual simulation to clearly explain what is happening inside the logic structure, and the ability to interface the software with GPIO controllers, enabling the use of real electronics as inputs or outputs from the system.

### Planned Features:
* GUI for all program features, including drag and drop interface for creating logic networks, that will visulise the states of all components in the system.
* Composite logic structure blocks. 
* Real time, or step based simulation. (Using a massively-multithreaded logic engine)
* Interface for Real world input-output to GPIO boards. (Raspberry Pi and similar)
* Support for exporting projects in (V)HDL Format.
* Support for the GUI, Simulation and IO module to all be on seperate devices connected via a network.

### Current Project status:
As of updating this file (30/08/16) currently the base simulation code works, including threading, with some early optimisation. The next steps are to provide a clean API to work with then begin adding analisys algorithms to the sim, meanwhile beginning development on a usable user interface. (Probably just a CLI to begin with; sorry guys and girls.) A current side goal is to make logic graph serialisation possible, allowing graph loading and unloading. 

### Building:
**Please remember to pull the submodules before attempting to build.**

This project uses CMake to build, however I'm lazy so there is a make file that automates CMake with a clean build by default. to build call `make` that will automatically call CMake then run make on the generated build files. (make -> cmake -> make)

There are demos in `.../L-CAD/lcadengine/src/main.c`, which compiles to `.../L-CAD/build/lcadengine/testmain`. Have fun.

### Licence:
This software is licenced under the GNU Affero General Public License v3.0 (AGPLv3) open source liecence. Additionally the use of this software is restricted by the Non-Military Humane License (NMHL) https://github.com/infuanfu/NMHL

