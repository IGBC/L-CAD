/*
 * This file is part of the L-CAD project
 * Copyright (c) 2016  Ashley Brown, Katharina Sabel
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 * 
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see http://www.gnu.org/licenses/.
 */


#include <stdio.h>
#include "dispatcher.h"
#include "graphLoader.h"
#include "logicGraph.h"
#define LOGMODULE "MAIN"
#include "utils/lcadLogger.h"

void simulate_adder() {
    graph *g = graphCreate();

    unsigned long a = graphAddGLI(g, INPUT, true, 101, 0);
    unsigned long b = graphAddGLI(g, INPUT, false, 102,  0);
    unsigned long c = graphAddGLI(g, INPUT, false, 103, 0);

    unsigned long xor1 = graphAddGLI(g, XOR, false, 4, 0);
    unsigned long andAB = graphAddGLI(g, AND, false, 5, 0);
    unsigned long and1C = graphAddGLI(g, AND, false, 6, 0);

    unsigned long out = graphAddGLI(g, XOR, false, 7, 0);
    unsigned long cOut = graphAddGLI(g, OR, false, 8, 0);

    unsigned long OUT = graphAddGLI(g, OUTPUT, false, 200, 0);
    unsigned long COUT = graphAddGLI(g, OUTPUT, false, 201, 0);

    /* Setup connections */
    graphAddConnection(g, a, xor1);
    graphAddConnection(g, b, xor1);

    graphAddConnection(g, xor1, out);
    graphAddConnection(g, c, out);

    graphAddConnection(g, xor1, and1C);
    graphAddConnection(g, c, and1C);

    graphAddConnection(g, a, andAB);
    graphAddConnection(g, b, andAB);

    graphAddConnection(g, andAB, cOut);
    graphAddConnection(g, and1C, cOut);

    graphAddConnection(g, out, OUT);
    graphAddConnection(g, cOut, COUT);

    dispatcher *d = dispatcherCreate(g, 4);

    graphGetGLI(g, a)->state = true;
    graphGetGLI(g, b)->state = true;
    graphGetGLI(g, c)->state = true;

    dispatcherAddJob(d, a, 1);
    dispatcherAddJob(d, b, 1);
    dispatcherAddJob(d, c, 1);

    for (int i = 0; i < 10; i++) {
        graphPrint(g);
    	dispatcherStep(d);
    }

    dispatcherDelete(d);
    graphDelete(g);
}


void calculate_truth_table(gateInputType t, bool n) {
    graph *g = graphCreate();
    unsigned long in1 = graphAddGLI(g, UNITY, false, 101, 0);
    unsigned long in2 = graphAddGLI(g, UNITY, false, 102, 0);
    unsigned long in3 = graphAddGLI(g, UNITY, false, 103, 0);
    unsigned long ID = graphAddGLI(g, t, n, 1, 0);
    graphAddConnection(g, in1, ID);
    graphAddConnection(g, in2, ID);
    graphAddConnection(g, in3, ID);
    graphGetGLI(g, ID)->state = true;
    dispatcher *d = dispatcherCreate(g, 4);
    //printf("output values are: %i, %i, %i\n",(int *) graphGetGLI(g, in1)->state, (int *) graphGetGLI(g, in2)->state, (int *) graphGetGLI(g, ID)->state);

    graphGetGLI(g, in1)->state = false;
    graphGetGLI(g, in2)->state = false;
    graphGetGLI(g, in3)->state = false;
    dispatcherAddJob(d, ID, 1);
    dispatcherStep(d);
    printf("output values are: %i, %i, %i = %i\n",(int *) graphGetGLI(g, in1)->state, (int *) graphGetGLI(g, in2)->state, (int *) graphGetGLI(g, in3)->state, (int *) graphGetGLI(g, ID)->state);

    graphGetGLI(g, in1)->state = false;
    graphGetGLI(g, in2)->state = false;
    graphGetGLI(g, in3)->state = true;
    dispatcherAddJob(d, ID, 1);
    dispatcherStep(d);
    printf("output values are: %i, %i, %i = %i\n",(int *) graphGetGLI(g, in1)->state, (int *) graphGetGLI(g, in2)->state, (int *) graphGetGLI(g, in3)->state, (int *) graphGetGLI(g, ID)->state);



    graphGetGLI(g, in1)->state = false;
    graphGetGLI(g, in2)->state = true;
    graphGetGLI(g, in3)->state = false;
    dispatcherAddJob(d, ID, 1);
    dispatcherStep(d);
    printf("output values are: %i, %i, %i = %i\n",(int *) graphGetGLI(g, in1)->state, (int *) graphGetGLI(g, in2)->state, (int *) graphGetGLI(g, in3)->state, (int *) graphGetGLI(g, ID)->state);



    graphGetGLI(g, in1)->state = false;
    graphGetGLI(g, in2)->state = true;
    graphGetGLI(g, in3)->state = true;
    dispatcherAddJob(d, ID, 1);
    dispatcherStep(d);
    printf("output values are: %i, %i, %i = %i\n",(int *) graphGetGLI(g, in1)->state, (int *) graphGetGLI(g, in2)->state, (int *) graphGetGLI(g, in3)->state, (int *) graphGetGLI(g, ID)->state);



    graphGetGLI(g, in1)->state = true;
    graphGetGLI(g, in2)->state = false;
    graphGetGLI(g, in3)->state = false;
    dispatcherAddJob(d, ID, 1);
    dispatcherStep(d);
    printf("output values are: %i, %i, %i = %i\n",(int *) graphGetGLI(g, in1)->state, (int *) graphGetGLI(g, in2)->state, (int *) graphGetGLI(g, in3)->state, (int *) graphGetGLI(g, ID)->state);



    graphGetGLI(g, in1)->state = true;
    graphGetGLI(g, in2)->state = false;
    graphGetGLI(g, in3)->state = true;
    dispatcherAddJob(d, ID, 1);
    dispatcherStep(d);
    printf("output values are: %i, %i, %i = %i\n",(int *) graphGetGLI(g, in1)->state, (int *) graphGetGLI(g, in2)->state, (int *) graphGetGLI(g, in3)->state, (int *) graphGetGLI(g, ID)->state);



    graphGetGLI(g, in1)->state = true;
    graphGetGLI(g, in2)->state = true;
    graphGetGLI(g, in3)->state = false;
    dispatcherAddJob(d, ID, 1);
    dispatcherStep(d);
    printf("output values are: %i, %i, %i = %i\n",(int *) graphGetGLI(g, in1)->state, (int *) graphGetGLI(g, in2)->state, (int *) graphGetGLI(g, in3)->state, (int *) graphGetGLI(g, ID)->state);



    graphGetGLI(g, in1)->state = true;
    graphGetGLI(g, in2)->state = true;
    graphGetGLI(g, in3)->state = true;
    dispatcherAddJob(d, ID, 1);
    dispatcherStep(d);
    printf("output values are: %i, %i, %i = %i\n",(int *) graphGetGLI(g, in1)->state, (int *) graphGetGLI(g, in2)->state, (int *) graphGetGLI(g, in3)->state, (int *) graphGetGLI(g, ID)->state);

    dispatcherDelete(d);
    graphDelete(g);
}


