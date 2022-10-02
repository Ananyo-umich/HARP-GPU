// C/C++ headers
#include <stdexcept>
#include <iostream>

// netcdf library headers
#include <netcdf.h>

// harp headers
#include "kinetics7_cross_disk.hpp"

void Kinetics7CrossDisk::readReactions(std::string fname)
{
  int fileid, dimid, varid, err;
  char tname[80];
  nc_open(fname.c_str(), NC_NETCDF4, &fileid);

  size_t nreactions;
  err = nc_inq_dimid(fileid, "reactions", &dimid);
  if (err != NC_NOERR)
    throw std::runtime_error(nc_strerror(err));

  err = nc_inq_dimlen(fileid, dimid, (size_t*)nreactions);
  if (err != NC_NOERR)
    throw std::runtime_error(nc_strerror(err));

  reactant_index_.resize(nreactions, MaxReactants);
  product_index_.resize(nreactions, MaxReactants);

  err = nc_inq_varid(fileid, "reactant_index", &varid);
  if (err != NC_NOERR)
    throw std::runtime_error(nc_strerror(err));
  err = nc_get_var_int(fileid, varid, reactant_index_.data());
  if (err != NC_NOERR)
    throw std::runtime_error(nc_strerror(err));

  err = nc_inq_varid(fileid, "product_index", &varid);
  if (err != NC_NOERR)
    throw std::runtime_error(nc_strerror(err));
  err = nc_get_var_int(fileid, varid, product_index_.data());
  if (err != NC_NOERR)
    throw std::runtime_error(nc_strerror(err));

  nc_close(fileid);
}

void Kinetics7CrossDisk::readSpeciesNames(std::string fname)
{
  /*int fileid, dimid, varid, err;
  nc_open(fname.c_str(), NC_NETCDF4, &fileid);

  size_t nspecies;
  nc_inq_dimid(fileid, "max_species", &dimid);
  nc_inq_dimlen(fileid, dimid, (size_t*)nspecies);
  species_names_.resize(nwaves);

  nc_inq_varid(fileid, "SpeciesList", &varid);
  nc_get_var_string(fileid, varid, species_names_.data());

  nc_close(fileid);*/
}

void Kinetics7CrossDisk::readPhotoCrossSection(std::string fname)
{
  int fileid, dimid, varid, err;
  char tname[80];
  nc_open(fname.c_str(), NC_NETCDF4, &fileid);

  size_t nwaves = wavelength_.size();
  size_t nreactions = reactant_index_.rows();

  cross_section_.resize(nreactions, nwaves);

  err = nc_inq_varid(fileid, "cross_section", &varid);
  if (err != NC_NOERR)
    throw std::runtime_error(nc_strerror(err));
  err = nc_get_var_float(fileid, varid, cross_section_.data());

  nc_close(fileid);
}

void Kinetics7CrossDisk::readWavelength(std::string fname)
{
  int fileid, dimid, varid, err;
  nc_open(fname.c_str(), NC_NETCDF4, &fileid);

  size_t nwaves;
  err = nc_inq_dimid(fileid, "wavelength", &dimid);
  if (err != NC_NOERR)
    throw std::runtime_error(nc_strerror(err));
  err = nc_inq_dimlen(fileid, dimid, &nwaves);
  if (err != NC_NOERR)
    throw std::runtime_error(nc_strerror(err));

  wavelength_.resize(nwaves);
  wavenumber_.resize(nwaves);
  status_.set(CrossDiskStatus::Wave);

  err = nc_inq_varid(fileid, "wavelength", &varid);
  if (err != NC_NOERR)
    throw std::runtime_error(nc_strerror(err));
  err = nc_get_var_float(fileid, varid, wavelength_.data());
  if (err != NC_NOERR)
    throw std::runtime_error(nc_strerror(err));

  for (size_t i = 0; i < wavelength_.size(); ++i)
    wavenumber_[i] = 1./wavelength_[i];

  nc_close(fileid);
}

void Kinetics7CrossDisk::readWavelengthStartIndex(std::string fname)
{
}

void Kinetics7CrossDisk::readWavelengthEndIndex(std::string fname)
{
}
