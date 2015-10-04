/*
 * opencog/atomspace/FloatValue.cc
 *
 * Copyright (C) 2015 Linas Vepstas
 * All Rights Reserved
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License v3 as
 * published by the Free Software Foundation and including the exceptions
 * at http://opencog.org/wiki/Licenses
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program; if not, write to:
 * Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include <opencog/atomspace/FloatValue.h>

using namespace opencog;

bool FloatValue::operator==(const ProtoAtom& other) const
{
	if (FLOAT_VALUE != other.getType()) return false;
	return true;
}

// ==============================================================
// Whole lotta truthiness going on here.  Does it really need to be
// this complicated!?

std::string FloatValue::toString(std::string indent)
{
	return indent + std::to_string(_value);
}
