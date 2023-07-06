#ifndef __EMSCRIPTEN__

#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkMRMLScene.h>
#include "BasicRender.h"
#include "Line.h"

int main(int, char*[])
{
    BasicRender basicRender;
    basicRender.StartRendering();
    return 0;
}

#endif

#ifdef __EMSCRIPTEN__
//#include <emscripten/bind.h>
//#include <BasicRender.h>
//#include <Line.h>
//
//EMSCRIPTEN_BINDINGS(test_app_binding)
//{
//  emscripten::class_<BasicRender>("BasicRender")
//    .constructor<>()
//    .function("StartRendering", &BasicRender::StartRendering)
//    .function("DestroyLine", &BasicRender::DestroyLine)
//    .function("ShowLine", &BasicRender::ShowLine);
//}

#include <vtkSmartPointer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkMRMLMarkupsLineNode.h>
#include <vtkMRMLScene.h>
#include <vtkSlicerMarkupsWidget.h>
#include <vtkSlicerMarkupsWidgetRepresentation3D.h>
#include <vtkMRMLUnitNode.h>
#include <iostream>
#include <vtkMRMLModelDisplayNode.h>
#include <vtkCamera.h>
#include <vtkVector.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkSlicerApplicationLogic.h>
#include <vtkMRMLInteractionNode.h>
#include <vtkMRMLViewDisplayableManager.h>
#include <vtkViewport.h>
#include <vtkRendererCollection.h>
#include <vtkMRMLViewNode.h>
#include <vtkMRMLMarkupsFiducialNode.h>
#include <vtkSlicerPointsRepresentation3D.h>
#include <vtkSlicerPointsWidget.h>
#include <vtkCallbackCommand.h>
#include <vtkPointPicker.h>
#include <vtkTimerLog.h>


using namespace std;

struct DataForTransfer {
    vtkSmartPointer<vtkMRMLMarkupsNode> lineNode;
    vtkSmartPointer<vtkSlicerPointsRepresentation3D> rep;
    vtkSmartPointer<vtkMRMLAbstractViewNode> viewNode;
    vtkSmartPointer<vtkMRMLMarkupsDisplayNode> displayNode;
};

DataForTransfer dataForTransferVar;


void MousePressEvent(vtkObject* obj, long unsigned int eventId, void* clientData, void* callData)
{
    vtkRenderWindowInteractor* interactor = static_cast<vtkRenderWindowInteractor*>(obj);
    vtkPointPicker* picker = static_cast<vtkPointPicker*>(interactor->GetPicker());

    int* clickPos = interactor->GetEventPosition();
    picker->Pick(clickPos[0], clickPos[1], 0, interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer());

    double* point = picker->GetPickPosition();
//    std::cout << "Coordinates: " << point[0] << ", " << point[1] << ", " << point[2] << std::endl;\

    vtkVector3d point5(point[0], point[1], point[2]);  // Создайте вторую точку
    dataForTransferVar.lineNode->AddControlPoint(point5);  // Добавьте вторую точку в markupsNode
    dataForTransferVar.rep->SetViewNode(dataForTransferVar.viewNode);
    dataForTransferVar.rep->SetMarkupsDisplayNode(dataForTransferVar.displayNode);
    dataForTransferVar.rep->UpdateFromMRML(nullptr, 0); // full update
}


