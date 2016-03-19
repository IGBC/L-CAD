# L-CAD
Java Based Logic Design / Simulation Package.

### Project Goal:
Create a Logic IDE for the development of logic systems that can be simulated and tested in software, before being exported in useful formats. (for example to burn an FPGA) 
This tool should be simple enough to use that it can be used to educate students on the basics of boolean logic, but powerful enough that an advanced user can use it to develop an application for a multi thousand gate FPGA.

### Planned Features:
* Qt(?) Based GUI for all program features, including drag and drop interface for creating logic networks, that will visulise the states of all components in the system.
* Composite logic structure blocks. 
* Real time, or step based simulation. (Using a massively-multithreaded logic engine)
* Interface for Real world input-output to GPIO boards. (Raspberry Pi and similar)
* Support for exporting projects in (V)HDL Format.
* Support for the GUI, Simulation and IO module to all be on seperate devices connected via a network.
