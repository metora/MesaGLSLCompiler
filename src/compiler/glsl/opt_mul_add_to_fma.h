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

#ifndef OPT_MUL_ADD_TO_FMA_H
#define OPT_MUL_ADD_TO_FMA_H

#include "ir.h"
#include "ir_hierarchical_visitor.h"

class mul_add_to_fma_visitor : public ir_hierarchical_visitor {
public:
   mul_add_to_fma_visitor()
   {
      /* empty */
   }

   ir_visitor_status visit_leave(ir_expression *ir)
   {
      if (ir->operation != ir_binop_add)
         return visit_continue;

      ir_expression const *op0 = ir->operands[0]->as_expression();
      if (op0 != NULL && op0->operation == ir_binop_mul) {
         ir->operation = ir_triop_fma;
         ir->operands[2] = ir->operands[1];
         ir->operands[1] = op0->operands[1];
         ir->operands[0] = op0->operands[0];
         return visit_continue;
      }

      ir_expression const *op1 = ir->operands[1]->as_expression();
      if (op1 != NULL && op1->operation == ir_binop_mul) {
         ir->operation = ir_triop_fma;
         ir->operands[2] = ir->operands[0];
         ir->operands[1] = op1->operands[1];
         ir->operands[0] = op1->operands[0];
         return visit_continue;
      }

      return visit_continue;
   }
};

#endif /* OPT_MUL_ADD_TO_FMA_H */
