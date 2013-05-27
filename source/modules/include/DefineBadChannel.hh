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

#ifndef COMPTONSOFT_DefineBadChannel_H
#define COMPTONSOFT_DefineBadChannel_H 1

#include "VCSModule.hh"

namespace comptonsoft {

class DefineBadChannel : public VCSModule
{
  DEFINE_ANL_MODULE(DefineBadChannel, 2.0);
public:
  DefineBadChannel();
  ~DefineBadChannel() {}

  anl::ANLStatus mod_startup();
  anl::ANLStatus mod_init();

private:
  std::string m_FileName;
};

}

#endif /* COMPTONSOFT_DefineBadChannel_H */
