//
// Created by mazurkin.daniel on 6/16/23.
//

#include "vtkMRMLScene.h"
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkCamera.h>
#include <Line.h>

#ifndef CONE_BASIC_H
#define CONE_BASIC_H


class BasicRender {
    vtkSmartPointer<vtkRenderer> renderer;
    vtkSmartPointer<vtkRenderWindow> renderWindow;
    vtkSmartPointer<vtkRenderWindowInteractor> interactor;
    vtkSmartPointer <vtkMRMLScene> scene;
    vtkSmartPointer<vtkCamera> camera;
    Line *line_from_slicer;
public:
    BasicRender();
    void StartRendering(int height, int width);
    vtkRenderer* GetRenderer();
    vtkMRMLScene* GetMRMLScene();
    vtkRenderWindow* GetRendererWindow();
    vtkCamera* GetCamera();
    void ShowLine();
    void DestroyLine();
};


#endif //CONE_BASIC_H
