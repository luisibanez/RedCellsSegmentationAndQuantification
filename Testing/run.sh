#
#  Execute this script as:
#
#    ./run.sh 10 1
#
./bin/SimpleImageReconstruction "/home/ibanez/data/BroadInstitute/Harvard/GamLiveDevelopment/Image00$1.tif.frames/Image00$1_C00$2Z%03d.tif" 1 32 1e-05 1e-05 13e-05 Image00$1_C00$2Z.mhd
./bin/MedianImageFilter Image00$1_C00$2Z.mhd                Image00$1_C00$2Z_Median_3_01.mhd 3
./bin/MedianImageFilter Image00$1_C00$2Z_Median_3_01.mhd    Image00$1_C00$2Z_Median_3_02.mhd 3
./bin/MedianImageFilter Image00$1_C00$2Z_Median_3_02.mhd    Image00$1_C00$2Z_Median_3_03.mhd 3

./bin/ExtractSurface Image00$1_C00$2Z_Median_3_03.mhd  Image00$1_C00$2Z_Median_3_03.vtk 10

./bin/ComputeSurfaceAndVolume Image00$1_C00$2Z_Median_3_03.vtk

