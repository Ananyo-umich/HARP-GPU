// C/C++ header
#include <algorithm>

// harp headers
#include "cross_disk_base.hpp"

std::vector<std::string> CrossDiskBase::getReactants(int rid) const
{
  std::vector<std::string> x;

  for (int i = 0; i < MaxReactants; ++i) {
    if (i != -1) {
      int j = reactant_index_(rid, i);
      x.push_back(species_names_[j]);
    } else {
      break;
    }
  }

  return x;
}

std::vector<std::string> CrossDiskBase::getProducts(int rid) const
{
  std::vector<std::string> x;

  for (int i = 0; i < MaxReactants; ++i) {
    if (i != -1) {
      int j = product_index_(rid, i);
      x.push_back(species_names_[j]);
    } else {
      break;
    }
  }

  return x;
}

int CrossDiskBase::getSpeciesIndex(std::string name) const
{
  auto lower = std::lower_bound(species_names_.begin(), species_names_.end(), name);
  return lower - species_names_.begin();
}
