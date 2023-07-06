//
// Created by danil on 6/16/23.
//

#include <vtkMRMLScene.h>
#include <vtkCamera.h>
#include <vtkSlicerLineRepresentation3D.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSlicerLineWidget.h>


#ifndef CONE_LINE_H
#define CONE_LINE_H


class Line {
    vtkSmartPointer<vtkMRMLInteractionNode> interaction_node;
    vtkSmartPointer<vtkMRMLMarkupsNode> lineNode;
    vtkSmartPointer<vtkMRMLMarkupsDisplayNode> displayNode;
    vtkSmartPointer<vtkMRMLScene> scene;
    vtkSmartPointer<vtkSlicerLineRepresentation3D> rep;
    vtkSmartPointer<vtkMRMLAbstractViewNode> viewNode;
    vtkSmartPointer<vtkSlicerLineWidget> slicer_line_widget;
public:
    Line(vtkMRMLScene* scene);
    void RenderingLine(vtkRenderer* renderer, vtkRenderWindow* renderWindow, vtkCamera* camera);
};

#endif //CONE_LINE_H
