/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkSplitField.h

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
/**
 * @class   vtkSplitField
 * @brief   Split a field into single component fields
 *
 * vtkSplitField is used to split a multi-component field (vtkDataArray)
 * into multiple single component fields. The new fields are put in
 * the same field data as the original field. The output arrays
 * are of the same type as the input array. Example:
 * @verbatim
 * sf->SetInputField("gradient", vtkSplitField::POINT_DATA);
 * sf->Split(0, "firstcomponent");
 * @endverbatim
 * tells vtkSplitField to extract the first component of the field
 * called gradient and create an array called firstcomponent (the
 * new field will be in the output's point data).
 * Note that, by default, the original array is also passed through.
 *
 * @warning
 * When using Java, Python or Visual Basic bindings, the array name
 * can not be one of the  AttributeTypes when calling Split() which takes
 * strings as arguments. The wrapped command will
 * always assume the string corresponds to an attribute type when
 * the argument is one of the AttributeTypes. In this situation,
 * use the Split() which takes enums.
 *
 * @sa
 * vtkFieldData vtkDataSet vtkDataObjectToDataSetFilter
 * vtkDataSetAttributes vtkDataArray vtkRearrangeFields
 * vtkAssignAttribute vtkMergeFields
 */

#ifndef vtkSplitField_h
#define vtkSplitField_h

#include "vtkDataSetAlgorithm.h"
#include "vtkFiltersGeneralModule.h" // For export macro

#include "vtkDataSetAttributes.h" // Needed for NUM_ATTRIBUTES

VTK_ABI_NAMESPACE_BEGIN
class vtkFieldData;

class VTKFILTERSGENERAL_EXPORT vtkSplitField : public vtkDataSetAlgorithm
{
public:
  vtkTypeMacro(vtkSplitField, vtkDataSetAlgorithm);
  void PrintSelf(ostream& os, vtkIndent indent) override;

  /**
   * Create a new vtkSplitField.
   */
  static vtkSplitField* New();

  /**
   * Use the given attribute in the field data given
   * by fieldLoc as input.
   */
  void SetInputField(int attributeType, int fieldLoc);

  /**
   * Use the array with given name in the field data given
   * by fieldLoc as input.
   */
  void SetInputField(const char* name, int fieldLoc);

  /**
   * Helper method used by other language bindings. Allows the caller to
   * specify arguments as strings instead of enums.
   */
  void SetInputField(const char* name, const char* fieldLoc);

  /**
   * Create a new array with the given component.
   */
  void Split(int component, const char* arrayName);

  enum FieldLocations
  {
    DATA_OBJECT = 0,
    POINT_DATA = 1,
    CELL_DATA = 2
  };

  struct Component
  {
    int Index;
    char* FieldName;
    Component* Next; // linked list
    void SetName(const char* name)
    {
      delete[] this->FieldName;
      this->FieldName = nullptr;
      if (name)
      {
        size_t len = strlen(name) + 1;
        this->FieldName = new char[len];
#ifdef _MSC_VER
        strncpy_s(this->FieldName, len, name, len - 1);
#else
        strncpy(this->FieldName, name, len);
#endif
      }
    }
    Component() { FieldName = nullptr; }
    ~Component() { delete[] FieldName; }
  };

protected:
  enum FieldTypes
  {
    NAME,
    ATTRIBUTE
  };

  vtkSplitField();
  ~vtkSplitField() override;

  int RequestData(vtkInformation*, vtkInformationVector**, vtkInformationVector*) override;

  char* FieldName;
  int FieldType;
  int AttributeType;
  int FieldLocation;

  static char FieldLocationNames[3][12];
  static char AttributeNames[vtkDataSetAttributes::NUM_ATTRIBUTES][10];

  vtkDataArray* SplitArray(vtkDataArray* da, int component);

  // Components are stored as a linked list.
  Component* Head;
  Component* Tail;

  // Methods to browse/modify the linked list.
  Component* GetNextComponent(Component* op) { return op->Next; }
  Component* GetFirst() { return this->Head; }
  void AddComponent(Component* op);
  Component* FindComponent(int index);
  void DeleteAllComponents();

  void PrintComponent(Component* op, ostream& os, vtkIndent indent);
  void PrintAllComponents(ostream& os, vtkIndent indent);

private:
  vtkSplitField(const vtkSplitField&) = delete;
  void operator=(const vtkSplitField&) = delete;
};

VTK_ABI_NAMESPACE_END
#endif
