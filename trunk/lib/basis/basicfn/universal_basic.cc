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

/*! \file four_basic.cc
 * 
 * @sa four_basic.h
 * 
 * @author  M. K. Verma
 * @version 4.0 MPI
 * @date	22/08/2008
 * @bug		No known bugs
 */ 

#include "universal.h"
#include "Global_extern_vars.h"
#include "basicfn_inline.h"


/**********************************************************************************************

	-- Number of modes included inside shell (inner_radius, outer_radius]
	-- also count the complex conj
	
***********************************************************************************************/


int Universal::Get_number_modes_in_shell(DP inner_radius, DP outer_radius)
{
    
	int kx_max, ky_max, kz_max;
	
	kx_max = (int) ceil(outer_radius/kfactor[1]);
	
	if (Ny > 1)
		ky_max = (int) ceil(outer_radius/kfactor[2]);
	else
		ky_max = 0.0;
    
    kz_max = (int) ceil(outer_radius/kfactor[3]);
	
	int count = 0;
	DP  Kmag;
	

	for (int kx = -kx_max; kx <= kx_max; kx++)
		for (int ky = -ky_max; ky <= ky_max; ky++)  
			for (int kz = 0; kz <= kz_max; kz++) {
                Kmag = sqrt(pow2(kx*kfactor[1]) + pow2(ky*kfactor[2]) + pow2(kz*kfactor[3]));
				
				if (( Kmag > inner_radius) && ( Kmag <= outer_radius))	{
					if (kz == 0)
						count++;
					else 
						count = count + 2;
				}		
			}
	
	return count;		

}

//*********************************************************************************************

void Universal::Print_large_Fourier_elements(Array<complx,3> A)
{
    #pragma omp parallel for
    for (int ly=0; ly<A.extent(0); ly++) 
        for (int lz=0; lz<A.extent(1); lz++) 
	       for (int lx=0; lx<A.extent(2); lx++) 
				if (abs(A(ly, lz, lx)) > MYEPS2) {
					cout << "my_id = " << my_id <<  " vect(k) = ( " << Get_kx(lx) << "," << Get_ky(ly) << "," << Get_kz(lz) <<");  Array(k) = " << A(ly, lz, lx) << '\n';
				}
	
    cout << endl;
}

/**********************************************************************************************

       		Replaces A(k) by A(k)*K^2.

***********************************************************************************************/


void Universal::Array_mult_ksqr(Array<complx,3> A)
{
    DP Kysqr;    // Ky^2
	DP Kyzsqr;
    DP Ksqr;
	
    #pragma omp parallel for private(Kysqr,Kyzsqr,Ksqr) 
	for (int ly=0; ly<A.extent(0); ly++) {
		Kysqr = my_pow(Get_ky(ly)*kfactor[2],2);	
		
        for (int lz=0; lz<A.extent(1); lz++) {
            Kyzsqr = Kysqr + my_pow(Get_kz(lz)*kfactor[3],2);
            for (int lx=0; lx<A.extent(2); lx++) {
                Ksqr= Kyzsqr + my_pow(Get_kx(lx)*kfactor[1],2);

		      A(ly, lz, lx) *= Ksqr; 
          }
        }
    }
}


/**********************************************************************************************

	Replaces A(k) by A(k)/K^2 with K^2 = sum_i [ki*kfactor(i)]^2 ; A(0)=0

***********************************************************************************************/



void Universal::Array_divide_ksqr(Array<complx,3> A)
{
    DP Kysqr;    // Ky^2
    DP Kyzsqr;
    DP Ksqr;
    
    #pragma omp parallel for private(Kysqr,Kyzsqr,Ksqr) 
    for (int ly=0; ly<A.extent(0); ly++) {
        Kysqr = my_pow(Get_ky(ly)*kfactor[2],2);    
        
        for (int lz=0; lz<A.extent(1); lz++) {
            Kyzsqr = Kysqr + my_pow(Get_kz(lz)*kfactor[3],2);
            
            for (int lx=0; lx<A.extent(2); lx++) {
                Ksqr= Kyzsqr + my_pow(Get_kx(lx)*kfactor[1],2);
                A(ly, lz, lx) /= Ksqr; 
            }
        }
    }  
	   
	// To avoid division by zero
	if (master)
		A(0,0,0) = 0.0;   
}


/**********************************************************************************************

	Replaces A(k) by A(k)*exp(factor*K^2).

***********************************************************************************************/


void Universal::Array_exp_ksqr(Array<complx,3> A, DP factor)
{	
    
	DP Kysqr;    // Ky^2
	DP Kyzsqr;
	DP Ksqr;
	
	#pragma omp parallel for private(Kysqr,Kyzsqr,Ksqr) 
	for (int ly=0; ly<A.extent(0); ly++) {
		Kysqr = my_pow(Get_ky(ly)*kfactor[2],2);    
		
		for (int lz=0; lz<A.extent(1); lz++) {
			Kyzsqr = Kysqr + my_pow(Get_kz(lz)*kfactor[3],2);
			
			for (int lx=0; lx<A.extent(2); lx++) {
				Ksqr= Kyzsqr + my_pow(Get_kx(lx)*kfactor[1],2);

			  A(ly, lz, lx) *= exp(factor*Ksqr); 
		  }
		}
	}  
}



