# L-CAD
#### Logic Design / Simulation Package.

### Project Goal:
Create a Logic IDE for the development of logic systems that can be simulated and tested in software, before being exported in useful formats. (for example to burn an FPGA) 
This tool should be simple enough to use that it can be used to educate students on the basics of boolean logic, but powerful enough that an advanced user can use it to develop an application for a multi thousand gate FPGA.

### Planned Features:
* Qt Based GUI for all program features, including drag and drop interface for creating logic networks, that will visulise the states of all components in the system.
* Composite logic structure blocks. 
* Real time, or step based simulation. (Using a massively-multithreaded logic engine) (Research into openCL acceleration is being conducted)
* Interface for Real world input-output to GPIO boards. (Raspberry Pi and similar)
* Support for exporting projects in (V)HDL Format.
* Support for the GUI, Simulation and IO module to all be on seperate devices connected via a network.

### Building:
This project uses the ant build system. The default target will build the entire project and generate a jar file automatically. All needed dependancies are included in this repository. 

The project is developed using Eclipse, and can be imported with eclipse's ant xml import functionality. To import the project once cloned do:
 1. in the projects pane "new->project->Java Project from Existing Ant Buildfile"
 2. select `../L-CAD/build.xml` as the buildfile
 3. click finish.

The clean target will clear the `bin/` and `jar/` temporary directories as well as the `MANIFEST.MF` file
