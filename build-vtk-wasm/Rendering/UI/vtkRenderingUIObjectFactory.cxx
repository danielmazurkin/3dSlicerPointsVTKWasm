/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkRenderingUIObjectFactory.cxx

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

#include "vtkRenderingUIObjectFactory.h"
#include "vtkVersion.h"

// Include all of the classes we want to create overrides for.
#include <vtkCollection.h>
#include <vtkObjectFactoryCollection.h>
#include <vtkLogger.h>
#include <cstdlib>
#include "vtkGenericRenderWindowInteractor.h"
#include "vtkSDL2RenderWindowInteractor.h"


VTK_ABI_NAMESPACE_BEGIN

vtkStandardNewMacro(vtkRenderingUIObjectFactory);

// Now create the functions to create overrides with.
VTK_CREATE_CREATE_FUNCTION(vtkGenericRenderWindowInteractor)
VTK_CREATE_CREATE_FUNCTION(vtkSDL2RenderWindowInteractor)


vtkRenderingUIObjectFactory::vtkRenderingUIObjectFactory()
{
this->RegisterOverride("vtkRenderWindowInteractor", "vtkGenericRenderWindowInteractor", "Override for VTK::RenderingUI module", 1, vtkObjectFactoryCreatevtkGenericRenderWindowInteractor);
this->RegisterOverride("vtkRenderWindowInteractor", "vtkSDL2RenderWindowInteractor", "Override for VTK::RenderingUI module", 1, vtkObjectFactoryCreatevtkSDL2RenderWindowInteractor);

}

const char * vtkRenderingUIObjectFactory::GetVTKSourceVersion()
{
  return VTK_SOURCE_VERSION;
}

void vtkRenderingUIObjectFactory::PrintSelf(ostream &os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);
}

// Registration of object factories.
static unsigned int vtkRenderingUICount = 0;

VTKRENDERINGUI_EXPORT void vtkRenderingUI_AutoInit_Construct()
{
  if(++vtkRenderingUICount == 1)
  {

    // defaults
    #ifdef __EMSCRIPTEN__
    int use_platform = 0;
    int use_sdl2 = 1;
    #else
    int use_platform = 1;
    int use_sdl2 = 0;
    #endif
    // Query the enviromental for backend to use.
    if(const char* p = std::getenv("VTK_WINDOW_BACKEND"))
    {
      const std::string backend(p);
      if(backend == "PLATFORM")
      {
        use_sdl2 = 0;
        use_platform = 1;
      }
      else if(backend == "SDL2")
      {
        #ifndef VTK_ENABLE_SDL2
        vtkLogF(ERROR,"SDL2 backend requested but the SDL2 backend was not compiled");
        #else
        use_sdl2 = 1;
        use_platform = 0;
        #endif
      }
      else
      {
        vtkLogF(ERROR,"Unknown backend '%p', using default platform native window",backend.c_str());
      }
    }
      // register the factory before modyfing the overrrides so it is found below
    vtkRenderingUIObjectFactory* renderingUIFactory = vtkRenderingUIObjectFactory::New();
    if (renderingUIFactory)
    {
      // vtkObjectFactory keeps a reference to the factory,
      vtkObjectFactory::RegisterFactory(renderingUIFactory);
      renderingUIFactory->Delete();
    }
    vtkObjectFactory* object_factory;
    vtkCollectionSimpleIterator osit;
    for (vtkObjectFactory::GetRegisteredFactories()->InitTraversal(osit);
        (object_factory = vtkObjectFactory::GetRegisteredFactories()->GetNextObjectFactory(osit));)
    {
      if (object_factory->HasOverride("vtkRenderWindowInteractor"))
      {
        if (use_sdl2 && !use_platform)
        {
          object_factory->SetEnableFlag(use_sdl2, "vtkRenderWindowInteractor", "vtkSDL2RenderWindowInteractor");
          // disable ALL other interactor overrides.
          object_factory->SetEnableFlag(0, "vtkRenderWindowInteractor", "vtkGenericRenderWindowInteractor");
          object_factory->SetEnableFlag(0, "vtkRenderWindowInteractor", "vtkCocoaRenderWindowInteractor");
          object_factory->SetEnableFlag(0, "vtkRenderWindowInteractor", "vtkWin32RenderWindowInteractor");
          object_factory->SetEnableFlag(0, "vtkRenderWindowInteractor", "vtkXRenderWindowInteractor");
        }
      }
    }

    vtkRenderingUIObjectFactory* factory = vtkRenderingUIObjectFactory::New();
    if (factory)
    {
      // vtkObjectFactory keeps a reference to the "factory",
      vtkObjectFactory::RegisterFactory(factory);
      factory->Delete();
    }
  }
}
VTK_ABI_NAMESPACE_END
