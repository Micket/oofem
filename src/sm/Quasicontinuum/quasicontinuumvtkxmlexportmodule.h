/*
 *
 *                 #####    #####   ######  ######  ###   ###
 *               ##   ##  ##   ##  ##      ##      ## ### ##
 *              ##   ##  ##   ##  ####    ####    ##  #  ##
 *             ##   ##  ##   ##  ##      ##      ##     ##
 *            ##   ##  ##   ##  ##      ##      ##     ##
 *            #####    #####   ##      ######  ##     ##
 *
 *
 *             OOFEM : Object Oriented Finite Element Code
 *
 *               Copyright (C) 1993 - 2013   Borek Patzak
 *
 *
 *
 *       Czech Technical University, Faculty of Civil Engineering,
 *   Department of Structural Mechanics, 166 29 Prague, Czech Republic
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef quasicontinuumvtkxmlexportmodule_h
#define quasicontinuumvtkxmlexportmodule_h

#include "vtkxmlexportmodule.h"
//#include "exportmodule.h"
#include "intarray.h"
#include "nodalrecoverymodel.h"
#include "interface.h"
#include "internalstatevaluetype.h"
#include "integrationrule.h"
#include "xfem/xfemmanager.h"


#ifdef __VTK_MODULE
 #include <vtkUnstructuredGrid.h>
 #include <vtkSmartPointer.h>
#endif

#include <string>
#include <list>

///@name Input fields for QcVTK XML export module
//@{
#define _IFT_QuasicontinuumVTKXMLExportModule_Name "qcvtkxml"
#define _IFT_QuasicontinuumVTKXMLExportModule_ExportDeactivatedElements "expdeaktelem"
//@}

namespace oofem {
class OOFEM_EXPORT QuasicontinuumVTKXMLExportModule : public VTKXMLExportModule
{
protected:
    int deactivatedElementsExportFlag;

    /// List of InternalStateType values, identifying the selected vars for export.
    IntArray internalVarsToExport;
    /// List of primary unknowns to export.
    IntArray primaryVarsToExport;
    /// List of cell data to export.
    IntArray cellVarsToExport;
    
public:
    /// Constructor. Creates empty Output Manager. By default all components are selected.
    QuasicontinuumVTKXMLExportModule(int n, EngngModel * e);
    /// Destructor
    virtual ~QuasicontinuumVTKXMLExportModule();

    virtual IRResultType initializeFrom(InputRecord *ir);

 protected:    
    //
    //  Exports single internal variable by smoothing.
    //
    virtual void setupVTKPiece(VTKPiece &vtkPiece, TimeStep *tStep, int region);
    /**
     * Assembles the region node map. Also computes the total number of nodes in region.
     * The region are numbered starting from offset+1.
     * If mode == 0 then regionNodalNumbers is array with mapping from global numbering to local region numbering.
     * The i-th value contains the corresponding local region number (or zero, if global number is not in region).
     * If mode == 1 then regionNodalNumbers is array with mapping from local to global numbering.
     * The i-th value contains the corresponding global node number.
     */
    virtual int initRegionNodeNumbering(IntArray &mapG2L, IntArray &mapL2G,
                                int &regionDofMans, 
				int &totalcells,
                                Domain *domain, TimeStep *tStep, int reg);
};
} // end namespace oofem
#endif // quasicontinuumvtkxmlexportmodule_h
