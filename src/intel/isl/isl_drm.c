/*
 * Copyright 2017 Intel Corporation
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a
 *  copy of this software and associated documentation files (the "Software"),
 *  to deal in the Software without restriction, including without limitation
 *  the rights to use, copy, modify, merge, publish, distribute, sublicense,
 *  and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice (including the next
 *  paragraph) shall be included in all copies or substantial portions of the
 *  Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 *  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 *  IN THE SOFTWARE.
 */

#include <assert.h>
#include <stdlib.h>

#include <drm_fourcc.h>

#include "isl.h"
#include "common/gen_device_info.h"

struct isl_drm_modifier_info modifier_info[] = {
   {
      .modifier = DRM_FORMAT_MOD_NONE,
      .name = "DRM_FORMAT_MOD_NONE",
      .tiling = ISL_TILING_LINEAR,
   },
   {
      .modifier = I915_FORMAT_MOD_X_TILED,
      .name = "I915_FORMAT_MOD_X_TILED",
      .tiling = ISL_TILING_X,
   },
   {
      .modifier = I915_FORMAT_MOD_Y_TILED,
      .name = "I915_FORMAT_MOD_Y_TILED",
      .tiling = ISL_TILING_Y0,
   },
};

const struct isl_drm_modifier_info *
isl_drm_modifier_get_info(uint64_t modifier)
{
   for (unsigned i = 0; i < ARRAY_SIZE(modifier_info); i++) {
      if (modifier_info[i].modifier == modifier)
         return &modifier_info[i];
   }

   return NULL;
}