#include <vtkSmartPointer.h>
#include <vtkNrrdReader.h>
#include <vtkPiecewiseFunction.h>
#include <vtkColorTransferFunction.h>
#include <vtkVolumeProperty.h>
#include <vtkGPUVolumeRayCastMapper.h>
#include <vtkVolume.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>

int main(int, char *[])
{
    auto reader = vtkSmartPointer<vtkNrrdReader>::New();
    reader->SetFileName("/home/danil/Cone/Cone/resources/1.nrrd");
    reader->Update();

    double data_alpha_range[2] = { 0.0, 28.0 };
    double data_colour_range[2] = { -25.0, 40.0 };

    auto opacity_transfer_function = vtkSmartPointer<vtkPiecewiseFunction>::New();

    opacity_transfer_function->AddPoint(0.0, 0.0);
    opacity_transfer_function->AddPoint(500, 0.05);
    opacity_transfer_function->AddPoint(1000, 0.15);
    opacity_transfer_function->AddPoint(1150, 0.85);


    auto colour_transfer_function = vtkSmartPointer<vtkColorTransferFunction>::New();
    colour_transfer_function->AddRGBPoint(0.0, 0.0, 0.0, 0.0);
    colour_transfer_function->AddRGBPoint(500, 1.0, 0.5, 1.0);
    colour_transfer_function->AddRGBPoint(1000, 1.0, 0.5, 1.0);
    colour_transfer_function->AddRGBPoint(1150, 1.0, 1.0, 1.0);

    auto volume_property = vtkSmartPointer<vtkVolumeProperty>::New();
    volume_property->SetColor(colour_transfer_function);
    volume_property->SetScalarOpacity(opacity_transfer_function);
    volume_property->ShadeOff();
    volume_property->SetInterpolationTypeToLinear();

    auto volume_mapper = vtkSmartPointer<vtkGPUVolumeRayCastMapper>::New();
    volume_mapper->SetInputConnection(reader->GetOutputPort());

    auto volume = vtkSmartPointer<vtkVolume>::New();
    volume->SetMapper(volume_mapper);
    volume->SetProperty(volume_property);

    auto ren1 = vtkSmartPointer<vtkRenderer>::New();
    ren1->SetBackground(0, 0, 0);
    ren1->AddActor(volume);
    ren1->ResetCamera();

    auto renWin = vtkSmartPointer<vtkRenderWindow>::New();
    renWin->AddRenderer(ren1);
    renWin->SetSize(600, 600);

    auto iren = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    iren->SetRenderWindow(renWin);

    iren->Initialize();
    iren->Start();

    return EXIT_SUCCESS;
}