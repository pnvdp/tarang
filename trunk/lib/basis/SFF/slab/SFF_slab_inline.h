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

/*! \file sincosfour_inline.h 
 * 
 * @brief Inline functions to compute array indices \f$ \vec{i} \f$ given wavenumber  
 *		\f$ \vec{k} \f$ and viceversa.
 *		Also contains other useful functions like Kmagnitude, Max radius etc.
 *
 * Grid wavenumber \f$ \vec{k} \f$ is integer, that can be computed using the grid index 
 *		\f$ \vec{i} \f$. Actual wavenumber \f$ \vec{K} \f$ is computed from the grid wavenumber 
 *		\f$ \vec{k} \f$ using \f$ K_i = k_i * f_i \f$  where \f$ f_i \f$ is the kfactor[i]. 
 *
 * lx, ly, lz = local array indices. <BR>
 * i1, i2, i3 = global or total array indices.
 *
 * For shell/ring energy spectrum \f$ E(k) \f$, the wavenumber is either actual wavenumber 
 *		or gridwavenumber depending on the switch WAVENOACTUAL or WAVENOGRID.
 * 
 * @author  M. K. Verma
 * @version 4.0 Parallel
 * @date	August 2008
 * @bug		No known bugs
 */


#include "SFF_slab.h"


//*********************************************************************************************

/*! @brief	Get grid waveno kx given first local array index lx.
 * 
 *	i1= local_Nx_start + lx.
 * 
 * \param lx  first local index of an array
 * \return kx corresponding to lx
 */
inline int SFF_SLAB::Get_kx(int lx) { return  (local_Nx_start + lx); }


/*! @brief	Get local array index lx given grid waveno kx.
 * 
 *	lx= kx - local_Nx_start.
 * 
 * \param	kx  grid wavenumber along x
 * \return	lx  local array index along x
 */
inline int SFF_SLAB::Get_lx(int kx)  { return  (kx-local_Nx_start); } 

inline int SFF_SLAB::Get_ix(int kx) {return  kx;}

/*! @brief	Get grid waveno ky given first local array index ly.
 * 
 *  If ly<=N2/2, k2=ly; else ky=ly-N2.
 * 
 * \param ly  second local index of an array
 * \return kx corresponding to lx
 */
inline int SFF_SLAB::Get_ky(int ly) { return  (ly <= Ny/2) ? ly : (ly-Ny); }


/*! @brief	Get local array index ly given grid waveno ky.
 * 
 *  If ky>=0, ly=ky; else ly=ky+N2.
 * 
 * \param	ky  grid wavenumber along y
 * \return	ly  local array index along y
 */
inline int SFF_SLAB::Get_ly(int ky) { return  (ky >= 0) ? ky : (ky + Ny); } 

inline int SFF_SLAB::Get_iy(int ky) { return  (ky >= 0) ? ky : (ky + Ny); }

inline int SFF_SLAB::Get_lz(int kz)  { return kz; }

inline int SFF_SLAB::Get_iz(int kz)  { return kz; }
	
// local_Nz_start = 0 	
inline int SFF_SLAB::Get_kz(int lz)  { return lz; } 

inline bool SFF_SLAB::Probe_in_me(int kx, int ky, int kz) 
{
	int lx = Get_lx(kx);
	return ((lx >= 0) && (lx < local_Nx));
}

inline complx SFF_SLAB::Get_spectral_field(int kx, int ky, int kz, Array<complx,3> A)
{ 
	int lx = Get_lx(kx);
    int ly = Get_ly(ky);
	
	if  ((lx >= 0) && (lx < local_Nx))
		return A(lx, ly, kz);

	return complx(0,0);
}

inline TinyVector<complx,3> SFF_SLAB::Get_spectral_field(int kx, int ky, int kz, Array<complx,3> Ax, Array<complx,3> Ay, Array<complx,3> Az)
{
	
	int lx = Get_lx(kx);
    int ly = Get_ly(ky);
	
	if  ((lx >= 0) && (lx < local_Nx))
		return TinyVector<complx,3>(Ax(lx, ly, kz), Ay(lx, ly, kz), Az(lx, ly, kz));

	return TinyVector<complx,3>(0,0,0);
}

