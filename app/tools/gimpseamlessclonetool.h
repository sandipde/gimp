/* GIMP - The GNU Image Manipulation Program
 *
 * gimpseamlessclonetool.h
 * Copyright (C) 2011 Barak Itkin <lightningismyname@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __GIMP_SEAMLESS_CLONE_TOOL_H__
#define __GIMP_SEAMLESS_CLONE_TOOL_H__


#include "gimpdrawtool.h"


#define GIMP_TYPE_SEAMLESS_CLONE_TOOL            (gimp_seamless_clone_tool_get_type ())
#define GIMP_SEAMLESS_CLONE_TOOL(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_SEAMLESS_CLONE_TOOL, GimpSeamlessCloneTool))
#define GIMP_SEAMLESS_CLONE_TOOL_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_SEAMLESS_CLONE_TOOL, GimpSeamlessCloneToolClass))
#define GIMP_IS_SEAMLESS_CLONE_TOOL(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_SEAMLESS_CLONE_TOOL))
#define GIMP_IS_SEAMLESS_CLONE_TOOL_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_SEAMLESS_CLONE_TOOL))
#define GIMP_SEAMLESS_CLONE_TOOL_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_SEAMLESS_CLONE_TOOL, GimpSeamlessCloneToolClass))

#define GIMP_SEAMLESS_CLONE_TOOL_GET_OPTIONS(t)  (GIMP_SEAMLESS_CLONE_OPTIONS (gimp_tool_get_options (GIMP_TOOL (t))))


typedef struct _GimpSeamlessCloneTool      GimpSeamlessCloneTool;
typedef struct _GimpSeamlessCloneToolClass GimpSeamlessCloneToolClass;

struct _GimpSeamlessCloneTool
{
  GimpDrawTool    parent_instance;

  GeglBuffer     *paste;         /* A buffer containing the original
                                  * paste that will be used in the
                                  * rendering process */

  GeglBuffer     *tricache;      /* Gegl buffer where each pixel contains
                                  * information to associate it with a
                                  * triangle of the mesh */
                                  
  gpointer        mesh_cache;    /* The interpolation mesh, and sampling
                                  * lists - an abstract data structure
                                  * returned by the preprocessing GEGL
                                  * operation */

  GeglNode       *render_node;    /* The parent of the Gegl graph that
                                   * renders the seamless cloning */
                                   
  GeglNode       *translate_node; /* A Gegl node to translate the paste
                                   * when the user moves it */

  gint            tool_state;     /* The current state in the tool's
                                   * state machine */

  GimpImageMap   *image_map;      /* The image map object which renders
                                   * the live preview, and commits it
                                   * when at the end */
};

struct _GimpSeamlessCloneToolClass
{
  GimpDrawToolClass parent_class;
};


void    gimp_seamless_clone_tool_register (GimpToolRegisterCallback  callback,
                                           gpointer                  data);

GType   gimp_seamless_clone_tool_get_type (void) G_GNUC_CONST;


#endif  /*  __GIMP_SEAMLESS_CLONE_TOOL_H__  */