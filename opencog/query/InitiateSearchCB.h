/*
 * InitiateSearchCB.h
 *
 * Copyright (C) 2015 Linas Vepstas <linasvepstas@gmail.com>
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
 *
 * Created by Linas Vepstas April 2015
 */

#ifndef _OPENCOG_INITIATE_SEARCH_H
#define _OPENCOG_INITIATE_SEARCH_H

#include <opencog/util/empty_string.h>
#include <opencog/atoms/atom_types/types.h>
#include <opencog/atoms/core/Quotation.h>
#include <opencog/atoms/pattern/PatternLink.h>
#include <opencog/query/PatternMatchCallback.h>

namespace opencog {

class AtomSpace;

/**
 * Callback mixin class, used to provide a default atomspace search.
 * This class is a pure virtual class, it does not implement any
 * of the matching callbacks.
 *
 * The *only* thing it provides is search initiation.
 */
class InitiateSearchCB : public virtual PatternMatchCallback
{
public:
	InitiateSearchCB(AtomSpace*);

	/**
	 * Called to perform the actual search. This makes some default
	 * assumptions about the kind of things that might be matched,
	 * in order to drive a reasonably-fast search.
	 */
	virtual void set_pattern(const Variables&, const Pattern&);
	virtual bool initiate_search(PatternMatchCallback&);

	std::string to_string(const std::string& indent=empty_string) const;

protected:

	NameServer& _nameserver;

	const Variables* _variables;
	const Pattern* _pattern;
	const HandleSet* _dynamic;

	PatternLinkPtr _pl;
	void jit_analyze(void);

	Handle _root;
	Handle _starter_term;
	HandleSeq _search_set;

	struct Choice
	{
		Handle clause;
		Handle best_start;
		Handle start_term;
	};
	Handle _curr_clause;
	std::vector<Choice> _choices;

	virtual Handle find_starter(const Handle&, size_t&, Handle&, size_t&);
	virtual Handle find_starter_recursive(const Handle&, size_t&, Handle&,
	                                      size_t&);
	virtual Handle find_thinnest(const HandleSeq&,
	                             const HandleSet&,
	                             Handle&, Handle&);
	virtual void find_rarest(const Handle&, Handle&, size_t&,
	                         Quotation quotation=Quotation());

	bool setup_neighbor_search(void);
	bool setup_no_search(void);
	bool setup_link_type_search(void);
	bool setup_variable_search(void);

	bool choice_loop(PatternMatchCallback&, const std::string);
	bool search_loop(PatternMatchCallback&, const std::string);
	AtomSpace *_as;
};

// Primaliry for gdb debugging, see
// https://wiki.opencog.org/w/Development_standards#Pretty_Print_OpenCog_Objects
std::string oc_to_string(const InitiateSearchCB& iscb,
                         const std::string& indent=empty_string);

} // namespace opencog

#endif // _OPENCOG_INITIATE_SEARCH_H