/*
inline void SFF_SLAB::Get_spectral_field(int kx, int ky, int kz, Array<complx,3> A,DP &field)
{ 
	cout << "MYERROR: SFF_SLAB::Get_spectral_field(); Use complex data type " << endl; 
}

inline void SFF_SLAB::Get_spectral_field(int kx, int ky, int kz, Array<complx,3> Ax, Array<complx,3> Ay, Array<complx,3> Az, TinyVector<DP,3> &V)
{
	
	cout << "MYERROR: SFF_SLAB::Get_spectral_field(); Use complex data type " << endl;
}*/

	// Assign..

inline void SFF_SLAB::Assign_spectral_field(int kx, int ky, int kz, Array<complx,3> A, complx field)
{ 
	int lx = Get_lx(kx);
    int ly = Get_ly(ky);
	
	if ((lx >= 0) && (lx < local_Nx))
		A(lx, ly, kz) = field;
}


inline void SFF_SLAB::Assign_spectral_field(int kx, int ky, int kz, Array<complx,3> Ax, Array<complx,3> Ay, Array<complx,3> Az, TinyVector<complx,3> V)
{
	
	int lx = Get_lx(kx);
    int ly = Get_ly(ky);

	if ((lx >= 0) && (lx < local_Nx)) {
		Ax(lx, ly, kz) = V(0);
		Ay(lx, ly, kz) = V(1);
		Az(lx, ly, kz) = V(2);
	}
}


inline void SFF_SLAB::Assign_spectral_field(int kx, int ky, int kz, Array<complx,3> A,DP field)
{ 
	cout << "MYERROR: SFF_SLAB:Assign_spectral_field(); Use complex data type " << endl; 
}

inline void SFF_SLAB::Assign_spectral_field(int kx, int ky, int kz, Array<complx,3> Ax, Array<complx,3> Ay, Array<complx,3> Az, TinyVector<DP,3> V)
{
	
	cout << "MYERROR: SFF_SLAB::Assign_spectral_field(); Use complex data type " << endl;
}

inline void SFF_SLAB::Add_spectral_field(int kx, int ky, int kz, Array<complx,3> A, complx field)
{ 
	int lx = Get_lx(kx);
    int ly = Get_ly(ky);
	
	if ((lx >= 0) && (lx < local_Nx))
		A(lx, ly, kz) += field;
}


inline void SFF_SLAB::Add_spectral_field(int kx, int ky, int kz, Array<complx,3> Ax, Array<complx,3> Ay, Array<complx,3> Az, TinyVector<complx,3> V)
{
	
	int lx = Get_lx(kx);
    int ly = Get_ly(ky);
	
	if ((lx >= 0) && (lx < local_Nx)) {
		Ax(lx, ly, kz) += V(0);
		Ay(lx, ly, kz) += V(1);
		Az(lx, ly, kz) += V(2);
	}
}

inline void SFF_SLAB::Add_spectral_field(int kx, int ky, int kz, Array<complx,3> A,DP field)
{ 
	cout << "MYERROR: SFF_SLAB:Assign_spectral_field(); Use complex data type " << endl; 
}

inline void SFF_SLAB::Add_spectral_field(int kx, int ky, int kz, Array<complx,3> Ax, Array<complx,3> Ay, Array<complx,3> Az, TinyVector<DP,3> V)
{
	
	cout << "MYERROR: SFF_SLAB::Assign_spectral_field(); Use complex data type " << endl;
}


	// local..


inline complx SFF_SLAB::Get_local_spectral_field(int lx, int ly, int lz, Array<complx,3> A)
{ 
	 return A(lx, ly, lz);
}

inline TinyVector<complx,3> SFF_SLAB::Get_local_spectral_field(int lx, int ly, int lz, Array<complx,3> Ax, Array<complx,3> Ay, Array<complx,3> Az)
{
	
	return TinyVector<complx,3>(Ax(lx, ly, lz), Ay(lx, ly, lz), Az(lx, ly, lz));
}

/*
inline void SFF_SLAB::Get_local_spectral_field(int lx, int ly, int lz, Array<complx,3> A,DP &field)
{ 
	cout << "MYERROR: SFF_SLAB::Get_local_spectral_field(); Use complex data type " << endl; 
}

inline void SFF_SLAB::Get_local_spectral_field(int lx, int ly, int lz, Array<complx,3> Ax, Array<complx,3> Ay, Array<complx,3> Az, TinyVector<DP,3> &V)
{
	
	cout << "MYERROR: SFF_SLAB::Get_local_spectral_field(); Use complex data type " << endl;
}*/

