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
#include "itkBinaryThresholdImageFilter.h"
#include "itkSliceBySliceImageFilter.h"

int main(int argc, char * argv [] )
{

  if( argc != 4 )
    {
    std::cerr << "usage: " << argv[0] << " inputImage outputImage threshold" << std::endl;
    return EXIT_FAILURE;
    }

  const unsigned int Dimension = 3;

  typedef unsigned short                      PixelType;
  typedef itk::Image< PixelType, Dimension >  ImageType;

  typedef unsigned char                           MaskPixelType;
  typedef itk::Image< MaskPixelType, Dimension >  MaskImageType;

  typedef itk::ImageFileReader< ImageType > ReaderType;
  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName( argv[1] );


  typedef itk::SliceBySliceImageFilter< ImageType, MaskImageType > SliceFilterType;

  SliceFilterType::Pointer slicer = SliceFilterType::New();

  slicer->SetInput( reader->GetOutput() );

  typedef itk::BinaryThresholdImageFilter<
    SliceFilterType::InternalInputImageType,
    SliceFilterType::InternalOutputImageType > ThresholdFilterType;

  ThresholdFilterType::Pointer thresholder = ThresholdFilterType::New();

  thresholder->SetUpperThreshold( itk::NumericTraits< PixelType >::max() );
  thresholder->SetLowerThreshold( atoi( argv[3] ) );

  slicer->SetFilter( thresholder );

  slicer->SetInput( reader->GetOutput() );

  typedef itk::ImageFileWriter< MaskImageType > WriterType;

  WriterType::Pointer writer = WriterType::New();

  writer->SetInput( slicer->GetOutput() );
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
