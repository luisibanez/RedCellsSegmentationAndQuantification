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

#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkRobustAutomaticThresholdImageFilter.h"
#include "itkGradientMagnitudeRecursiveGaussianImageFilter.h"

int main(int argc, char * argv [] )
{

  if( argc != 4 )
    {
    std::cerr << "usage: " << argv[0] << " inputImage outputImage pow" << std::endl;
    return EXIT_FAILURE;
    }

  const unsigned int Dimension = 2;

  typedef unsigned short                      PixelType;
  typedef itk::Image< PixelType, Dimension >  ImageType;

  typedef float                                   RealPixelType;
  typedef itk::Image< RealPixelType, Dimension >  RealImageType;

  typedef itk::ImageFileReader< ImageType > ReaderType;
  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName( argv[1] );
  reader->Update();

  ImageType::ConstPointer inputImage = reader->GetOutput();

  ImageType::SpacingType spacing = inputImage->GetSpacing();

  typedef itk::GradientMagnitudeRecursiveGaussianImageFilter< ImageType, RealImageType > GradientType;
  GradientType::Pointer gradient = GradientType::New();
  gradient->SetInput( reader->GetOutput() );
  gradient->SetSigma( spacing[2] );
  gradient->Update();

  typedef itk::RobustAutomaticThresholdImageFilter< ImageType, RealImageType > FilterType;

  FilterType::Pointer filter = FilterType::New();

  filter->SetInput( reader->GetOutput() );
  filter->SetGradientImage( gradient->GetOutput() );
  filter->SetPow( atof(argv[3]) );

  typedef itk::ImageFileWriter< ImageType > WriterType;
  WriterType::Pointer writer = WriterType::New();
  writer->SetInput( filter->GetOutput() );
  writer->SetFileName( argv[2] );

  try
    {
    writer->Update();
    }
  catch ( itk::ExceptionObject & excp )
    {
    std::cerr << excp << std::endl;
    return EXIT_FAILURE;
    }

  return EXIT_SUCCESS;

}
