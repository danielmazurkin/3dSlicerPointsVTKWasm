//
// Created by mazurkin.daniel on 6/16/23.
//

#include "vtkMRMLScene.h"
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkCamera.h>

#ifndef CONE_BASIC_H
#define CONE_BASIC_H


class BasicRender {
    vtkSmartPointer<vtkRenderer> renderer;
    vtkSmartPointer<vtkRenderWindow> renderWindow;
    vtkSmartPointer<vtkRenderWindowInteractor> interactor;
    vtkSmartPointer <vtkMRMLScene> scene;
    vtkSmartPointer<vtkCamera> camera;
public:
    BasicRender();
    void StartRendering();
    vtkRenderer* GetRenderer();
    vtkMRMLScene* GetMRMLScene();
    vtkRenderWindow* GetRendererWindow();
    vtkCamera* GetCamera();
};


#endif //CONE_BASIC_H
