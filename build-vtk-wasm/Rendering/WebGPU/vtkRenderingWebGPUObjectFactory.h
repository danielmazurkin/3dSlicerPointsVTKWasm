/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkRenderingWebGPUObjectFactory.h

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

#ifndef vtkRenderingWebGPUObjectFactory_h
#define vtkRenderingWebGPUObjectFactory_h

#include "vtkRenderingWebGPUModule.h" // For export macro
#include "vtkObjectFactory.h"

VTK_ABI_NAMESPACE_BEGIN

class VTKRENDERINGWEBGPU_EXPORT vtkRenderingWebGPUObjectFactory : public vtkObjectFactory
{
public:
  static vtkRenderingWebGPUObjectFactory * New();
  vtkTypeMacro(vtkRenderingWebGPUObjectFactory, vtkObjectFactory);

  const char * GetDescription() override { return "vtkRenderingWebGPU factory overrides."; }

  const char * GetVTKSourceVersion() override;

  void PrintSelf(ostream &os, vtkIndent indent) override;

protected:
  vtkRenderingWebGPUObjectFactory();

private:
  vtkRenderingWebGPUObjectFactory(const vtkRenderingWebGPUObjectFactory&) = delete;
  void operator=(const vtkRenderingWebGPUObjectFactory&) = delete;
};

VTK_ABI_NAMESPACE_END

#endif // vtkRenderingWebGPUObjectFactory_h
