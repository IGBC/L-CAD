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

#ifndef LOGICGATE_H
#define LOGICGATE_H

typedef enum {AND, OR, XOR, UNITY, INPUT, OUTPUT} gateInputType;


#define VAL_FIELD 0b00000001
#define UNKNOWN_FIELD 0b00000010
#define DTCARE_FIELD 0b00000100

typedef enum {FALSE=0b00000000, TRUE=0b00000001, DTKNOW=0b00000010, DTCARE=0b00000110} logicType;

struct {
	size_t ID; /* Sequential ID of Gate */
	logicType state; /* Current Output state for this GLI */
	unsigned int delay; /* Propagation delay of this gate */
	gateInputType inputMode; /* AND OR etc.... */
	bool inputNegate; /* N in front of the mode */

	// Dispatcher Fields
	bool *lockTag; /* Stores the location of this gate's work locks
	  Memory for the locks must be provided by the dispatcher at creation,
	  if the dispatcher is not in scope this variable is not valid.*/
	bool seen = 0; /* Used in recursive functions to detect if we've seen this
	function MUST MUST MUST reset this to 0 once on returning down the stack. */
} typedef genericLogicInterface;

struct {
	size_t ID; /* ID of this connection */
	genericLogicInterface *srcEp; /* Pointer to the GLI of the source */
	genericLogicInterface *drnEp; /* Pointer to the GLI of the drain */
	size_t srcID; /* ID of the source */
	size_t drnID; /* ID of the drain */
} typedef connection;

bool logic_isState(genericLogicInterface *val) {
	return (bool)(val->state & VAL_FIELD);
}

bool logic_isUnknown(genericLogicInterface *val) {
	return (bool)(val->state & UNKNOWN_FIELD);
}

bool logic_isDontCare(genericLogicInterface *val) {
	return (bool)(val->state & DTCARE_FIELD);
}

#endif
