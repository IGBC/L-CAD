Challenging
-------------
This folder contains the L-CAD Engine Library.

 - `./include`: Library headers
 - `./include-private`: Headers used inside the library
 - `./src`: Library source code
 - `./tests`: Hah! Right?

### Dev Notes / Ideas
#### Notes on the initialisation problem: 
Rough problem description:
Initially all logic gates in the graph are initialised with a state of 0. in a purely combinational graph this is not a problem, as any logical contradictions. In graph loops these logical contradictions are fed back into the graph so cannot be cleared by simply stepping the simulation into a sane state. The most obvious of these loop bugs has been dubbed the "latch bug" where a NAND or NOR latch will oscillate between 0,0 and 1,1 states, both of which are logical contradictions. These contradictions cannot be cleared by the engine, as the simulation cannot currently detect the contradiction, or act "intelligently" to clear it. Instead it just dumbly updates both of the gates in the latch, based on their current state, propagating the contradiction between two theoretically possible, but wholly useless states.

 - A multi-state logic could be beneficial here, as a YES/NO/DON'T_KNOW would allow a secondary analysis of DON'T_KNOW conditions, to determine _a_ sane start configuration. This would require a rewrite of most of the engine however as it is all written with more traditional Boolean types. An enum would be needed. Slower? -- Thanks to LUX
 
 - Graph initialisation could also be performed using a graph colouring algorithm. One theory is to compile a new graph where nodes contain sections of the original graph and vertices present negations in the graph. By attempting to colour the graph with only two colours (I like to imagine them yellow and white) if successful you would theoretically have a stable solution. -- Solution suggestion by Fuzzel. This of course is not a rigorous proof. It could be closer to one, with only one corner case (that I can see), if you beforehand transformed the graph into only OR and NOT gates, but this 'solution' would be hard to map back to the original graph for simulation.

 - Loop detection algorithms could be employed to find all of the cycles in the graph and determine their order. The order is determined by the number of logical negations in the graph. In cases where the order is odd it must be accepted that the graph cannot under all conditions be stable, as a logical contradiction must exist, these graphs should continue to function unmodified, as their hazards are correctly simulated by the existing engine. Even ordered graphs could be coloured using graph colouring. 