inline void SFF_SLAB::Assign_local_spectral_field(int lx, int ly, int lz, Array<complx,3> A, complx field)
{ 
	
	if ((lx >= 0) && (lx < local_Nx))
		A(lx, ly, lz) = field;
}


inline void SFF_SLAB::Assign_local_spectral_field(int lx, int ly, int lz, Array<complx,3> Ax, Array<complx,3> Ay, Array<complx,3> Az, TinyVector<complx,3> V)
{
	if ((lx >= 0) && (lx < local_Nx)) {
		Ax(lx, ly, lz) = V(0);
		Ay(lx, ly, lz) = V(1);
		Az(lx, ly, lz) = V(2);
	}
}

inline void SFF_SLAB::Assign_local_spectral_field(int lx, int ly, int lz, Array<complx,3> A,DP field)
{ 
	cout << "MYERROR: SFF_SLAB:Assign_local_spectral_field(); Use complex data type " << endl; 
}

inline void SFF_SLAB::Assign_local_spectral_field(int lx, int ly, int lz, Array<complx,3> Ax, Array<complx,3> Ay, Array<complx,3> Az, TinyVector<DP,3> V)
{
	
	cout << "MYERROR: SFF_SLAB::Assign_local_spectral_field(); Use complex data type " << endl;
}



inline void SFF_SLAB::Add_local_spectral_field(int lx, int ly, int lz, Array<complx,3> A, complx field)
{ 
	
	if ((lx >= 0) && (lx < local_Nx))
		A(lx, ly, lz) += field;
}


inline void SFF_SLAB::Add_local_spectral_field(int lx, int ly, int lz, Array<complx,3> Ax, Array<complx,3> Ay, Array<complx,3> Az, TinyVector<complx,3> V)
{
	if ((lx >= 0) && (lx < local_Nx)) {
		Ax(lx, ly, lz) += V(0);
		Ay(lx, ly, lz) += V(1);
		Az(lx, ly, lz) += V(2);
	}
}

inline void SFF_SLAB::Add_local_spectral_field(int lx, int ly, int lz, Array<complx,3> A,DP field)
{ 
	cout << "MYERROR: SFF_SLAB:Assign_local_spectral_field(); Use complex data type " << endl; 
}

inline void SFF_SLAB::Add_local_spectral_field(int lx, int ly, int lz, Array<complx,3> Ax, Array<complx,3> Ay, Array<complx,3> Az, TinyVector<DP,3> V)
{
	
	cout << "MYERROR: SFF_SLAB::Assign_local_spectral_field(); Use complex data type " << endl;
}

				 
//REAL-SPACE
inline int SFF_SLAB::Get_lx_real_space(int rx) {return  rx;}

inline int SFF_SLAB::Get_ly_real_space(int ry) {return  (ry-local_Ny_start);}

inline int SFF_SLAB::Get_lz_real_space(int rz) {return (rz-2*local_Nz_start);}


inline int SFF_SLAB::Get_rx_real_space(int lx) {return  lx;}

inline int SFF_SLAB::Get_ry_real_space(int ly) {return  (ly+local_Ny_start);}
	
inline int SFF_SLAB::Get_rz_real_space(int lz) {return (lz+2*local_Nz_start);}


inline bool SFF_SLAB::Probe_in_me_real_space(int rx, int ry, int rz) 
{
	if (Ny>1) {
		int ly = Get_ly_real_space(ry);
		return ((ly >= 0) && (ly < local_Ny));
	}
	
	else if (Ny == 1) {
		int lz = Get_lz_real_space(rz);
		return ((lz >= 0) && (lz < 2*local_Nz));
	}

	return false;
}


inline DP SFF_SLAB::Get_real_field(int rx, int ry, int rz, Array<DP,3> A)
{
	if (Probe_in_me_real_space(rx,ry,rz)) {
		int ly = Get_ly_real_space(ry);
		int lz = Get_lz_real_space(rz);
			
		return A(rx, ly, lz);
	}
	return 0;
}

