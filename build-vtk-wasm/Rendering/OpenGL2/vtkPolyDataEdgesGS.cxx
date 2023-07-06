#include "vtkPolyDataEdgesGS.h"

const char *vtkPolyDataEdgesGS =
"//VTK::System::Dec\n"
"\n"
"/*=========================================================================\n"
"\n"
"  Program:   Visualization Toolkit\n"
"\n"
"  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen\n"
"  All rights reserved.\n"
"  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.\n"
"\n"
"     This software is distributed WITHOUT ANY WARRANTY; without even\n"
"     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR\n"
"     PURPOSE.  See the above copyright notice for more information.\n"
"\n"
"=========================================================================*/\n"
"// Template for the polydata mappers geometry shader\n"
"\n"
"uniform int PrimitiveIDOffset;\n"
"\n"
"// VC position of this fragment\n"
"//VTK::PositionVC::Dec\n"
"\n"
"// primitiveID\n"
"//VTK::PrimID::Dec\n"
"\n"
"// optional color passed in from the vertex shader, vertexColor\n"
"//VTK::Color::Dec\n"
"\n"
"// optional surface normal declaration\n"
"//VTK::Normal::Dec\n"
"\n"
"// extra lighting parameters\n"
"//VTK::Light::Dec\n"
"\n"
"// Texture coordinates\n"
"//VTK::TCoord::Dec\n"
"\n"
"// picking support\n"
"//VTK::Picking::Dec\n"
"\n"
"// Depth Peeling Support\n"
"//VTK::DepthPeeling::Dec\n"
"\n"
"// clipping plane vars\n"
"//VTK::Clip::Dec\n"
"\n"
"// the output of this shader\n"
"//VTK::Output::Dec\n"
"\n"
"layout(triangles) in;\n"
"layout(triangle_strip, max_vertices = 3) out;\n"
"\n"
"uniform vec4 vpDims;\n"
"out vec4 edgeEqn[3];\n"
"uniform float lineWidth;\n"
"\n"
"//VTK::Edges::Dec\n"
"\n"
"void main()\n"
"{\n"
"  //VTK::Normal::Start\n"
"\n"
"  vec2 pos[4];\n"
"\n"
"  for (int i = 0; i < 3; i++)\n"
"  {\n"
"    pos[i] = gl_in[i].gl_Position.xy/gl_in[i].gl_Position.w;\n"
"    pos[i] = pos[i]*vec2(0.5) + vec2(0.5);\n"
"    pos[i] = pos[i]*vpDims.zw + vpDims.xy;\n"
"  }\n"
"  pos[3] = pos[0];\n"
"\n"
"  float ccw = sign(cross(vec3(pos[1] - pos[0], 0.0), vec3(pos[2] - pos[0], 0.0)).z);\n"
"\n"
"  for (int i = 0; i < 3; i++)\n"
"  {\n"
"    vec2 tmp = normalize(pos[i+1] - pos[i]);\n"
"    tmp = ccw*vec2(-tmp.y, tmp.x);\n"
"    float d = dot(pos[i], tmp);\n"
"    edgeEqn[i] = vec4(tmp.x, tmp.y, 0.0, -d);\n"
"  }\n"
"\n"
"  vec2 offsets[3];\n"
"\n"
"  offsets[0] = edgeEqn[2].xy + edgeEqn[0].xy;\n"
"  offsets[0] = -0.5*normalize(offsets[0])*lineWidth;\n"
"  offsets[0] /= vpDims.zw;\n"
"\n"
"  offsets[1] = edgeEqn[0].xy + edgeEqn[1].xy;\n"
"  offsets[1] = -0.5*normalize(offsets[1])*lineWidth;\n"
"  offsets[1] /= vpDims.zw;\n"
"\n"
"  offsets[2] = edgeEqn[1].xy + edgeEqn[2].xy;\n"
"  offsets[2] = -0.5*normalize(offsets[2])*lineWidth;\n"
"  offsets[2] /= vpDims.zw;\n"
"\n"
"  //VTK::Edges::Impl\n"
"\n"
"  for (int i = 0; i < 3; i++)\n"
"    {\n"
"    //VTK::PrimID::Impl\n"
"\n"
"    //VTK::Clip::Impl\n"
"\n"
"    //VTK::Color::Impl\n"
"\n"
"    //VTK::Normal::Impl\n"
"\n"
"    //VTK::Light::Impl\n"
"\n"
"    //VTK::TCoord::Impl\n"
"\n"
"    //VTK::DepthPeeling::Impl\n"
"\n"
"    //VTK::Picking::Impl\n"
"\n"
"    // VC position of this fragment\n"
"    //VTK::PositionVC::Impl\n"
"\n"
"    // gl_Position = gl_in[i].gl_Position;\n"
"\n"
"    gl_Position = gl_in[i].gl_Position;\n"
"    gl_Position.xy = gl_Position.xy + offsets[i]*gl_Position.w;\n"
"\n"
"    EmitVertex();\n"
"    }\n"
"  EndPrimitive();\n"
"}\n"
"";