/*=========================================================================
 *
 *  Copyright Insight Software Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/

#include "vtkSmartPointer.h"
#include "vtkPolyDataReader.h"
#include "vtkMassProperties.h"

int main(int argc, char* argv[])
{
  if (argc < 2)
    {
    std::cerr << "Usage: " << argv[0]
              << " InputFile(.vtk)" << std::endl;
    return EXIT_FAILURE;
    }

  const char * inputFileName = argv[1];

  // Load data
  vtkSmartPointer<vtkPolyDataReader> reader =
    vtkSmartPointer<vtkPolyDataReader>::New();
  reader->SetFileName(inputFileName);

  // Compute parameter
  vtkSmartPointer<vtkMassProperties> massProperties =
    vtkSmartPointer<vtkMassProperties>::New();

  massProperties->SetInputConnection( reader->GetOutputPort() );

  const double surfaceArea   = massProperties->GetSurfaceArea();
  const double surfaceVolume = massProperties->GetVolume();

  std::cout << "Area = " << surfaceArea << std::endl;
  std::cout << "Volume = " << surfaceVolume << std::endl;

  return EXIT_SUCCESS;
}