inline TinyVector<DP,3> SFF_SLAB::Get_real_field(int rx, int ry, int rz, Array<DP,3> Ax, Array<DP,3> Ay, Array<DP,3> Az)
{
    if (Probe_in_me_real_space(rx,ry,rz)) {
		int ly = Get_ly_real_space(ry);
		int lz = Get_lz_real_space(rz);
		
		TinyVector<DP,3>(Ax(rx, ly, lz), Ay(rx, ly, lz), Az(rx, ly, lz));
	}
	return TinyVector<DP,3>(0,0,0);
}


inline void SFF_SLAB::Assign_real_field(int rx, int ry, int rz, Array<DP,3> A, DP field)
{	
    if (Probe_in_me_real_space(rx,ry,rz)) {
		int ly = Get_ly_real_space(ry);
		int lz = Get_lz_real_space(rz);
		
		A(rx, ly, lz) = field;
	}
}

inline void SFF_SLAB::Assign_real_field(int rx, int ry, int rz, Array<DP,3> Ax, Array<DP,3> Ay, Array<DP,3> Az, TinyVector<DP,3> V)
{
	if (Probe_in_me_real_space(rx,ry,rz)) {
		int ly = Get_ly_real_space(ry);
		int lz = Get_lz_real_space(rz);
		
		Ax(rx, ly, lz) = V(0);
		Ay(rx, ly, lz) = V(1);
		Az(rx, ly, lz) = V(2);
	}
	else
		cerr << "rx,ry,rz = (" <<rx << ","<< ry << "," << rz << ") not in procid " << my_id << endl;
	
}



/**********************************************************************************************

	Compute Wavenumber

***********************************************************************************************/


inline void SFF_SLAB::Wavenumber(int lx, int ly, int lz, TinyVector<DP,3> &K)
{
	K = Get_kx(lx)*kfactor[1],  Get_ky(ly)*kfactor[2], Get_kz(lz)*kfactor[3];
}


// Complex K; The imaginary part is zero.  Written to use cross function of blitz.
// Omega = cross(V,K).
inline void SFF_SLAB::Wavenumber(int lx, int ly, int lz, TinyVector<complx,3> &K)
{
	K = complx(Get_kx(lx)*kfactor[1], 0.0), complx(Get_ky(ly)*kfactor[2], 0.0), complx(Get_kz(lz)*kfactor[3], 0.0);
}



/**********************************************************************************************

		  If wavenos computed using actual wavenumber:  Ki = Kfactor[i]*grid[i]

***********************************************************************************************/


///  WAVENOACTUAL: \f$ K = \sqrt{K_x^2 + K_y^2 + K_z^2} \f$
inline DP SFF_SLAB::Kmagnitude(int lx, int ly, int lz)
{ 
	if	(global.field.waveno_switch)
		return sqrt( pow2(Get_kx(lx)*kfactor[1]) + pow2(Get_ky(ly)*kfactor[2]) + pow2(Get_kz(lz)*kfactor[3]) ); 
	
	else 
		return sqrt( pow2(Get_kx(lx)) + pow2(Get_ky(ly)) + pow2(Get_kz(lz)) );
}


/// WAVENOACTUAL -- Radius of the smallest sphere that contains the wavenumber K box Ni's. <BR>
/// The range of kx=[0:N1-1];  ki = [-Ni/2+1 : Ni/2] along perp directions.
inline int SFF_SLAB::Min_radius_outside() 
{
	if	(global.field.waveno_switch)
		return (int) ceil(sqrt(  pow2((Nx-1)*kfactor[1]) + pow2(Ny/2 * kfactor[2]) + pow2(Nz/2* kfactor[3]) ));
	
	else 
		return (int) ceil(sqrt(  pow2(Nx-1) + pow2(Ny/2) + pow2(Nz/2) ));
}


/// WAVENOACTUAL -- Radius of the largest sphere that fits inside the wavenumber K box Ni's. <BR>
/// The range of kx=[0:N1-1];  ki = [-Ni/2+1 : Ni/2] along perp directions.
inline int SFF_SLAB::Max_radius_inside() 
{
	int ans = 1;
	DP Kmag;
	
	if	(global.field.waveno_switch) {
		if (Ny > 1) {
			Kmag = min( (Nx-1)*kfactor[1], (Ny/2)*kfactor[2]);
			Kmag = min(Kmag, (Nz/2)*kfactor[3]); 
		} 
		
		else if (Ny == 1)
			Kmag = min((Nx-1)*kfactor[1], (Nz/2)*kfactor[3]);
		
		ans = ((int) Kmag);
	}
	
	else
	{
		if (Ny > 1)  {
			ans = min(Nx-1, Ny/2);
			ans = min(ans, Nz/2);
		}
		
		else if (Ny == 1)
			ans = min(Nx-1, (Nz/2));
	}
	
	return ans;
}		

