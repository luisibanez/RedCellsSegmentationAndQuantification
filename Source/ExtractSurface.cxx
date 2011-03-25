#include "vtkSmartPointer.h"
#include "vtkMetaImageReader.h"
#include "vtkContourFilter.h"
#include "vtkPolyDataConnectivityFilter.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"
#include "vtkProperty.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkPolyDataWriter.h"

int main(int argc, char* argv[])
{
  if (argc < 4)
    {
    std::cerr << "Usage: " << argv[0]
              << " InputFile(.mhd/.mha) OutputFile(.vtk) Threshold" << std::endl;
    return EXIT_FAILURE;
    }

  const char * inputFileName = argv[1];
  const char * outputFileName = argv[2];
  float threshold = atof(argv[3]);

  // Load data
  vtkSmartPointer<vtkMetaImageReader> reader =
    vtkSmartPointer<vtkMetaImageReader>::New();
  reader->SetFileName(inputFileName);

  // Create a 3D surface
  vtkSmartPointer<vtkContourFilter> mc =
    vtkSmartPointer<vtkContourFilter>::New();
  mc->SetInputConnection(reader->GetOutputPort());
  mc->ComputeNormalsOn();
  mc->ComputeGradientsOn();
  mc->SetValue(0, threshold);  // second value acts as threshold

  // To extract largest region
  vtkSmartPointer<vtkPolyDataConnectivityFilter> confilter =
    vtkSmartPointer<vtkPolyDataConnectivityFilter>::New();

  confilter->SetInputConnection(mc->GetOutputPort());
  confilter->SetExtractionModeToLargestRegion();


  // Write out surface
  vtkSmartPointer<vtkPolyDataWriter> writer =
    vtkSmartPointer<vtkPolyDataWriter>::New();

  writer->SetFileName( outputFileName );
  writer->SetInputConnection( confilter->GetOutputPort() );
  writer->Update();

  // Create a mapper
  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();

  mapper->SetInputConnection(confilter->GetOutputPort());

  mapper->ScalarVisibilityOff();    // utilize actor's property I set

  // Visualize
  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();

  actor->GetProperty()->SetColor(1,1,1);
  actor->SetMapper(mapper);

  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor(actor);

  vtkSmartPointer<vtkRenderWindow> renwin =
    vtkSmartPointer<vtkRenderWindow>::New();
  renwin->AddRenderer(renderer);

  vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renwin);
  iren->Initialize();
  iren->Start();

  return EXIT_SUCCESS;
}
