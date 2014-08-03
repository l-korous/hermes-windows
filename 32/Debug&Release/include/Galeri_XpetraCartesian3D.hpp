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
#ifndef GALERI_XPETRACARTESIAN3D_HPP
#define GALERI_XPETRACARTESIAN3D_HPP

#include <Teuchos_RCP.hpp>
#include <Teuchos_Comm.hpp>
#include <Teuchos_ArrayView.hpp>

#include "Galeri_Exception.h"
#include "Galeri_Utils.h"

namespace Galeri {

  namespace Xpetra {

    namespace Maps {

      typedef size_t global_size_t;

      //TODO: avoid using GlobalOrdinal everywhere?

      template <class LocalOrdinal, class GlobalOrdinal, class Map>
      Teuchos::RCP<Map>
      Cartesian3D(const Teuchos::RCP<const Teuchos::Comm<int> > & comm, const GlobalOrdinal nx, const GlobalOrdinal ny, const GlobalOrdinal nz,
                  const GlobalOrdinal mx, const GlobalOrdinal my, const GlobalOrdinal mz)
      {
        if (nx <= 0 || ny <= 0 || nz <= 0 ||
            mx <= 0 || my <= 0 || mz <= 0 ||
            (mx > nx) || (my > ny) || (mz > nz))
          throw(Exception(__FILE__, __LINE__,
                          "Incorrect input parameter to Maps::Cartesian3D()",
                          "nx = " + toString(nx) +
                          ", ny = " + toString(ny) +
                          ", nz = " + toString(nz) +
                          ", mx = " + toString(mx) +
                          ", my = " + toString(my) +
                          ", mz = " + toString(mz)));

        int MyPID = comm->getRank();
        GlobalOrdinal startx, starty, startz, endx, endy, endz;

        GlobalOrdinal mxy  = mx * my;
        GlobalOrdinal zpid = MyPID / mxy;
        GlobalOrdinal xpid = (MyPID % mxy) % mx;
        GlobalOrdinal ypid = (MyPID % mxy) / mx;

        GlobalOrdinal PerProcSmallXDir = (int) (((double) nx)/((double) mx));
        GlobalOrdinal PerProcSmallYDir = (int) (((double) ny)/((double) my));
        GlobalOrdinal PerProcSmallZDir = (int) (((double) nz)/((double) mz));
        GlobalOrdinal NBigXDir         = nx - PerProcSmallXDir*mx;
        GlobalOrdinal NBigYDir         = ny - PerProcSmallYDir*my;
        GlobalOrdinal NBigZDir         = nz - PerProcSmallZDir*mz;

        if (xpid < NBigXDir) startx =  xpid*(PerProcSmallXDir+1);
        else                 startx = (xpid-NBigXDir)*PerProcSmallXDir +
          NBigXDir*(PerProcSmallXDir+1);
        endx = startx + PerProcSmallXDir;
        if (xpid < NBigXDir) endx++;

        if (ypid < NBigYDir) starty =  ypid*(PerProcSmallYDir+1);
        else                 starty = (ypid-NBigYDir)*PerProcSmallYDir +
          NBigYDir*(PerProcSmallYDir+1);
        endy = starty + PerProcSmallYDir;
        if ( ypid < NBigYDir) endy++;

        if (zpid < NBigZDir) startz =  zpid*(PerProcSmallZDir+1);
        else                 startz = (zpid-NBigZDir)*PerProcSmallZDir +
          NBigZDir*(PerProcSmallZDir+1);
        endz = startz + PerProcSmallZDir;
        if ( zpid < NBigZDir) endz++;

        size_t NumMyElements = (endx - startx) * (endy - starty) * (endz - startz);
        vector<GlobalOrdinal> MyGlobalElements(NumMyElements);
        size_t count = 0;

        for (GlobalOrdinal i = startx ; i < endx ; ++i)
          for (GlobalOrdinal j = starty ; j < endy ; ++j)
            for (GlobalOrdinal k = startz ; k < endz ; ++k)
              MyGlobalElements[count++] = i + j * nx +k * (nx * ny);

        global_size_t numGlobalElements = nx * ny * nz;
        const Teuchos::ArrayView<const GlobalOrdinal> elementList(MyGlobalElements);
        return MapTraits<GlobalOrdinal,Map>::Build(numGlobalElements, elementList, 0/*indexBase*/, comm /*TODO:node*/);

      } // Cartesian3D()

    } // namespace Maps
  } // namespace Xpetra
} // namespace Galeri

#endif
