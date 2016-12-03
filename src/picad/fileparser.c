#include "fileparser.h"

#include "../lcadengine/graphLoader.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

enum fileCommand {CMD_INPUT, CMD_OUTPUT, CMD_GRAPH};

struct lineDataset {
    enum fileCommand command;
    size_t gate_id;
	int phy_addr;
};

struct lineDataset readCMD(char* str){
    char *end_token;
	char *sstr = malloc(strlen(str)+1);
	strcpy(sstr, str);

    enum readstate {CMD, ID, PORT};
	enum readstate state = CMD;
	
    struct lineDataset data;	
	// Get next token
	char *token = strtok_r(str, " ", &end_token);
	while (token != NULL) {
	    // Swallow Comments
		if (token[0] == '#') break;
		switch(state) {
		case CMD:
		    if (!strcmp(token, "INPUT")) data.command = CMD_INPUT;
			if (!strcmp(token, "OUTPUT")) data.command = CMD_OUTPUT;
			if (!strcmp(token, "GRAPH")) data.command = CMD_GRAPH;
			state = ID;
			break;
		case ID:
		    data.gate_id = atol(token);
		    state = PORT;
			break;
		case PORT:
		    data.phy_addr = atol(token);
		    break;
		}
		token = strtok_r(NULL, " ", &end_token);
	}
	free(sstr);
	return data;
}

struct fileInfoDataset parseFile(char *filename) {
    printf("Loading from file: %s", filename);
    
	// Open File;
	FILE *fp;
	fp = fopen(filename, "r");

	char *str;
	size_t length;
	if (!fp) {
		printf("File: %s not found", filename);
		exit(0);
	}
	// Get length of file
	fseek(fp, 0, SEEK_END);
	length = ftell (fp);
	fseek(fp, 0, SEEK_SET);
	// Allocate buffer;
	str = malloc(length);
	if (!str) {
	  printf("Malloc Failed during file loading");
	  exit(0);
	}
	// Read into buffer;
	fread (str, 1, length, fp);
	fclose(fp);

	printf("File Contents: %s", str);
	//TODO: strip all '/r''s
    
    struct fileInfoDataset info;
    info.inputCount = 0;
    info.outputCount = 0;
    info.inputs = calloc(0,sizeof(IO_Item));
    info.outputs = calloc(0,sizeof(IO_Item));
        
    //split file into lines
    char *end_token;
    char *line = strtok_r(str, "\n", &end_token);
    
	while (line != NULL) {
		line = strtok_r(NULL, "\n", &end_token);
		// Read Line
		struct lineDataset set = readCMD(line);
		switch (set.command) {
		    case CMD_GRAPH:
		        info.g = loaderLoadFromStr(end_token);
		        free(str);	  
                return info;
		        break;
		    case CMD_INPUT:
		        info.inputs = realloc(info.inputs, sizeof(IO_Item*)*(info.inputCount + 1));
		        info.inputs[info.inputCount] = setupPin(set.phy_addr, IOM_IN); 
	            info.inputs[info.inputCount]->ID = set.gate_id;
	            info.inputCount++;
		        break;
		    case CMD_OUTPUT:
		        info.outputs = realloc(info.outputs, sizeof(IO_Item*)*(info.outputCount + 1));
		        info.outputs[info.outputCount] = setupPin(set.phy_addr, IOM_OUT);
	            info.outputs[info.outputCount]->ID = set.gate_id;
	            info.outputCount++;
		        break;
		}
	}

	return info;

};

void cleanFile(struct fileInfoDataset file){
	graphDelete(file.g);
	for (size_t i; i < file.inputCount; i++) {
	    cleanPin(file.inputs[i]);
	}
	free(file.inputs);
	for (size_t i; i < file.outputCount; i++) {
	    cleanPin(file.outputs[i]);
	}
	free(file.outputs);
}
