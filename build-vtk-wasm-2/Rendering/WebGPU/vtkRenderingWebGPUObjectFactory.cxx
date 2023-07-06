/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkRenderingWebGPUObjectFactory.cxx

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

#include "vtkRenderingWebGPUObjectFactory.h"
#include "vtkVersion.h"

// Include all of the classes we want to create overrides for.
#include <vtkCollection.h>
#include <vtkObjectFactoryCollection.h>
#include <vtkLogger.h>
#include <cstdlib>
#include "vtkWebGPUActor.h"
#include "vtkWebGPUCamera.h"
#include "vtkWebGPUHardwareSelector.h"
#include "vtkWebGPULight.h"
#include "vtkWebGPUPolyDataMapper.h"
#include "vtkWebGPUProperty.h"
#include "vtkWebGPURenderer.h"
#include "vtkSDL2WebGPURenderWindow.h"


VTK_ABI_NAMESPACE_BEGIN

vtkStandardNewMacro(vtkRenderingWebGPUObjectFactory);

// Now create the functions to create overrides with.
VTK_CREATE_CREATE_FUNCTION(vtkWebGPUActor)
VTK_CREATE_CREATE_FUNCTION(vtkWebGPUCamera)
VTK_CREATE_CREATE_FUNCTION(vtkWebGPUHardwareSelector)
VTK_CREATE_CREATE_FUNCTION(vtkWebGPULight)
VTK_CREATE_CREATE_FUNCTION(vtkWebGPUPolyDataMapper)
VTK_CREATE_CREATE_FUNCTION(vtkWebGPUProperty)
VTK_CREATE_CREATE_FUNCTION(vtkWebGPURenderer)
VTK_CREATE_CREATE_FUNCTION(vtkSDL2WebGPURenderWindow)


vtkRenderingWebGPUObjectFactory::vtkRenderingWebGPUObjectFactory()
{
this->RegisterOverride("vtkActor", "vtkWebGPUActor", "Override for VTK::RenderingWebGPU module", 1, vtkObjectFactoryCreatevtkWebGPUActor);
this->RegisterOverride("vtkCamera", "vtkWebGPUCamera", "Override for VTK::RenderingWebGPU module", 1, vtkObjectFactoryCreatevtkWebGPUCamera);
this->RegisterOverride("vtkHardwareSelector", "vtkWebGPUHardwareSelector", "Override for VTK::RenderingWebGPU module", 1, vtkObjectFactoryCreatevtkWebGPUHardwareSelector);
this->RegisterOverride("vtkLight", "vtkWebGPULight", "Override for VTK::RenderingWebGPU module", 1, vtkObjectFactoryCreatevtkWebGPULight);
this->RegisterOverride("vtkPolyDataMapper", "vtkWebGPUPolyDataMapper", "Override for VTK::RenderingWebGPU module", 1, vtkObjectFactoryCreatevtkWebGPUPolyDataMapper);
this->RegisterOverride("vtkProperty", "vtkWebGPUProperty", "Override for VTK::RenderingWebGPU module", 1, vtkObjectFactoryCreatevtkWebGPUProperty);
this->RegisterOverride("vtkRenderer", "vtkWebGPURenderer", "Override for VTK::RenderingWebGPU module", 1, vtkObjectFactoryCreatevtkWebGPURenderer);
this->RegisterOverride("vtkRenderWindow", "vtkSDL2WebGPURenderWindow", "Override for VTK::RenderingWebGPU module", 1, vtkObjectFactoryCreatevtkSDL2WebGPURenderWindow);

}

const char * vtkRenderingWebGPUObjectFactory::GetVTKSourceVersion()
{
  return VTK_SOURCE_VERSION;
}

void vtkRenderingWebGPUObjectFactory::PrintSelf(ostream &os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);
}

// Registration of object factories.
static unsigned int vtkRenderingWebGPUCount = 0;