/*! \brief WAVENOACTUAL -- Returns the approximate number of modes in a wavenumber 
 *			K shell of radius "radius".
 * 
 *  We divide the area in Fourier space by volume of unit lattice \f$ \Pi_i f_i \f$, 
 *			where \f$ f_i \f$ is the factor[i]. In 1D, The area in NOT divided by kfactor.
 *
 * \param  radius
 * \return The number of modes in a shell of radius. In 2D, it is quarter circle (kx, ky>= 0). 
 *			In 3D, it is quarter sphere with (kx,kz>=0).
 */
inline DP SFF_SLAB::Approx_number_modes_in_shell(int radius)
{
    if (global.field.waveno_switch)
        return (4*M_PI*radius*radius)/(kfactor[1]*kfactor[2]*kfactor[3]);	
    
    else 
        return (4*M_PI*radius*radius);
}


//*********************************************************************************************



/*! \brief Returns multiplication factor for computing enregy spectrum etc. 
 *  
 * Modal energy  = \f$ E(k) =  |A(k_x, \vec{k}_{\perp})|^{2} \f$  if  \f$ (k_x > 0) \f$.  <BR>
 * Modal energy  = \f$ E(k) =  |A(0, \vec{k}_{\perp})|^{2}/2 \f$  if  \f$ (k_x = 0) \f$.  <BR>
 * In simulation we double the energy of most of the modes because complex conjugates modes with 
 * -ky are not stored in the simulation.  
 * The modes on the xy-plane are not doubled because their c.c. are already counted.
 * 
 * \param  lx, ly, lz
 * \return Multiplication factor for computing enregy spectrum etc.
 */
inline DP SFF_SLAB::Multiplicity_factor(int lx, int ly, int lz)
{
	DP factor;

	int m = Get_kx(lx);
	int ky = Get_ky(ly);
	
	if (lz > 0)
		if ( m > 0 )
			factor  = 2.0;
		else				// m = 0 plane
			factor = 1.0;
			
	else					// kz = 0 plane
		if (m > 0)
			factor = 1.0;
		else				// kz = 0; m = 0 line
			factor = 0.5;
			
	if ((ky == Ny/2) && (Ny > 1))
		return 2*factor;	// for both ky = Ny/2 and -Ny/2
	else					
		return factor;
}



/**********************************************************************************************

		Modal energy

***********************************************************************************************/
/// Modal energy  = \f$ E(k) =  |A(k_x, \vec{k}_{\perp})|^{2} \f$  if  \f$ (k_x > 0) \f$.  <BR>
/// Modal energy  = \f$ E(k) =  |A(0, \vec{k}_{\perp})|^{2}/2 \f$  if  \f$ (k_x = 0) \f$.  <BR>
inline DP SFF_SLAB::Modal_energy(int lx, int ly, int lz, Array<complx,3> A)
{
	return pow2(abs(A(lx,ly,lz)))/2;	
}



/**********************************************************************************************

	Get Modal helicity for (lx,ly,lz).

***********************************************************************************************/

inline DP SFF_SLAB::Get_Modal_helicity
(
	int lx, int ly, int lz, 
	Array<complx,3> Ax, Array<complx,3> Ay, Array<complx,3> Az
)
{

	TinyVector<DP,3> Vreal, Vimag, VrcrossVi, K;
	
	// -I to convert sin to Fourier basis along x axis
	if ((global.program.sincostr_switch == "SFF") || (global.program.sincostr_switch == "S0F")) {	
		Vreal = real(Ax(lx, ly, lz)*(-I)), real(Ay(lx, ly, lz)), real(Az(lx, ly, lz));
		Vimag = imag(Ax(lx, ly, lz)*(-I)), imag(Ay(lx, ly, lz)), imag(Az(lx, ly, lz));
	}
	
	else if ((global.program.sincostr_switch == "CFF") || (global.program.sincostr_switch == "C0F")) {	
		Vreal = real(Ax(lx, ly, lz)), real(Ay(lx, ly, lz)*(-I)), real(Az(lx, ly, lz)*(-I));
		Vimag = imag(Ax(lx, ly, lz)), imag(Ay(lx, ly, lz)*(-I)), imag(Az(lx, ly, lz)*(-I));
	}
		
	VrcrossVi = cross(Vreal, Vimag);
	Wavenumber(lx, ly, lz, K);
	
	return (dot(K, VrcrossVi));	

}


