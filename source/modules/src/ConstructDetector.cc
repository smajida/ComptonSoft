/*************************************************************************
 *                                                                       *
 * Copyright (c) 2011 Hirokazu Odaka                                     *
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

#include "ConstructDetector.hh"
#include <iostream>
#include "VRealDetectorUnit.hh"
#include "DetectorSystem.hh"

using namespace anl;

namespace comptonsoft {

ConstructDetector::ConstructDetector()
  : detectorManager_(new DetectorSystem),
    configurationFile_("detector_config.xml"),
    verboseLevel_(0)
{
  add_alias("ConstructDetector");
}

ConstructDetector::~ConstructDetector() = default;

ANLStatus ConstructDetector::mod_startup()
{
  detectorManager_->setMCSimulation(false);

  register_parameter(&configurationFile_, "detector_configuration");
  set_parameter_description("XML data file describing a detector configuration.");

  register_parameter(&verboseLevel_, "verbose_level");

  return AS_OK;
}

ANLStatus ConstructDetector::mod_init()
{
  bool complete = detectorManager_->loadDetectorConfiguration(configurationFile_.c_str());
  if (!complete) {
    std::cout << "Loading the detector configuration failed." << std::endl;
    return AS_QUIT;
  }
  
  if (VerboseLevel() > 0) {
    detectorManager_->printDetectorGroups();
  }
  
  return AS_OK;
}

ANLStatus ConstructDetector::mod_ana()
{
  detectorManager_->initializeEvent();
  return AS_OK;
}

} /* namespace comptonsoft */
