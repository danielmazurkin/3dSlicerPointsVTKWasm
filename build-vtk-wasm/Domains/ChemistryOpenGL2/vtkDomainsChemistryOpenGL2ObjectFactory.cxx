/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkDomainsChemistryOpenGL2ObjectFactory.cxx

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

// Object factories should never have deprecation warnings.
// NOLINTNEXTLINE(modernize-macro-to-enum)
#define VTK_DEPRECATION_LEVEL 0

#include "vtkDomainsChemistryOpenGL2ObjectFactory.h"
#include "vtkVersion.h"

// Include all of the classes we want to create overrides for.
#include "vtkOpenGLMoleculeMapper.h"


VTK_ABI_NAMESPACE_BEGIN

vtkStandardNewMacro(vtkDomainsChemistryOpenGL2ObjectFactory);

// Now create the functions to create overrides with.
VTK_CREATE_CREATE_FUNCTION(vtkOpenGLMoleculeMapper)


vtkDomainsChemistryOpenGL2ObjectFactory::vtkDomainsChemistryOpenGL2ObjectFactory()
{
this->RegisterOverride("vtkMoleculeMapper", "vtkOpenGLMoleculeMapper", "Override for VTK::DomainsChemistryOpenGL2 module", 1, vtkObjectFactoryCreatevtkOpenGLMoleculeMapper);

}

const char * vtkDomainsChemistryOpenGL2ObjectFactory::GetVTKSourceVersion()
{
  return VTK_SOURCE_VERSION;
}

void vtkDomainsChemistryOpenGL2ObjectFactory::PrintSelf(ostream &os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);
}

// Registration of object factories.
static unsigned int vtkDomainsChemistryOpenGL2Count = 0;

VTKDOMAINSCHEMISTRYOPENGL2_EXPORT void vtkDomainsChemistryOpenGL2_AutoInit_Construct()
{
  if(++vtkDomainsChemistryOpenGL2Count == 1)
  {


    vtkDomainsChemistryOpenGL2ObjectFactory* factory = vtkDomainsChemistryOpenGL2ObjectFactory::New();
    if (factory)
    {
      // vtkObjectFactory keeps a reference to the "factory",
      vtkObjectFactory::RegisterFactory(factory);
      factory->Delete();
    }
  }
}
VTK_ABI_NAMESPACE_END