/**********************************************************************************************

	Compute Modal Vorticity

***********************************************************************************************/


inline void SFF_SLAB::Compute_Modal_vorticity
(
	int lx, int ly, int lz, 
	Array<complx,3> Ax, Array<complx,3> Ay, Array<complx,3> Az, 
	TinyVector<complx,3> &vorticity
)
{
	TinyVector<DP,3> K;
	TinyVector<complx,3> Vi;
	
	// -I to convert sin to Fourier basis along x axis
	if ((global.program.sincostr_switch == "SFF") || (global.program.sincostr_switch == "S0F"))
		Vi = (-I)*Ax(lx, ly, lz), Ay(lx, ly, lz), Az(lx, ly, lz);
	
	else if ((global.program.sincostr_switch == "CFF") || (global.program.sincostr_switch == "C0F"))
		Vi = Ax(lx, ly, lz), (-I)*Ay(lx, ly, lz), (-I)*Az(lx, ly, lz);
	
	Wavenumber(lx, ly, lz, K);
	
	vorticity(0) = I *  (K(1)*Vi(2) - K(2)*Vi(1));
	vorticity(1) = I *  (K(2)*Vi(0) - K(0)*Vi(2));
	vorticity(2) = I *  (K(0)*Vi(1) - K(1)*Vi(0));
}




inline void SFF_SLAB::Compute_Modal_vorticity_y_component
(
    int lx, int ly, int lz, 
    Array<complx,3> Ax, Array<complx,3> Ay, Array<complx,3> Az, 
    complx &vort_y
)
{
	TinyVector<DP,3> K;
	TinyVector<complx,3> Vi;
	
	// -I to convert sin to Fourier basis along x axis
	// We have set Vi(1) = 0 to save time.
	if ((global.program.sincostr_switch == "SFF") || (global.program.sincostr_switch == "S0F"))
		Vi = (-I)*Ax(lx, ly, lz), 0, Az(lx, ly, lz);
	
	else if ((global.program.sincostr_switch == "CFF") || (global.program.sincostr_switch == "C0F"))
		Vi = Ax(lx, ly, lz), 0, (-I)*Az(lx, ly, lz);
	
	Wavenumber(lx, ly, lz, K);
	
	vort_y = I *  (K(2)*Vi(0) - K(0)*Vi(2));
}



//*********************************************************************************************

/// 3D == Anisotropic axis along x1: for anisotropic energy spectrum and 
///			energy transfer calculations,  \f$ K_{||} = K_1 \f$.		
inline DP SFF_SLAB::AnisKpll(int lx, int ly, int lz)
{	
	if (global.field.anisotropy_dirn == 1)
		return (Get_kx(lx)*kfactor[1]); 
	
	else if (global.field.anisotropy_dirn == 2)
		return (Get_ky(ly) * kfactor[2]);
	
	else if (global.field.anisotropy_dirn == 3)
		return (Get_kz(lz) * kfactor[3]);
		
	else
		return 0;		// for -Wall
}

/// 3D == Anisotropic axis along x1: for anisotropic energy spectrum and 
///			energy transfer calculations,  \f$ K_\perp =\sqrt{K_2^2 + K_3^2} \f$.			
inline DP SFF_SLAB::AnisKperp(int lx, int ly, int lz)
{
	if (global.field.anisotropy_dirn == 1)
		return sqrt( pow2(Get_ky(ly) * kfactor[2]) + pow2(Get_kz(lz)*kfactor[3]) ); 
	
	else if (global.field.anisotropy_dirn == 2)
		return sqrt( pow2(Get_kx(lx)*kfactor[1]) + pow2(Get_kz(lz)*kfactor[3]) );
		
	else if (global.field.anisotropy_dirn == 3)
		return sqrt( pow2(Get_kx(lx)*kfactor[1]) + pow2(Get_ky(ly)*kfactor[2]) );
			
	else
		return 0;		// for -Wall
}

