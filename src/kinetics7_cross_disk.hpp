#ifndef KINETICS7_CROSSDISK_HPP
#define KINETCIS7_CROSSDISK_HPP

#include "cross_disk_base.hpp"

class Kinetics7CrossDisk : public CrossDiskBase {
public:
  Kinetics7CrossDisk() {}
  ~Kinetics7CrossDisk() {}

  void readPhotoCrossSection(std::string fname) override;

  void readSpeciesNames(std::string fname) override;

  void readWavelength(std::string fname) override;

  void readReactions(std::string fname) override;

  void readWavelengthStartIndex(std::string fname);

  void readWavelengthEndIndex(std::string fname);

private:
  // wavelength start and end index
  std::vector<int> iws_, iwe_;
};

#endif
