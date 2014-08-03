// @HEADER
//
// ***********************************************************************
//
//           Galeri: Finite Element and Matrix Generation Package
//                 Copyright (2006) ETHZ/Sandia Corporation
//
// Under the terms of Contract DE-AC04-94AL85000 with Sandia Corporation,
// the U.S. Government retains certain rights in this software.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
// 1. Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright
// notice, this list of conditions and the following disclaimer in the
// documentation and/or other materials provided with the distribution.
//
// 3. Neither the name of the Corporation nor the names of the
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY SANDIA CORPORATION "AS IS" AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
// PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL SANDIA CORPORATION OR THE
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Questions? Contact
//                    Jeremie Gaidamour (jngaida@sandia.gov)
//                    Jonathan Hu       (jhu@sandia.gov)
//                    Ray Tuminaro      (rstumin@sandia.gov)
//
// ***********************************************************************
//
// @HEADER
/*
  Direct translation of parts of Galeri matrix generator.
*/
#ifndef GALERI_XPETRACARTESIAN1D_HPP
#define GALERI_XPETRACARTESIAN1D_HPP

#include <Teuchos_RCP.hpp>
#include <Teuchos_Comm.hpp>
#include <Teuchos_ArrayView.hpp>

#include "Galeri_Exception.h"
#include "Galeri_Utils.h"
#include "Galeri_MapTraits.hpp"

#ifdef HAVE_GALERI_TPETRA //TODO: this macro is not defined
#include <Tpetra_Map.hpp>
#endif

namespace Galeri {

  namespace Xpetra {

    namespace Maps {

      typedef size_t global_size_t;

      //TODO: avoid using GlobalOrdinal everywhere?

      template <class LocalOrdinal, class GlobalOrdinal, class Map>
      Teuchos::RCP<Map>
      Cartesian1D(const Teuchos::RCP<const Teuchos::Comm<int> > & comm, const GlobalOrdinal nx, const GlobalOrdinal mx)
      {
        if (nx <= 0 || mx <= 0 || (mx > nx))
          throw(Exception(__FILE__, __LINE__,
                          "Incorrect input parameter to Maps::Cartesian1D()",
                          "nx = " + toString(nx) +
                          ", mx = " + toString(mx)));

        int MyPID = comm->getRank();
        GlobalOrdinal startx, endx;
        GlobalOrdinal xpid = MyPID % mx;

        GlobalOrdinal PerProcSmallXDir = (GlobalOrdinal) (((double) nx)/((double) mx));
        GlobalOrdinal NBigXDir         = nx - PerProcSmallXDir*mx;

        if (xpid < NBigXDir) startx =  xpid*(PerProcSmallXDir+1);
        else                 startx = (xpid-NBigXDir)*PerProcSmallXDir + NBigXDir*(PerProcSmallXDir+1);
        endx = startx + PerProcSmallXDir;
        if (xpid < NBigXDir) endx++;

        size_t NumMyElements = endx - startx;
        vector<GlobalOrdinal> MyGlobalElements(NumMyElements);
        size_t count = 0;

        for (GlobalOrdinal i = startx ; i < endx ; ++i)
          MyGlobalElements[count++] = i;

        global_size_t numGlobalElements = nx;
        const Teuchos::ArrayView<const GlobalOrdinal> elementList(MyGlobalElements);
        return MapTraits<GlobalOrdinal,Map>::Build(numGlobalElements, elementList, 0/*indexBase*/, comm /*TODO:node*/);

      } // Cartesian1D()

    } // namespace Maps
  } // namespace Xpetra
} // namespace Galeri

#endif
