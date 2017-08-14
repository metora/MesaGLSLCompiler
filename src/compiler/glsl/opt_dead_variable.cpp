/*
 * Copyright © 2016 Intel Corporation
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

/**
 * \file opt_dead_variable.cpp
 *
 * Eliminates unused variables.
 */

#include "util/string_to_uint_map.h"
#include "util/set.h"
#include "ir.h"

namespace {

class dead_variable_visitor : public ir_hierarchical_visitor {
public:
   dead_variable_visitor()
   {
      variables = _mesa_set_create(NULL,
                                   _mesa_hash_pointer,
                                   _mesa_key_pointer_equal);
   }

   virtual ~dead_variable_visitor()
   {
      _mesa_set_destroy(variables, NULL);
   }

   virtual ir_visitor_status visit(ir_variable *ir)
   {
      /* If the variable is auto or temp, add it to the set of variables that
       * are candidates for removal.
       */
      if (ir->data.mode != ir_var_auto && ir->data.mode != ir_var_temporary)
         return visit_continue;

      _mesa_set_add(variables, ir);

      return visit_continue;
   }

   virtual ir_visitor_status visit(ir_dereference_variable *ir)
   {
      struct set_entry *entry = _mesa_set_search(variables, ir->var);

      /* If a variable is dereferenced at all, remove it from the set of
       * variables that are candidates for removal.
       */
      if (entry != NULL)
         _mesa_set_remove(variables, entry);

      return visit_continue;
   }

   void remove_dead_variables()
   {
      struct set_entry *entry;

      set_foreach(variables, entry) {
         ir_variable *ir = (ir_variable *) entry->key;

         assert(ir->ir_type == ir_type_variable);
         ir->remove();
      }
   }

private:
   set *variables;
};

} /* unnamed namespace */

bool
do_dead_variables(exec_list *instructions)
{
   dead_variable_visitor v;
   visit_list_elements(&v, instructions);
   v.remove_dead_variables();
   return true;
}
