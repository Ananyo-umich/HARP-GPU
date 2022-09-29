// C/C++ headers
#include <iostream>

// harp headers
#include <cross_disks>

int main(int arg, char **argv) {
  Kinetics7CrossDisk crossdisk;

  crossdisk.readWavelength("KINETICS7_Bhattacharya_092922.nc");
  
  std::cout << "number of wavelenths = " << crossdisk.wavelengths() << std::endl;
  std::cout << "wavelengths (Angstrom) " << std::endl;
  for (int i = 0; i < crossdisk.wavelengths(); ++i) {
    std::cout << crossdisk.getWavelength(i) << std::endl;
  }
}
