/*
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
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */


#include "spectral_plan_slab_3d.h"

class SSS_slab_Alltoall_3D : public SpectralPlan_Slab_3D {
private:
	
	FFTW_PLAN plan_sintr_x, plan_costr_x;
	FFTW_PLAN plan_isintr_x, plan_icostr_x;

	FFTW_PLAN plan_sintr_y, plan_costr_y;
	FFTW_PLAN plan_isintr_y, plan_icostr_y;

	FFTW_PLAN plan_sintr_z, plan_costr_z;
	FFTW_PLAN plan_isintr_z, plan_icostr_z;


	void Init_array();

	void Normalize(Array<complx,3> A);

	void SinCostr_x(char sincostr_option, Array<DP,3> Ar);
	void ISinCostr_x(char sincostr_option, Array<DP,3> Ar);
	void SinCostr_y(char sincostr_option, Array<complx,3> Ar);
	void ISinCostr_y(char sincostr_option, Array<complx,3> Ar);
	void SinCostr_z(char sincostr_option, Array<complx,3> Ar);
	void ISinCostr_z(char sincostr_option, Array<complx,3> Ar);


public:

	SSS_slab_Alltoall_3D(int my_id, int numprocs, int num_iter, int Nx, int Ny, int Nz);

	void Forward_transform(string sincostr_switch, Array<DP,3> Ar, Array<complx,3> A);
	void Inverse_transform(string sincostr_switch, Array<complx,3> A, Array<DP,3> Ar);

	void Transpose(Array<DP,3> Ar, Array<complx,3> A);
	void Transpose(Array<complx,3> A, Array<DP,3> Ar);
};

