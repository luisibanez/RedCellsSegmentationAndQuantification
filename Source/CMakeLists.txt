#
#
#
add_executable( ImageSeriesReadWrite  ImageSeriesReadWrite.cxx )
target_link_libraries( ImageSeriesReadWrite ${ITK_LIBRARIES} )

add_executable( MedianImageFilter  MedianImageFilter.cxx )
target_link_libraries( MedianImageFilter ${ITK_LIBRARIES} )
