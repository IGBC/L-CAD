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

struct {
	size_t ID; /* Sequential ID of Gate */
	bool state; /* Current Output state for this GLI */
	unsigned int delay; /* Propagation delay of this gate */
	gateInputType inputMode; /* AND OR etc.... */
	bool inputNegate; /* N in front of the mode */

	// Dispatcher Fields
	bool *lockTag; /* stores the location of this gate's work locks
	  Memory for the locks must be provided by the dispatcher at creation,
	  if the dispatcher is not in scope this variable is not valid.*/
} typedef genericLogicInterface;

struct {
	size_t ID; /* ID of this connection */
	genericLogicInterface *srcEp; /* pointer to the GLI of the source */
	genericLogicInterface *drnEp; /* pointer to the GLI of the drain */
	size_t srcID; /* ID of the source */
	size_t drnID; /* ID of the drain */
} typedef connection;

#endif