int main() {
	LOG(FATAL, "I crashed");
	LOG(CRITICAL, "I'm about to crash");
	LOG(ERROR, "I might Crash");
	LOG(WARNING, "HUH that's odd");
	LOG(INFO1, "STATE1");
	LOG(INFO2, "STATE2");
	LOG(INFO3, "STATE3");
	LOG(TRACE, "I think he went through here");
	LOG(DEBUG, "I = 3")
	return 0;
    printf("+= Sizeof =+\n| char:  %i |\n| short: %i |\n| int:   %i |\n| long:  %i |\n| void*: %i |\n+----------+\n",sizeof(char), sizeof(short), sizeof(int), sizeof(long), sizeof(void*)); 
   // simulate_adder();
    
//    printf("\n\n=== AND ===\n");
//    calculate_truth_table(AND, false);
//
//    printf("\n\n=== NAND ===\n");
//    calculate_truth_table(AND, true);
//
//    printf("\n\n=== OR ===\n");
//    calculate_truth_table(OR, false);
//
//    printf("\n\n=== NOR ===\n");
//    calculate_truth_table(OR, true);
//
//    printf("\n\n=== XOR ===\n");
//    calculate_truth_table(XOR, false);
//
//    printf("\n\n=== NXOR ===\n");
//    calculate_truth_table(XOR, true);

    graph *g = loaderLoad(//"0 NOT 0\n 1 NAND 0 1\n 2 IN");
"0 IN \n \
#100 NOT 0 \n \
#1 OUT 14 #Q1\n \
#2 OUT 24 #Q2\n \
#3 OUT 34 #Q2\n \
#4 OUT 44 #Q4\n \
\n \
1 NAND 7 0\n \
2 NOT 7\n \
3 NAND 2 0\n \
4 NOR 1 5 #Q\n \
5 NOR 3 4 #!Q\n \
6 OUT 4\n \
7 IN #D\n \
#21 NAND 25 0\n \
#22 NOT 25\n \
#23 NAND 22 0\n \
#24 NAND 21 25 #Q\n \
#25 NAND 23 24 #!Q\n \
\n \
#31 NAND 35 0\n \
#32 NOT 35\n \
#33 NAND 32 0\n \
#34 NAND 31 35 #Q\n \
#35 NAND 33 34 #!Q\n \
\n \
#41 NAND 45 0\n \
#42 NOT 45\n \
#43 NAND 42 0\n \
#44 NAND 41 45 #Q\n \
#45 NAND 43 44 #!Q");

    dispatcher *d = dispatcherCreate(g, 1);

    for(int j = 0; j < graphGetNodeCount(g); j++) {
    	dispatcherAddJob(d, j, 1);
    }

    for(int j = 0; j < 10; j++) {
    	//printf(" %i,", j);
    	dispatcherStep(d);
    }

    graphPrint(g);

	graphGetGLI(g, 0)->state = 1;
	dispatcherAddJob(d, 0, 1);
	graphGetGLI(g, 7)->state = 1;
	dispatcherAddJob(d, 7, 1);

	for(int i = 0; i < 10; i++) {
		dispatcherStep(d);
		printf("\n");
		graphPrint(g);
	}

	graphGetGLI(g, 0)->state = 0;
	dispatcherAddJob(d, 0, 1);

	for(int i = 0; i < 10; i++) {
			dispatcherStep(d);
			printf("\n");
			graphPrint(g);
		}
	    
	//graphDelete(g);

    return 0;    
}
