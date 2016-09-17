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


#include "graphLoader.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct {
	unsigned long src;
	unsigned long drn;
} connRecord;

void readGate(graph *ctx, char* str, connRecord *rec, int *i) {
	char *end_token;
	char sstr[1000];
	strcpy(sstr, str);

	enum readstate {id, gt, input};
	enum readstate state = id;

	unsigned long ID;
	gateInputType inputMode;
	bool nin;

	//get next token
	char *token = strtok_r(str, " ", &end_token);
	while (token != NULL) {
		printf("token: %s\n", token);

		if (token[0] == '#') break;
		char *loc;
		switch(state) {
		case id:
			ID = atol(token);
			state = gt;
			break;
		case gt:
			loc = token;
			if (loc[0] == '!' || loc[0] == 'N') {
				nin = true;
				loc++;
			}
			if (!strcmp(loc, "AND")) inputMode = AND;
			if (!strcmp(loc, "OR")) inputMode = OR;
			if (!strcmp(loc, "XOR")) inputMode = XOR;
			if (!strcmp(loc, "BUF")) inputMode = UNITY;
			if (!strcmp(loc, "OT")) inputMode = UNITY;
			if (!strcmp(loc, "IN")) inputMode = INPUT;
			if (!strcmp(loc, "OUT")) inputMode = OUTPUT;
			state = input;
			break;
		case input:
			rec[*i].src = atol(token);
			rec[*i].drn = ID;
			*i += 1;
			break;
		}
		token = strtok_r(NULL, " ", &end_token);
	}
	//todo verify data;
	graphAddGLI(ctx, inputMode, nin, ID, 0);
};

graph *loaderLoad(char *str){
	// Create a graph if this fails then give up
	char * end_token;
	char sstr[1000*1000];
	strcpy(sstr, str);
	connRecord records[1000];
	memset(records, 0, sizeof(records));
	int rec = 0;

	graph *ctx = graphCreate();
	if (!ctx) return NULL;

	char *line = strtok_r(sstr, "\n", &end_token);
	while (line != NULL)
	{
		printf("line: %s\n", line);
		readGate(ctx, line, (connRecord*) records, &rec);
		line = strtok_r(NULL, "\n", &end_token);
	}

	printf("rec: %i\n", rec);

	for (int i=rec-1; i>=0; i--){
		graphAddConnection(ctx, records[i].src, records[i].drn);
	}

	return ctx;
}
