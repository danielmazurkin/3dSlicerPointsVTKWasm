#include <vtkSmartPointer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkMRMLMarkupsLineNode.h>
#include <vtkSlicerLineRepresentation3D.h>
#include <vtkSlicerLineRepresentation2D.h>
#include <vtkMRMLScene.h>
#include <vtkSlicerLineWidget.h>
#include <vtkSlicerMarkupsWidgetRepresentation.h>
//#include <vtkSlicerMarkupsWidgetRepresentation3D.h>
#include <vtkMRMLUnitNode.h>
#include <iostream>
#include <vtkMRMLModelDisplayNode.h>
#include <vtkCamera.h>
#include <vtkVector.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkSlicerApplicationLogic.h>
#include <vtkMRMLInteractionNode.h>
#include <vtkMRMLViewDisplayableManager.h>
#include <vtkSlicerMarkupsWidgetRepresentation.h>
#include <vtkRendererCollection.h>
#include <vtkMRMLViewNode.h>
#include <vtkMRMLMarkupsFiducialNode.h>
#include <vtkMRMLSelectionNode.h>


using namespace std;


int main(int argc, char *argv[]) {
    // Создание визуализатора VTK
    vtkSmartPointer <vtkMRMLScene> scene = vtkSmartPointer<vtkMRMLScene>::New();
    vtkSmartPointer<vtkMRMLSelectionNode> selectionNode = vtkSmartPointer<vtkMRMLSelectionNode>::New();
    // Создание MRML узла
    vtkSmartPointer <vtkMRMLMarkupsNode> lineNode = vtkSmartPointer<vtkMRMLMarkupsLineNode>::New();
    lineNode->SetID("id_test");
    lineNode->SetName("Line");
    lineNode->SetScene(scene);
    scene->AddNode(selectionNode);
//    selectionNode->SetReferenceActivePlaceNodeID(lineNode->GetID());

    vtkVector3d point1(0, 0, 0);  // Создайте первую точку
    int first_result_control_point = lineNode->AddControlPoint(point1);  // Добавьте первую точку в markupsNode

    cout << "main(): first_Result_control_point = " << first_result_control_point << endl;

    vtkVector3d point2(0.05, 0.05, 0);  // Создайте вторую точку
    int second_result_control_point = lineNode->AddControlPoint(point2);  // Добавьте вторую точку в markupsNode

    cout << "main(): second_result_control_point: " << second_result_control_point << endl;

    vtkSmartPointer<vtkMRMLInteractionNode> interaction_node = vtkSmartPointer<vtkMRMLInteractionNode>::New();
    interaction_node->SetScene(scene);

    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();

    vtkRendererCollection* rendererCollection = renderWindow->GetRenderers();
    vtkRenderer* renderer_from_collection = rendererCollection->GetFirstRenderer();

    renderWindow->AddRenderer(renderer);

    vtkSmartPointer<vtkSlicerLineRepresentation3D> rep = vtkSmartPointer<vtkSlicerLineRepresentation3D>::New();
    cout << "Rep = " << rep << endl;

    rep->ReleaseGraphicsResources(renderWindow);
//
    vtkSmartPointer<vtkMRMLMarkupsDisplayNode> displayNode = vtkSmartPointer<vtkMRMLMarkupsDisplayNode>::New();
    displayNode->SetScene(scene);
    displayNode->SetColor(1.0, 0.0, 0.0);

//
    rep->SetMarkupsNode(lineNode);
//
    scene->AddNode(lineNode);
    scene->AddNode(displayNode);
//
//    // Создание интерактора

    vtkSmartPointer<vtkRenderWindowInteractor> interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    interactor->SetRenderWindow(renderWindow);
    renderWindow->AddRenderer(renderer);
    renderWindow->Render();

    vtkSmartPointer<vtkMRMLAbstractViewNode> viewNode = vtkSmartPointer<vtkMRMLViewNode>::New();
    // Создание MRML сцены
    // Создание виджета
    vtkSmartPointer <vtkSlicerLineWidget> slicer_line_widget = vtkSmartPointer<vtkSlicerLineWidget>::New();
    slicer_line_widget->SetRenderer(renderer);
    slicer_line_widget->SetRepresentation(rep);
    rep->SetViewNode(viewNode);
    rep->SetMarkupsDisplayNode(displayNode);
    rep->UpdateFromMRML(nullptr, 0); // full update


    vtkSmartPointer<vtkCamera> camera = vtkSmartPointer<vtkCamera>::New();
    renderer->SetActiveCamera(camera);
    renderer->AddActor(slicer_line_widget->GetRepresentation());

    interactor->Start();

    return 0;
}
