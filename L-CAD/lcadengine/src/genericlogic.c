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

#include "genericlogic.h"

bool logic_isState(genericLogicInterface *val) {
	return (bool)(val->state & VAL_FIELD);
}

bool logic_isUnknown(genericLogicInterface *val) {
	return (bool)(val->state & UNKNOWN_FIELD);
}

bool logic_isDontCare(genericLogicInterface *val) {
	return (bool)(val->state & DTCARE_FIELD);
}

