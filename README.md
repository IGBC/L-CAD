# L-CAD                                                          {#mainpage}
### Project Goal:
L-CAD is a Logic Design / Simulation Package, for aiding the design of logic Systems. Ultimately the goals for this project are for it to function as a stand in replacement for proprietary solutions provided by companies like Xilinx and Altera, providing everything necessary for designing a HDL system right up to the point where the system must be compiled and uploaded to a chip. 

The targeted users for this project are students. This project aims to help their studies with a free (as in speech) comprehensive tool-set for examining logic systems and understanding their behaviour. This project will likely also be useful for engineers or programmers looking to debug their systems, however the higher levels of polish typical in professional development environments are not currently a high priority for this project.

Several of the planned features are designed to make this software beginner friendly, namely the project will use visual simulation to clearly explain what is happening inside the logic structure, and the ability to interface the software with GPIO controllers, enabling the use of real electronics as inputs or outputs from the system.

### Planned Features:
* GUI for all program features, including drag and drop interface for creating logic networks, that will visualise the states of all components in the system.
* Composite logic structure blocks. 
* Real time, or step based simulation. (Using a massively-multi-threaded logic engine)
* Interface for Real world input-output to GPIO boards. (Raspberry Pi and similar)
* Support for exporting projects in (V)HDL or similar suitable format Format.
* Support for the GUI, Simulation and IO module to all be on separate devices connected via a network.

### Current Project status:
 - **(26/11/16)** After discovering a sever loop stability bug in the simulation engine most efforts have gone into fixing that. This has now (mostly) been resolved however the engine needs testing to discover exactly where the rough edges are. This means now development will finally begin on a tool to simulate a given graph from a Raspberry Pi's GPIO. At this point a basic graph language is implemented, and graph loading works.
 - **(30/08/16)** Currently the base simulation code works, including threading, with some early optimisation. The next steps are to provide a clean API to work with then begin adding analysis algorithms to the simulation, meanwhile beginning development on a usable user interface. (Probably just a CLI to begin with; sorry guys and girls.) A current side goal is to make logic graph serialisation possible, allowing graph loading and unloading. 

### Building:
This project uses CMake to build, however I'm lazy so there is a make file that automates CMake with a clean build by default. to build call `make` that will automatically call CMake then run make on the generated build files. (make -> cmake -> make)

There are demos in `.../L-CAD/lcadengine/src/main.c`, which compiles to `.../L-CAD/build/lcadengine/testmain`. Have fun.

### Licence:
This software is licensed under the GNU Affero General Public License v3.0 (AGPLv3) open source licence. Additionally the use of this software is restricted by the Non-Military Humane License (NMHL) https://github.com/infuanfu/NMHL

