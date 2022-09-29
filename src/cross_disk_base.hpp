#ifndef CROSSDISK_BASE_HPP
#define CROSSDISK_BASE_HPP

// C/C++ headers
#include <vector>
#include <string>
#include <bitset>

// harp headers
#include <configure.hpp>

//! Base class for photochemistry cross disk
class CrossDiskBase {
public:
  CrossDiskBase() {}
  virtual ~CrossDiskBase() {}

  virtual void readSpeciesNames(std::string fname) {}

  virtual void readWavelength(std::string fname) {}

  virtual void readWavenumber(std::string fname) {}

  virtual void readPhotoCrossSection(std::string fname) {}

  virtual void readReactions(std::string fname) {}

  int getSpeciesIndex(std::string name) const;

  std::vector<std::string> getReactants(int rid) const;

  std::vector<std::string> getProducts(int rid) const;

  int reactions() const {
    return cross_section_.rows();
  }

  int wavelengths() const {
    return wavelength_.size();
  }

  int wavenumbers() const {
    return wavenumber_.size();
  }

  Real const& getWavenumber(int i) const {
    return wavenumber_[i];
  }

  Real const& getWavelength(int i) const {
    return wavelength_[i];
  }

  Real getCrossSection(int rid, int wid) const {
    return cross_section_(rid, wid);
  }

  std::string getSpeciesName(int index) const {
    return species_names_[index];
  }

protected:
  std::bitset<CrossDiskStatusBits> status_;
  std::vector<std::string> species_names_;
  std::vector<Real> wavelength_;
  std::vector<Real> wavenumber_;

  Array<int, Dynamic, MaxReactants> reactant_index_;
  Array<int, Dynamic, MaxReactants> product_index_;
  Array<Real, Dynamic, Dynamic> cross_section_;
};

#endif
