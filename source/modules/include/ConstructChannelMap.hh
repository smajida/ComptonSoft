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

#ifndef COMPTONSOFT_ConstructChannelMap_H
#define COMPTONSOFT_ConstructChannelMap_H 1

#include <vector>
#include <string>
#include <memory>

#include "VCSModule.hh"

namespace comptonsoft {

class VChannelMap;

/**
 *
 * @author Hirokazu Odaka
 */
class ConstructChannelMap : public VCSModule
{
  DEFINE_ANL_MODULE(ConstructChannelMap, 2.0);
public:
  ConstructChannelMap();
  ~ConstructChannelMap();

  anl::ANLStatus mod_startup();
  anl::ANLStatus mod_init();

private:
  std::vector<std::shared_ptr<const VChannelMap>> channelMaps_;
  std::string filename_;
};

} /* namespace comptonsoft */

#endif /* COMPTONSOFT_ConstructChannelMap_H */
