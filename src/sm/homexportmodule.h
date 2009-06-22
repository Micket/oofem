/* $Header: /home/cvs/bp/oofem/sm/src/homexportmodule.h,v 1.9 2009/04/22 bp vs Exp $ */
/*
 *
 *****    *****   ******  ******  ***   ***
 **   **  **   **  **      **      ** *** **
 **   **  **   **  ****    ****    **  *  **
 **   **  **   **  **      **      **     **
 **   **  **   **  **      **      **     **
 *****    *****   **      ******  **     **
 *
 *
 *             OOFEM : Object Oriented Finite Element Code
 *
 *               Copyright (C) 2009 - 2009   Borek Patzak, Vit Smilauer
 *
 *
 *
 *       Czech Technical University, Faculty of Civil Engineering,
 *   Department of Structural Mechanics, 166 29 Prague, Czech Republic
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

//
// class HOMExportModule
//

#ifndef homexportmodule_h

#ifndef __MAKEDEPEND
 #include <stdio.h>
#endif
#include "exportmodule.h"
#include "domain.h"
#include "engngm.h"
#include "intarray.h"


/**
 * Represents HOM (Homogenization) export module. It averages strain and stress tensors over the whole domain
 * and all elements in global coordinate system. The strain and stress tensor (reduced to six components) is used through whole procedure. Appropriate element strain and stress components are placed using the mask of tensor indexes. Thus various element types (beam, plane element, brick) can be combined and will give correct macroscopic response.
 */
class HOMExportModule : public ExportModule
{
protected:

    /// scale all homogenized values
    double scale;
#ifdef RBR_SUPPORT
    enum omodeType { wdmode, rbrmode }; // WholeDomain or RegionByRegion output
    omodeType omode;
#endif

public:

    /// Constructor. Creates empty Output Manager.
    HOMExportModule(EngngModel *e);
    /// Destructor
    ~HOMExportModule();
    /// Initializes receiver acording to object description stored in input record.
    virtual IRResultType initializeFrom(InputRecord *ir);
    /**
     * Writes the output.
     * @param tStep time step.
     */
    void              doOutput(TimeStep *tStep);
    /**
     * Initializes receiver.
     * The init file messages should be printed.
     */
    void              initialize();
    /**
     * Terminates the receiver.
     * The terminating messages should be printed.
     * All the streams should be closed.
     */
    void              terminate();
    /// Returns class name of the receiver.
    virtual const char *giveClassName() const { return "HOMExportModule"; }


protected:
    /// stream for file
    FILE *stream;
};

#define homexportmodule_h
#endif