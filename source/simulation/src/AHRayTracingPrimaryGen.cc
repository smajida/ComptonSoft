/*************************************************************************
 *                                                                       *
 * Copyright (c) 2011 Tamotsu Sato, Hirokazu Odaka                       *
 *                                                                       *
 * This program is free software: you can redistribute it and/or modify  *
 * it under the terms of the GNU General Public License as published by  *
 * the Free Software Foundation, either version 3 of the License, or     *
 * (at your option) any later version.                                   *
 *                                                                       *
 * This program is distributed in the hope that it will be useful,       *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 * GNU General Public License for more details.                          *
 *                                                                       *
 * You should have received a copy of the GNU General Public License     *
 * along with this program.  If not, see <http://www.gnu.org/licenses/>. *
 *                                                                       *
 *************************************************************************/

#include "AHRayTracingPrimaryGen.hh"
#include "fitsio.h"
#include "G4SystemOfUnits.hh"

using namespace anl;
using namespace anlgeant4;
using namespace comptonsoft;


AHRayTracingPrimaryGen::AHRayTracingPrimaryGen()
  : m_FileName("raytracing.fits"),
    m_EventNum(0),
    m_ID(0)
{
  add_alias("AHRayTracingPrimaryGen");
}


ANLStatus AHRayTracingPrimaryGen::mod_startup()
{
  BasicPrimaryGen::mod_startup();
  
  unregister_parameter("particle");
  setParticleName("gamma");
  unregister_parameter("photon_index");
  unregister_parameter("energy_min");
  unregister_parameter("energy_max");
  
  register_parameter(&m_FileName, "filename");
  register_parameter(&m_offset, "position_offset", mm, "mm");
  
  return AS_OK;
}


ANLStatus AHRayTracingPrimaryGen::mod_init()
{
  BasicPrimaryGen::mod_init();

  fitsfile* fits(0);
  int fits_status(0);
  
  
  // ** open file ** //
  std::cout << " * Open FITS file" << std::endl;
  
  fits_open_file(&fits, m_FileName.c_str(), READONLY, &fits_status);
  
  if (fits_status) {
    fits_report_error(stderr, fits_status);
    return AS_QUIT_ERR;
  }
  
  
  // ** check column ** //
  std::cout << " * Check column" << std::endl;
  
  std::string colname[6] = {"energy","x","y","xDirection","yDirection","zDirection"};
  int colid[6] = {0};
  
  for( int i=0; i<6; ++i ){
    fits_get_colnum(fits, CASEINSEN, const_cast<char*>(colname[i].c_str()),
                    &colid[i], &fits_status);
    
    if (fits_status) {
      fits_report_error(stderr, fits_status);
      return AS_QUIT_ERR;
    }
  }
  
  
  // ** get key ** //
  std::cout << " * Get key" << std::endl;
  
  int nfound, anynull;
  long naxes[2];
  
  fits_read_keys_lng(fits, (char*)"NAXIS", 1, 2, naxes, &nfound, &fits_status);
  
  m_EventNum = (int)naxes[1];
  
  std::cout << "FITS read >> " << nfound << " " << m_EventNum << " " << naxes[0] << " " << naxes[1] << std::endl;
  
  if (fits_status) {
    fits_report_error(stderr, fits_status);
    return AS_QUIT_ERR;
  }
  
  
  // ** get column ** //
  std::cout << " * Get column" << std::endl;
  
  double doublenull(0.0);
  
  for( int i=0; i<6; ++i ){
    
    std::cout << "  ** Get " << colname[i] << std::endl;
    
    m_Column[i] = new double[m_EventNum];
    
    fits_read_col(fits, TDOUBLE, colid[i], (long)1, (long)1,
                  naxes[1], &doublenull,
                  m_Column[i], &anynull, &fits_status);
    
    if (fits_status) {
      fits_report_error(stderr, fits_status);
      return AS_QUIT_ERR;
    }
    
    std::cout << "  ** -> OK "<< std::endl;
  }
  
  
  // ** postprocess ** //
  std::cout << " * Close FITS File" << std::endl;
  
  fits_close_file(fits, &fits_status);
  
  if (fits_status) {
    fits_report_error(stderr, fits_status);
    return AS_QUIT_ERR;
  }
  
  return AS_OK;
}


ANLStatus AHRayTracingPrimaryGen::mod_ana()
{
  const int id = m_ID;
  if (id == m_EventNum) return AS_QUIT;
  
  double energy = m_Column[0][id]*keV;
  double x = m_Column[1][id]*mm;
  double y = m_Column[2][id]*mm;
  double z = 0.0;
  double xDirection = m_Column[3][id];
  double yDirection = m_Column[4][id];
  double zDirection = m_Column[5][id];
  
  G4ThreeVector position = m_offset + G4ThreeVector(x,y,z);
  
  G4ThreeVector direction(xDirection, yDirection, zDirection);
  direction.unit();
  
  setPrimary(position, energy, direction);
  
  ++m_ID;
  
  return BasicPrimaryGen::mod_ana();
}


ANLStatus AHRayTracingPrimaryGen::mod_exit()
{
  for( int i=0; i<6; ++i ){
    std::cout << " ** delete FITS column " << std::endl;
    delete[] m_Column[i];
  }
  
  return AS_OK;
}
