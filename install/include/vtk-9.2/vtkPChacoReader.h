/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkPChacoReader.h

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
/*----------------------------------------------------------------------------
 Copyright (c) Sandia Corporation
 See Copyright.txt or http://www.paraview.org/HTML/Copyright.html for details.
----------------------------------------------------------------------------*/

/**
 * @class   vtkPChacoReader
 * @brief   Read Chaco files
 *
 * vtkPChacoReader is a unstructured grid source object that reads
 * Chaco files.  The file is read by process 0 and converted into
 * a vtkUnstructuredGrid.  The vtkDistributedDataFilter is invoked
 * to divide the grid among the processes.
 */

#ifndef vtkPChacoReader_h
#define vtkPChacoReader_h

#include "vtkChacoReader.h"
#include "vtkIOParallelModule.h" // For export macro

VTK_ABI_NAMESPACE_BEGIN
class vtkTimerLog;
class vtkMultiProcessController;

class VTKIOPARALLEL_EXPORT vtkPChacoReader : public vtkChacoReader
{
public:
  static vtkPChacoReader* New();
  vtkTypeMacro(vtkPChacoReader, vtkChacoReader);
  void PrintSelf(ostream& os, vtkIndent indent) override;

  /**
   * Set/Get the communicator object (we'll use global World controller
   * if you don't set a different one).
   */

  void SetController(vtkMultiProcessController* c);
  vtkGetObjectMacro(Controller, vtkMultiProcessController);

protected:
  vtkPChacoReader();
  ~vtkPChacoReader() override;

  int RequestInformation(vtkInformation*, vtkInformationVector**, vtkInformationVector*) override;
  int RequestData(vtkInformation*, vtkInformationVector**, vtkInformationVector*) override;

private:
  vtkPChacoReader(const vtkPChacoReader&) = delete;
  void operator=(const vtkPChacoReader&) = delete;

  void SetUpEmptyGrid(vtkUnstructuredGrid* output);
  int DivideCells(vtkMultiProcessController* contr, vtkUnstructuredGrid* output, int source);
  int SendGrid(vtkMultiProcessController* c, int to, vtkUnstructuredGrid* grid);
  vtkUnstructuredGrid* GetGrid(vtkMultiProcessController* c, int from);
  vtkUnstructuredGrid* SubGrid(vtkUnstructuredGrid* ug, vtkIdType from, vtkIdType to);
  char* MarshallDataSet(vtkUnstructuredGrid* extractedGrid, vtkIdType& len);
  vtkUnstructuredGrid* UnMarshallDataSet(char* buf, vtkIdType size);

  int NumProcesses;
  int MyId;

  vtkMultiProcessController* Controller;
};

VTK_ABI_NAMESPACE_END
#endif
