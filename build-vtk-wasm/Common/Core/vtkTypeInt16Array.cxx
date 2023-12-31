/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkTypedArray.cxx.in

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkTypeInt16Array.h"

#include "vtkObjectFactory.h"

//----------------------------------------------------------------------------
VTK_ABI_NAMESPACE_BEGIN
vtkStandardNewMacro(vtkTypeInt16Array);

//----------------------------------------------------------------------------
vtkTypeInt16Array::vtkTypeInt16Array() = default;

//----------------------------------------------------------------------------
vtkTypeInt16Array::~vtkTypeInt16Array() = default;

//----------------------------------------------------------------------------
void vtkTypeInt16Array::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os,indent);
}
VTK_ABI_NAMESPACE_END