/**********************************************************************************************

	Replaces A(k) by A(k)*[ exp( factor*K^2+hyper_factor*K^4 )]

***********************************************************************************************/

void Universal::Array_exp_ksqr(Array<complx,3> A, DP factor, DP hyper_factor, int hyper_exponent)
{

	DP Kysqr;    // Ky^2
	DP Kyzsqr;
	DP Ksqr;
	DP Kpownm2;	// K^{q-2} where q = hyper_exponent
	
	for (int ly=0; ly<A.extent(0); ly++) {
		Kysqr = my_pow(Get_ky(ly)*kfactor[2],2);
		
		for (int lz=0; lz<A.extent(1); lz++) {
			Kyzsqr = Kysqr + my_pow(Get_kz(lz)*kfactor[3],2);
			
			for (int lx=0; lx<A.extent(2); lx++) {
				Ksqr= Kyzsqr + my_pow(Get_kx(lx)*kfactor[1],2);
				
				if (hyper_exponent == 4)
					Kpownm2 = Ksqr;
				else
					Kpownm2 = my_pow(Ksqr,(hyper_exponent-2)/2);
				
				A(ly, lz, lx) *= exp((factor+hyper_factor*Kpownm2)* Ksqr);
			}
		}
	}
}
 


/**********************************************************************************************

	Replaces A(k) by A(k)*(V0.K)^2 / K^2.

***********************************************************************************************/


void Universal::Array_mult_V0_khat_sqr(Array<complx,3> A, TinyVector<DP,3> V0)
{
    DP Kx, Ky, Kz;
    DP Kysqr;    // Ky^2
    DP Kyzsqr;
    DP Ksqr;
  
	DP V0x = V0(0);
	DP V0y = V0(1);
	DP V0z = V0(2);
    
    for (int ly=0; ly<A.extent(0); ly++) {
        Ky = Get_ky(ly)*kfactor[2];
        Kysqr = my_pow(Ky,2);
        
        for (int lz=0; lz<A.extent(1); lz++) {
            Kz = Get_kz(lz)*kfactor[3];
            Kyzsqr = Kysqr + my_pow(Kz,2);
            
            for (int lx=0; lx<A.extent(2); lx++) {
                Kx = Get_kx(lx)*kfactor[1];
                Ksqr = Kyzsqr + my_pow(Kx,2);
                A(ly, lz, lx) *= my_pow(V0x*Kx+V0y*Ky+V0z*Kz, 2)/Ksqr;
            }
        }
    }
	
    // To avoid division by zero
	if (my_id == master_id)
		A(0,0,0) = 0.0;
}

//********************************************************************************************* 


/** @brief Compute divergence of VF \f$ \vec{V} \f$.
 *
 *	@note	Divergence is stored in div
 *
 *  @return  \f$ *F = \mathcal{F}(D_i A_i) \f$. 
 */
void Universal::Compute_divergence(Array<complx,3> Ax, Array<complx,3> Ay, Array<complx,3> Az, Array<complx,3> div, string field_or_nlin, DP &total_abs_div, bool print_switch)
{	
	global.program.sincostr_switch = sincostr_switch_Vx;
    Xderiv(Ax, div);

	global.program.sincostr_switch = sincostr_switch_Vy;
	Add_Yderiv(Ay, div);
	
	global.program.sincostr_switch = sincostr_switch_Vz;
	Add_Zderiv(Az, div);
	
    if (field_or_nlin == "field") {
        total_abs_div = sqrt(Array_sqr(div));
        
        if ((print_switch) && (total_abs_div > MYEPS2)) {
            cout << "NON-ZERO DIVERGENCE for the following modes:"  << endl;
            Print_large_Fourier_elements(div);
        }
    }
}


//********************************************************************************************* 


// kz=0 is already filled.

void Universal::Fill_Vz(Array<complx,3> Ax, Array<complx,3> Ay, Array<complx,3> Az)
{
    if (global.io.input_vx_vy_switch && global.field.incompressible) {
		int kx, ky, kz;
		complx vz;
        
        #pragma omp parallel for
		for (int ly=0; ly<Ax.extent(0); ly++)
            for (int lz=1; lz<Ax.extent(1); lz++)
        		for (int lx=0; lx<Ax.extent(2); lx++){
					kx = Get_kx(lx);
					ky = Get_ky(ly);
					kz = Get_kz(lz);
                    
					Last_component(kx, ky, kz, Ax(ly,lz,lx), Ay(ly,lz,lx), vz);
                    
					Az(ly,lz,lx) = vz;
				}
	}
}

//*********************************************************************************************


void Universal::Zero_modes(Array<complx,3> Ax, Array<complx,3> Ay, Array<complx,3> Az)
{
    // Do nothing
}

void Universal::Zero_modes(Array<complx,3> F)
{
    // Do nothing
}


//*****************************  End of four_basic.cc **************************