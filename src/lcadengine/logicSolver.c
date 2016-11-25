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

#include "logicSolver.h"

bool solver_sumComparitor(genericLogicInterface *unit, size_t sum, size_t inputCount) {
	bool output = false;
	switch (unit->inputMode) {
		case AND:   if (sum == inputCount) output = true; break;
		case UNITY: // Behaves like a 1 input OR
		case OUTPUT: // Behaves like a 1 input OR
		case OR:    if (sum > 0)      output = true; break;
		case XOR:   if (sum == 1)     output = true; break;
		case INPUT: output = unit->state; break;
		default: break;
	}
	if (unit->inputNegate) output = !output;
	return output;
}