int main(int argc, char *argv[]) {
    // Создание визуализатора VTK
    vtkSmartPointer <vtkMRMLScene> scene = vtkSmartPointer<vtkMRMLScene>::New();

    // Создание MRML узла
    vtkSmartPointer <vtkMRMLMarkupsNode> lineNode = vtkSmartPointer<vtkMRMLMarkupsFiducialNode>::New();
    lineNode->SetID("id_test");
    lineNode->SetName("Line");

    dataForTransferVar.lineNode = lineNode;

    vtkVector3d point2(0.05, 0.05, 0);  // Создайте вторую точку
    lineNode->AddControlPoint(point2);  // Добавьте вторую точку в markupsNode

    vtkSmartPointer<vtkMRMLInteractionNode> interaction_node = vtkSmartPointer<vtkMRMLInteractionNode>::New();
    interaction_node->SetScene(scene);

    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();

    vtkRendererCollection* rendererCollection = renderWindow->GetRenderers();
    vtkRenderer* renderer_from_collection = rendererCollection->GetFirstRenderer();

    renderWindow->AddRenderer(renderer);

    vtkSmartPointer<vtkSlicerPointsRepresentation3D> rep = vtkSmartPointer<vtkSlicerPointsRepresentation3D>::New();

    dataForTransferVar.rep = rep;

    vtkSmartPointer<vtkMRMLMarkupsDisplayNode> displayNode = vtkSmartPointer<vtkMRMLMarkupsDisplayNode>::New();
    dataForTransferVar.displayNode = displayNode;
    displayNode->SetScene(scene);

    rep->SetMarkupsNode(lineNode);

    scene->AddNode(lineNode);
    scene->AddNode(displayNode);

    // Создание интерактора
    vtkSmartPointer<vtkRenderWindowInteractor> interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    interactor->Initialize();
    interactor->SetRenderWindow(renderer->GetRenderWindow());
    renderWindow->AddRenderer(renderer);
    renderWindow->Render();

    vtkSmartPointer<vtkPointPicker> picker = vtkSmartPointer<vtkPointPicker>::New();
    interactor->SetPicker(picker);

    vtkSmartPointer<vtkMRMLAbstractViewNode> viewNode = vtkSmartPointer<vtkMRMLViewNode>::New();
    dataForTransferVar.viewNode = viewNode;
    // Создание MRML сцены
    // Создание виджета
    cout << "main(): viewNode: " << viewNode << endl;

    vtkSmartPointer<vtkSlicerPointsWidget> widgetPoint = vtkSmartPointer<vtkSlicerPointsWidget>::New();
    cout << "slicer_line_widget->SetRenderer(renderer) Before" << endl;
    widgetPoint->SetRenderer(renderer);
    cout << "slicer_line_widget->SetRenderer(renderer) After" << endl;

    widgetPoint->SetRepresentation(rep);
//    cout << "main(): Widget->GetRepresentation()" << widgetPoint->GetRepresentation() << endl;
    rep->SetViewNode(viewNode);
    rep->SetMarkupsDisplayNode(displayNode);
    rep->UpdateFromMRML(nullptr, 0); // full update


    vtkSmartPointer<vtkCallbackCommand> clickCallback = vtkSmartPointer<vtkCallbackCommand>::New();
    clickCallback->SetCallback(MousePressEvent);
    interactor->AddObserver(vtkCommand::LeftButtonPressEvent, clickCallback);

    vtkVector3d point3(0.01, 0.01, 0);  // Создайте вторую точку
    lineNode->AddControlPoint(point3);  // Добавьте вторую точку в markupsNode
    rep->SetViewNode(viewNode);
    rep->SetMarkupsDisplayNode(displayNode);
    rep->UpdateFromMRML(nullptr, 0); // full update

    vtkVector3d point4(0.01, 0.01, 0);  // Создайте вторую точку
    lineNode->AddControlPoint(point4);  // Добавьте вторую точку в markupsNode
    rep->SetViewNode(viewNode);
    rep->SetMarkupsDisplayNode(displayNode);
    rep->UpdateFromMRML(nullptr, 0); // full update

    vtkVector3d point5(0.06, 0.08, 0);  // Создайте вторую точку
    lineNode->AddControlPoint(point5);  // Добавьте вторую точку в markupsNode
    rep->SetViewNode(viewNode);
    rep->SetMarkupsDisplayNode(displayNode);
    rep->UpdateFromMRML(nullptr, 0); // full update

    vtkVector3d point6(0.15, 0.01, 0);  // Создайте вторую точку
    lineNode->AddControlPoint(point6);  // Добавьте вторую точку в markupsNode
    rep->SetViewNode(viewNode);
    rep->SetMarkupsDisplayNode(displayNode);
    rep->UpdateFromMRML(nullptr, 0); // full update

    int numFrames = 100;
    double totalTime = 0.0;

//    for (int i = 0; i < numFrames; i++)
//    {
//        double t1 = vtkTimerLog::GetUniversalTime();
//        renderWindow->Render();
//        double t2 = vtkTimerLog::GetUniversalTime();
//        double elapsedTime = t2 - t1;
//        totalTime += elapsedTime;
//    }
//    double averageTime = totalTime / numFrames;

    vtkSmartPointer<vtkCamera> camera = vtkSmartPointer<vtkCamera>::New();
    renderer->SetActiveCamera(camera);
    renderer->AddActor(widgetPoint->GetRepresentation());

    interactor->Start();

    return 0;
}
#endif
