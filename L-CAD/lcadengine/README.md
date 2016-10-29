LibLCADEngine
-------------
This folder contains the L-CAD Engine Library.

 - `./include`: Library headers
 - `./include-private`: Headers used inside the library
 - `./src`: Library source code
 - `./tests`: Hah! Right?

### Dev Notes / Ideas
Notes on the initilisation problem: a multistate logic could be benefitial here, as a YES/NO/DON'T_KNOW would allow a secondary analiyis of DON'T_KNOW conditions, to detirmine _a_ sane start configuration. This would require a rewrite of most of the engine however as it is all written with more traditional boolean types. An enum would be needed. 

There was some other stuff about initialisation but I didn't write it down. I think this one came down to a graph colouring problem. More on that as I remeber it.