/// 3D == Anisotropic axis along x1: for anisotropic energy spectrum and 
///			energy transfer calculations,  horizontal direction 1, \f$ K_{h1} = K_2 \f$.										
inline DP SFF_SLAB::AnisKh1(int lx, int ly, int lz)
{	
	if (global.field.anisotropy_dirn == 1)
		return (Get_ky(ly) * kfactor[2]); 
	
	else if (global.field.anisotropy_dirn == 2)
		return (Get_kz(lz) * kfactor[3]);
		
	else if (global.field.anisotropy_dirn == 3)
		return (Get_kx(lx) * kfactor[1]);
			
	else
		return 0;		// for -Wall
}

/// 3D == Anisotropic axis along x1: for anisotropic energy spectrum and 
///			energy transfer calculations,  horizontal direction 2, \f$ K_{h2} = K_3 \f$.				
inline DP SFF_SLAB::AnisKh2(int lx, int ly, int lz)
{	
	if (global.field.anisotropy_dirn == 1)
		return (Get_kz(lz) * kfactor[3]);  
	
	else if (global.field.anisotropy_dirn == 2)
		return (Get_kx(lx) * kfactor[1]);
		
	else if (global.field.anisotropy_dirn == 3)
		return (Get_ky(ly) * kfactor[2]);
			
	else
		return 0;		// for -Wall
}
			
/// Cylindrical: Anis_min_Kpll
inline DP SFF_SLAB::Anis_min_Kpll() 
{ 
	return 0.0;
}
				
/// Cylindrical: Anis_max_Kpll
inline DP SFF_SLAB::Anis_max_Kpll() 
{ 
	
	DP maxKpll = 0.0;
	

    if (global.field.anisotropy_dirn == 1)
        maxKpll = ((Nx-1) * kfactor[1]); 
    
    else if (global.field.anisotropy_dirn == 2)
        maxKpll = ((Ny/2) * kfactor[2]); 
        
    else if (global.field.anisotropy_dirn == 3)
        maxKpll = ((Nz/2) * kfactor[3]); 

	
	return maxKpll;
}

	
/// 3D Cylindrical: Anis_max_Krho_radius_inside the wavenumber box.
inline int SFF_SLAB::Anis_max_Krho_radius_inside() 			
{
	DP Kmag = 0.0;	

    if (global.field.anisotropy_dirn == 1)
        Kmag = min( (Ny/2)*kfactor[2], (Nz/2)*kfactor[3] ); 
    
    else if (global.field.anisotropy_dirn == 2)
        Kmag = min( (Nx-1)*kfactor[1], (Nz/2)*kfactor[3] );
        
    else if (global.field.anisotropy_dirn == 3)
        Kmag = min( (Nx-1)*kfactor[1], (Ny/2)*kfactor[2] ); 
		
	return ((int) Kmag);	
}

// Max polar angle
inline DP SFF_SLAB::Get_max_polar_angle() 
{	
	
	return M_PI/2;
}			
	
//*********************************************************************************************

/*! \brief Returns the angle K vector makes with the anisotropic axis 
 * 
 * The range of angle is \f$ [0:\pi] \f$.
 *
 * \param  lx, ly, lz (3D)
 * \return \f$ \tan^{-1}(K_{\perp}/K_{||}) \f$.
 * \return \f$ \pi/2 \f$ if \f$ K_{||} = 0 \f$.
 */	
inline DP SFF_SLAB::AnisKvect_polar_angle(int lx, int ly, int lz)
{
	DP kkpll, kkperp;
	
	kkpll = AnisKpll(lx, ly, lz);
	kkperp = AnisKperp(lx, ly, lz);
	
	return Get_polar_angle(kkperp, kkpll);
}


/*! \brief 3D: Returns the azimutal angle.
 * 
 * The range of angle is \f$ [0:\pi] \f$.
 *
 * \param  lx, ly, lz (3D)
 * \return \f$ \tan^{-1}(Ky}/Kx \f$.
 * \return \f$ \pi/2 \f$ if \f$ K_{||} = 0 \f$.
 */	
inline DP SFF_SLAB::AnisKvect_azimuthal_angle(int lx, int ly, int lz)
{
	
	DP kkh1 = AnisKh1(lx, ly, lz);
	DP kkh2 = AnisKh2(lx, ly, lz);
	
	return Get_azimuthal_angle(kkh1, kkh2);
}			
						

//=================================== End of inline functions ==========================//



