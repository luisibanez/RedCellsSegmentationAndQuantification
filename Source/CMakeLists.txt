#
#
#
add_executable( ImageSeriesReadWrite  ImageSeriesReadWrite.cxx )
target_link_libraries( ImageSeriesReadWrite ${ITK_LIBRARIES} )

add_executable( SimpleImageReconstruction  SimpleImageReconstruction.cxx )
target_link_libraries( SimpleImageReconstruction ${ITK_LIBRARIES} )

add_executable( MedianImageFilter  MedianImageFilter.cxx )
target_link_libraries( MedianImageFilter ${ITK_LIBRARIES} )

add_executable( ExtractSurface  ExtractSurface.cxx )
target_link_libraries( ExtractSurface vtkHybrid)

add_executable( ComputeSurfaceAndVolume  ComputeSurfaceAndVolume.cxx )
target_link_libraries( ComputeSurfaceAndVolume vtkHybrid)

add_executable( RobustThresholdingPerSlice  RobustThresholdingPerSlice.cxx )
target_link_libraries( RobustThresholdingPerSlice ${ITK_LIBRARIES})

add_executable( OtsuThresholdingPerSlice  OtsuThresholdingPerSlice.cxx )
target_link_libraries( OtsuThresholdingPerSlice ${ITK_LIBRARIES})
