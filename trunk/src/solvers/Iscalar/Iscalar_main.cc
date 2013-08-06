/* Tarang-2
 *
 * Copyright (C) 2008, 2009  Mahendra K. Verma
 *
 * Mahendra K. Verma
 * Indian Institute of Technology, Kanpur-208016
 * UP, India
 *
 * mkv@iitk.ac.in
 *
 * This file is part of Tarang-2 .
 *
 * Tarang-2 is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * Tarang-2 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with Tarang-2; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, U
 */

/*! \file Ifluid_main.cc 
 * 
 * @brief Main program executing fluid turbulence
 *
 * @author  M. K. Verma, A. G. Chatterjee
 * @date 2 October 2008
 * 
 * @bugs  No known bug
 */ 


 #include "Iscalar_main.h"


//****************************************************************************************					
 
int Iscalar_main()
{
    // Set Dissipation coefficients
    if (global.program.kind == "SCALAR_INCOMPRESS") {
        // Dissipation coefficients assigned in global
        ;
    }
    
	else if (global.program.kind == "RBC") {
        // For RBC assign from the RBC parameters
        if (global.PHYSICS.Pr_option == "PRZERO") {
            global.field.diss_coefficients[0] = 1.0;
            global.field.diss_coefficients[1] = 0.0;
        }
        
        else if (global.PHYSICS.Pr_option == "PRLARGE") {
            if (global.PHYSICS.Uscaling == "USMALL") {
                global.field.diss_coefficients[0] = global.PHYSICS.Prandtl;              //  Coeff of grad^2 u
                global.field.diss_coefficients[1]  = 1.0;			// Coeff of grad^2 T
            }
            else if (global.PHYSICS.Uscaling == "ULARGE") {
                global.field.diss_coefficients[0] = sqrt(global.PHYSICS.Prandtl/global.PHYSICS.Rayleigh);             
                global.field.diss_coefficients[1]  = 1/sqrt(global.PHYSICS.Prandtl*global.PHYSICS.Rayleigh);			
            }
        }
        
        else if (global.PHYSICS.Pr_option == "PRSMALL")  {
            if (global.PHYSICS.Uscaling == "USMALL")  {
                global.field.diss_coefficients[0] = 1.0;             
                global.field.diss_coefficients[1]  = 1/global.PHYSICS.Prandtl;			
            }
            else if (global.PHYSICS.Uscaling == "ULARGE")  {
                global.field.diss_coefficients[0] = sqrt(global.PHYSICS.Prandtl/global.PHYSICS.Rayleigh);             
                global.field.diss_coefficients[1]  = 1/sqrt(global.PHYSICS.Prandtl*global.PHYSICS.Rayleigh);			
            }
        }
        
        else if (global.PHYSICS.Pr_option == "PRINFTY")  {
            if (global.PHYSICS.Uscaling == "USMALL")  {
                global.field.diss_coefficients[0] = global.PHYSICS.Prandtl;             
                global.field.diss_coefficients[1]  = 1.0;			
            }
            else if (global.PHYSICS.Uscaling == "ULARGE")  {
                global.field.diss_coefficients[0] = 1/sqrt(global.PHYSICS.Rayleigh);	             
                global.field.diss_coefficients[1]  = 1/sqrt(global.PHYSICS.Rayleigh);
            }
        }
    }
    
	// ITERATION...
	if (global.program.iter_or_diag == "ITERATION") {
        
        fluidIO_incompress.Open_files();
        fluidIO_incompress.Init_energy_transfer();
        
        FluidVF  U(global.field.diss_coefficients[0], global.field.hyper_diss_coefficients[0], global.field.hyper_diss_exponents[0], global.force.U_switch, "U");
        
      FluidSF T(global.field.diss_coefficients[1], global.field.hyper_diss_coefficients[1], global.field.hyper_diss_exponents[1], global.force.T_switch, "T"); 
        
		Pressure P;

		FORCE  Force;

		Time_advance_incompress  time_advance_incompress;
		// EnergyTr	energytr;
        
		fluidIO_incompress.Read_init_cond(U, T);
		
		cout << "Init energy: " << endl;
		if (basis_type.find("Ch") != string::npos)
			fluidIO_incompress.Output_cout_real_space(U,T);
		
		
	/*	cout << "After reading the INIT COND " << endl;
        cout << "V1" << endl; universal->Print_large_Fourier_elements(U.cvf.V1);
        cout << "V2" << endl; universal->Print_large_Fourier_elements(U.cvf.V2);
        cout << "V3" << endl; universal->Print_large_Fourier_elements(U.cvf.V3);
        cout << "F" << endl;universal->Print_large_Fourier_elements(T.csf.F);
		
        
        cout << "Values at the boundaries: " << endl;
        Array<complx,2> v_plus(local_Ny, local_Nz), v_minus(local_Ny, local_Nz);
        
        time_advance_incompress.Compute_fn_at_boundary(U.cvf.V1, v_plus, v_minus);
        cout << "V1(+1), V1(-1) = " << sum(abs(v_plus)) << " " << sum(abs(v_minus)) << endl;
        
        time_advance_incompress.Compute_fn_at_boundary(U.cvf.V2, v_plus, v_minus);
        cout << "V2(+1), V2(-1) = " << sum(abs(v_plus)) << " " << sum(abs(v_minus)) << endl;
        
        time_advance_incompress.Compute_fn_at_boundary(U.cvf.V3, v_plus, v_minus);
        cout << "V3(+1), V3(-1) = " << sum(abs(v_plus)) << " " << sum(abs(v_minus)) << endl;
        
        time_advance_incompress.Compute_fn_at_boundary(T.csf.F, v_plus, v_minus);
        cout << "F(+1), F(-1) = " << sum(abs(v_plus))  << " " << sum(abs(v_minus)) << endl; */
        
        DP total_abs_div;
        U.Compute_divergence_field(global.temp_array.X2, total_abs_div, true);
        // true mean print nonzero div modes
        if (total_abs_div > MYEPS2) {
            cout << "abs(sum(Divergence)) of the initial field U = " << total_abs_div << "is large. " << '\n' << "Therefore exiting the program." << endl;
            return (0);
        } 
        

		fluidIO_incompress.Output_all_inloop(U, T, P);  // for initial cond
		
        //*******************
		if (my_id == master_id)  
			cout << endl << "STARTING THE SIMULATION NOW" << endl;

		int  iter=0;  // iterations 

		global.time.now = global.time.init;
			//		fluidIO_incompress.Output_field_k(U, T);
	
		if (basis_type=="ChFF") {
			time_advance_incompress.Compute_homgeneous_soln_influence_matrix(U,P);
		//	cout << "Influence matrix computed " << global.temp_array.influence_matrix << endl;
		}
        
 //       cout << "P+" << global.temp_array.pressure_plus << endl;
   //     cout << "V1+" << global.temp_array.vx_plus << endl;
        
//		return 0;
//        cout << "Influence matrix computed " << global.temp_array.influence_matrix << endl;
		
		do 	{
			global.time.dt_computation_done = false;
			global.io.output_real_field_done = false;
			global.io.output_field_k_done = false;
			global.io.output_pressure_spectrum_done = false;
			global.io.output_pressure_done = false;
            global.io.output_nlin_magnitude_done = false;
			
			iter++;

			time_advance_incompress.Time_advance_step(U, T, P, Force);

			U.Compute_divergence_field(global.temp_array.X2, total_abs_div, true);
            // true mean print nonzero div modes
            if (total_abs_div > MYEPS2) {
                cout << "abs(sum(Divergence)) of  U = " << total_abs_div << "is large. " << '\n' << "Therefore exiting the program." << endl;
                return (0); 
            }
            
			fluidIO_incompress.Output_all_inloop(U, T, P);
			
            if ( (my_id == 0) && (isnan(U.cvf.total_energy) || (isnan(T.csf.total_energy))))  {
                cout << "ERROR: Numerical Overflow " << endl;  break;
            }
			
		} 
		while ( (global.time.now < global.time.final) && (clock() < global.time.job_time_final) );
		
		if (basis_type.find("Ch") != string::npos)
			fluidIO_incompress.Output_cout_real_space(U,T);
        else 
			fluidIO_incompress.Output_last(U, T, P);
		
		fluidIO_incompress.Close_files();
	}
	
	
    //*******************
	// DIAGNOSTICS
	else if (global.program.iter_or_diag == "DIAGNOSTICS") {
        string filename;
        
        FluidVF  U(global.field.diss_coefficients[0], global.field.hyper_diss_coefficients[0], global.field.hyper_diss_exponents[0], global.force.U_switch, "U");
        
        FluidSF T(global.field.diss_coefficients[1], global.field.hyper_diss_coefficients[1], global.field.hyper_diss_exponents[1], global.force.T_switch, "T");
        
        Pressure P;
        
        fluidIO_incompress.Init_energy_transfer();
		fluidIO_incompress.Read_init_cond(U, T);
        
		int i=0;
		while (i < global.io.diagnostic_procedures.size()) {
			switch (global.io.diagnostic_procedures[i])  {
                    
                case (0) : {
                    filename = "/out/glob.d";
                    filename = global.io.data_dir+ filename;
                    fluidIO_incompress.global_file.open(filename.c_str());
                    if (!fluidIO_incompress.global_file.is_open())
                        cout << "UNABLE TO OPEN FILE global_file (glob.d) " << endl;
                    fluidIO_incompress.Output_global(U, T);
                    fluidIO_incompress.Close_files();
                    break;
                }
                    
				case (1) : {
                    filename = "/out/spectrum.d";
                    filename = global.io.data_dir+ filename;
                    fluidIO_incompress.spectrum_file.open(filename.c_str());
                    fluidIO_incompress.Output_shell_spectrum(U, T);
                    fluidIO_incompress.Close_files();
                    break;
                }
                    
				case (2) : {
                    filename = "/out/ring_spectrum.d";
                    filename = global.io.data_dir+ filename;
                    fluidIO_incompress.ring_spectrum_file.open(filename.c_str());
                    fluidIO_incompress.Output_ring_spectrum(U, T);
                    fluidIO_incompress.Close_files();
                    break;
                }
                    
                    
				case (3) : {
                    filename = "/out/cyl_ring_spectrum.d";
                    filename = global.io.data_dir+ filename;
                    fluidIO_incompress.cylindrical_ring_spectrum_file.open(filename.c_str());
                    fluidIO_incompress.Output_cylindrical_ring_spectrum(U, T);
                    fluidIO_incompress.Close_files();
                    break;
                }
                    
				case (4) : {
                    filename = "/out/flux.d";
                    filename = global.io.data_dir+ filename;
                    fluidIO_incompress.flux_file.open(filename.c_str());
                    fluidIO_incompress.Output_flux(U, T, P);
                    fluidIO_incompress.Close_files();
                    break;
                }
                    
                    // force reqd for force-feed calculations
				case (5) : {
                    filename = "/out/shell_to_shell.d";
                    filename = global.io.data_dir+ filename;
                    fluidIO_incompress.shell_to_shell_file.open(filename.c_str());
                    fluidIO_incompress.Output_shell_to_shell(U, T, P);
                    fluidIO_incompress.Close_files();
                    break;
                }
                    
                case (6) : {
                    filename = "/out/ring_to_ring.d";
                    filename = global.io.data_dir+ filename;
                    fluidIO_incompress.ring_to_ring_file.open(filename.c_str());
                    fluidIO_incompress.Output_ring_to_ring(U, T, P);
                    fluidIO_incompress.Close_files();
                    break;
                }
                    
                    
				case (7) : {
                    filename = "/out/cylindrical_ring_to_ring.d";
                    filename = global.io.data_dir+ filename;
                    fluidIO_incompress.cylindrical_ring_to_ring_file.open(filename.c_str());
                    fluidIO_incompress.Output_cylindrical_ring_to_ring(U, T, P);
                    fluidIO_incompress.Close_files();
                    break;
                }
                    //		case (7) : fluidIO_incompress.Output_structure_fn(U);  break;
                    //		case (8) : fluidIO_incompress.Output_planar_structure_fn(U);  break;
				case (10) : {
                    filename = "/out/field_k_out_"+To_string(my_id)+".d";
                    filename = global.io.data_dir+ filename;
                    fluidIO_incompress.field_k_out_file.open(filename.c_str());
                    fluidIO_incompress.Output_field_k(U, T);
                    fluidIO_incompress.Close_files();
                    break;
                }
                    
				case (11) : {
                    filename = "/out/field_r_out_"+To_string(my_id)+".d";
                    filename = global.io.data_dir+ filename;
                    fluidIO_incompress.field_r_out_file.open(filename.c_str());
                    fluidIO_incompress.Output_field_r(U, T);
                    fluidIO_incompress.Close_files();
                    break;
                }
                    
				case (13) : {
                    filename = "/out/realfield_out.d";
                    filename = global.io.data_dir+ filename;
                    fluidIO_incompress.realfield_out_file.open(filename.c_str());
                    fluidIO_incompress.Output_real_field(U, T);
                    fluidIO_incompress.Close_files();
                    break;
                }
				case (14) : {
                    filename = "/out/field_out_reduced.d";
                    filename = global.io.data_dir+ filename;
                    fluidIO_incompress.field_out_reduced_file.open(filename.c_str());
                    fluidIO_incompress.Output_reduced_complex_field(U, T);
                    fluidIO_incompress.Close_files();
                    break;
                }
                    
			}
			
			i++;
		}	

	} 
  
	return(1);
  
} 


//********************************** End of Ifluid_main.cc ************************************	