VTKRENDERINGWEBGPU_EXPORT void vtkRenderingWebGPU_AutoInit_Construct()
{
  if(++vtkRenderingWebGPUCount == 1)
  {

  // defaults
  int use_opengl = 1;
  int use_webgpu = 0;
  // Query the enviromental for backend to use.
  if(const char* p = std::getenv("VTK_GRAPHICS_BACKEND"))
  {
    const std::string backend(p);
    if(backend == "OPENGL")
    {
      use_webgpu = 0;
      use_opengl = 1;
    }
    else if(backend == "WEBGPU")
    {
      #ifndef VTK_ENABLE_WEBGPU
      vtkLogF(ERROR,"WEBGPU backend requested but the WEBGPU backend was not compiled");
      #else
      use_webgpu = 1;
      use_opengl = 0;
      #endif
    }
    else
    {
      vtkLogF(ERROR,"Unknown backend '%p', using default OPENGL",backend.c_str());
    }
  }
    // register the factory before modyfing the overrrides so it is found below
  vtkRenderingWebGPUObjectFactory* renderingFactory = vtkRenderingWebGPUObjectFactory::New();
  if (renderingFactory)
  {
    // vtkObjectFactory keeps a reference to the factory,
    vtkObjectFactory::RegisterFactory(renderingFactory);
    renderingFactory->Delete();
  }
  vtkObjectFactory* object_factory;
  vtkCollectionSimpleIterator osit;
  for (vtkObjectFactory::GetRegisteredFactories()->InitTraversal(osit);
      (object_factory = vtkObjectFactory::GetRegisteredFactories()->GetNextObjectFactory(osit));)
  {
    if (object_factory->HasOverride("vtkActor"))
    {
      object_factory->SetEnableFlag(use_webgpu, "vtkActor", "vtkWebGPUActor");
      object_factory->SetEnableFlag(use_opengl, "vtkActor", "vtkOpenGLActor");
    }
    if (object_factory->HasOverride("vtkCamera"))
    {
      object_factory->SetEnableFlag(use_webgpu, "vtkCamera", "vtkWebGPUCamera");
      object_factory->SetEnableFlag(use_opengl, "vtkCamera", "vtkOpenGLCamera");
    }
    if (object_factory->HasOverride("vtkHardwareSelector"))
    {
      object_factory->SetEnableFlag(use_webgpu, "vtkHardwareSelector", "vtkWebGPUHardwareSelector");
      object_factory->SetEnableFlag(use_opengl, "vtkHardwareSelector", "vtkOpenGLHardwareSelector");
    }
    if (object_factory->HasOverride("vtkLight"))
    {
      object_factory->SetEnableFlag(use_webgpu, "vtkLight", "vtkWebGPULight");
      object_factory->SetEnableFlag(use_opengl, "vtkLight", "vtkOpenGLLight");
    }
    if (object_factory->HasOverride("vtkPolyDataMapper"))
    {
      object_factory->SetEnableFlag(use_webgpu, "vtkPolyDataMapper", "vtkWebGPUPolyDataMapper");
      object_factory->SetEnableFlag(use_opengl, "vtkPolyDataMapper", "vtkOpenGLPolyDataMapper");
      object_factory->SetEnableFlag(use_opengl, "vtkPolyDataMapper", "vtkOpenGLES30PolyDataMapper");
    }
    if (object_factory->HasOverride("vtkProperty"))
    {
      object_factory->SetEnableFlag(use_webgpu, "vtkProperty", "vtkWebGPUProperty");
      object_factory->SetEnableFlag(use_opengl, "vtkProperty", "vtkOpenGLProperty");
    }
    if (object_factory->HasOverride("vtkRenderer"))
    {
      object_factory->SetEnableFlag(use_webgpu, "vtkRenderer", "vtkWebGPURenderer");
      object_factory->SetEnableFlag(use_opengl, "vtkRenderer", "vtkOpenGLRenderer");
    }
    if (object_factory->HasOverride("vtkRenderWindow"))
    {
      if (use_webgpu && !use_opengl)
      {
        object_factory->SetEnableFlag(use_webgpu, "vtkRenderWindow", "vtkSDL2WebGPURenderWindow");
        // disable ALL opengl render window overrides.
        object_factory->SetEnableFlag(0, "vtkRenderWindow", "vtkCocoaOpenGLRenderWindow");
        object_factory->SetEnableFlag(0, "vtkRenderWindow", "vtkWin32OpenGLRenderWindow");
        object_factory->SetEnableFlag(0, "vtkRenderWindow", "vtkXOpenGLRenderWindow");
        object_factory->SetEnableFlag(0, "vtkRenderWindow", "vtkSDL2OpenGLRenderWindow");
      }
    }
  }

    vtkRenderingWebGPUObjectFactory* factory = vtkRenderingWebGPUObjectFactory::New();
    if (factory)
    {
      // vtkObjectFactory keeps a reference to the "factory",
      vtkObjectFactory::RegisterFactory(factory);
      factory->Delete();
    }
  }
}
VTK_ABI_NAMESPACE_END
