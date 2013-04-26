#include <winstd.H>

#include <NavierStokes.H>
#include <NS_error_F.H>

using std::string;

void
NavierStokes::error_setup()
{
    // The lines below define routines to be called to tag cells for error
    // estimation -- the arguments of each "add" call are:
    //   1. Name of variable (state variable or derived quantity) which will be
    //      passed into the Fortran subroutine.
    //   2. Number of ghost cells each array needs in each call to the Fortran
    //      subroutine.
    //   3. Type of Fortran subroutine -- this determines the argument list of
    //      the Fortran subroutine.  These types are pre-defined.
    //   4. Name of Fortran subroutine.

    //
    // **************  DEFINE ERROR ESTIMATION QUANTITIES  *************
    //
    if (do_density_ref)   {
        err_list.add("density",  1, ErrorRec::Special, 
                     BL_FORT_PROC_CALL(FORT_DENERROR,fort_denerror));
        if (ParallelDescriptor::IOProcessor()) std::cout << "Refining on DENSITY" << std::endl;
    }
    if (do_tracer_ref)    {
        err_list.add("tracer",   1, ErrorRec::Special, 
                     BL_FORT_PROC_CALL(FORT_ADVERROR,fort_adverror));
        if (ParallelDescriptor::IOProcessor()) std::cout << "Refining on TRACER" << std::endl;
    }
    if (do_tracer2_ref)    {
	err_list.add("tracer2",   1, ErrorRec::Special, 
                     BL_FORT_PROC_CALL(FORT_ADV2ERROR,fort_adv2error));
	if (ParallelDescriptor::IOProcessor()) std::cout << "Refining on TRACER2" << std::endl;
    }
    if (do_vorticity_ref) {
        err_list.add("mag_vort", 0, ErrorRec::Special, 
                     BL_FORT_PROC_CALL(FORT_MVERROR,fort_mverror));
        if (ParallelDescriptor::IOProcessor()) std::cout << "Refining on MAG_VORT" << std::endl;
    }
}
