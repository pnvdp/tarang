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

/*! \file basicfn_inline.h 
 * 
 * @brief basic inline functions and constant definitions that are common to all basis functions (MPI).
 * 
 * @version 4.0 Parallel version
 * @author  M. K. Verma
 * @date    August 2008
 * @bug		No known bug
 */ 



#ifndef _BASIC_FN_INLINE_H
#define _BASIC_FN_INLINE_H

#include "def_vars.h"
#include "Global_extern_vars.h"

using namespace blitz ;

//*********************************************************************************************

#ifndef _MYMIN
#define _MYMIN

	inline int min(int a, int b) { return a < b ? a : b; }		
	inline DP  min(DP a, DP b)   { return a < b ? a : b; }
	
	inline int minimum(ptrdiff_t a, int b) { return a < b ? a : b; }
	inline int maximum(ptrdiff_t a, int b) { return (b < a) ? a : b; }
	
#endif 

inline int newdivision(ptrdiff_t a, ptrdiff_t b) { return ((a%b) == 0) ? (a/b) : (a/b+1);}


inline DP my_pow(DP x, int n) {	
	double temp;
	switch (n) {
		case 0 : return 1.0; break;
		case 1 : return x; break;
		case 2 : return (x*x); break;
		case 3 : return (x*x*x); break;
		case 4 : temp = my_pow(x,2); return (temp*temp); break;	
		case 5 : return (my_pow(x,4)*x); break;
		case 6 : temp = my_pow(x,2); return (temp*temp*temp); break;	
		case 7 : return (my_pow(x,6)*x); break;
		case 8 : return (my_pow(x,4)*my_pow(x,4)); break;
		case 9 : return (my_pow(x,8)*x); break;
		case 10 : return (my_pow(x,8)*my_pow(x,2)); break;
		default : return pow(x,n); 	
	}
}

// re(V.W*)
inline DP real_cprod(complx V, complx W)
{
	return (real(V)*real(W) + imag(V)*imag(W));
}

// im(V.W*)
inline DP imag_cprod(complx V, complx W)
{
	return (-real(V)*imag(W) +imag(V)*real(W));
}


inline DP Vsqr(complx F)
{
    return (pow2(real(F)) + pow2(imag(F)));
}

inline DP Vsqr(complx Vx, complx Vy)
{
	return (pow2(real(Vx)) + pow2(imag(Vx)) + pow2(real(Vy)) + pow2(imag(Vy)));
}

inline DP Vsqr(complx Vx, complx Vy, complx Vz)
{
    return (pow2(real(Vx)) + pow2(imag(Vx)) + pow2(real(Vy)) + pow2(imag(Vy)) + pow2(real(Vz)) +pow2(imag(Vz)));
}

inline DP Vsqr(DP F) { return my_pow(F,2); }

inline DP Vsqr(DP Vx, DP Vy) {return (pow2(Vx) + pow2(Vy));}

inline DP Vsqr(DP Vx, DP Vy, DP Vz)
{
    return (pow2(Vx) + pow2(Vy) + pow2(Vz));
}

inline DP Vsqr(TinyVector<complx,3> V)
{
    return Vsqr(V(0), V(1), V(2));
}

inline DP Vsqr(TinyVector<DP,3> V)
{
    return (pow2(V(0)) + pow2(V(1)) + pow2(V(2)));
}

template<int rank>
inline DP Array_sqr(Array<complx,rank> A)
{
    return sum(sqr(abs(A)));
}

template<int rank>
inline DP Array_sqr(Array<DP,rank> A)
{
    return sum(sqr(A));
}


	// real(V.W*)
inline DP mydot(complx Vx, complx Vy, complx Vz, complx Wx, complx Wy, complx Wz)
{
    return  real_cprod(Vx,Wx)+ real_cprod(Vy,Wy) + real_cprod(Vz,Wz);
}

inline DP mydot_imag(complx Vx, complx Vy, complx Vz, complx Wx, complx Wy, complx Wz)
{
    return  imag_cprod(Vx,Wx)+ imag_cprod(Vy,Wy) + imag_cprod(Vz,Wz);
}

// real(V.W*); blitz does V.W
inline DP mydot(TinyVector<complx,3> V, TinyVector<complx,3> W)
{
    return  real_cprod(V(0),W(0))+ real_cprod(V(1),W(1)) + real_cprod(V(2),W(2));
}

// imag(V.W*); blitz does V.W
inline DP mydot_imag(TinyVector<complx,3> V, TinyVector<complx,3> W)
{
    return  imag_cprod(V(0),W(0))+ imag_cprod(V(1),W(1)) + imag_cprod(V(2),W(2));
}

// real(V.W*); blitz does V.W
template<int rank>
inline DP mydot(Array<complx,rank> A, Array<complx,rank> B)
{
	return sum(real(A*conj(B)));
}

template<int rank>
inline DP mydot(Array<DP,rank> A, Array<DP,rank> B)
{
	return sum(A*B);
}


// If G in some other basis, covert to Fourier_space; G as the first component of Vect V
inline void Convert_to_Fourier_space(complx G, complx &G_Four)
{
	if ((global.program.sincostr_switch == "SFF") || (global.program.sincostr_switch == "S0F") || (global.program.sincostr_switch == "SCF") || (global.program.sincostr_switch == "CSF")) 
		G_Four = (-I)*G;
	
	else if ((global.program.sincostr_switch == "CFF") || (global.program.sincostr_switch == "C0F") || (global.program.sincostr_switch == "CCF"))
		G_Four = G;
		
	else if (global.program.sincostr_switch == "SSF")
		G_Four = -G;
}

inline void Convert_to_Fourier_space(DP G, complx &G_Four)
{
	if ((global.program.sincostr_switch == "SCC") || (global.program.sincostr_switch == "CCS") || (global.program.sincostr_switch == "CSC") || (global.program.sincostr_switch == "S0C") || (global.program.sincostr_switch == "C0S")) 
		G_Four = complx(0, -G);
	
	else if (global.program.sincostr_switch == "SSS")
		G_Four = complx(0, G);
	
	else if ((global.program.sincostr_switch == "CCC") || (global.program.sincostr_switch == "C0C"))
		G_Four = complx(G, 0);
	
	else if ((global.program.sincostr_switch == "CSS") || (global.program.sincostr_switch == "SSC") || (global.program.sincostr_switch == "SCS") || (global.program.sincostr_switch == "S0S"))
		G_Four = complx(-G, 0);
}

// If V in some other basis, covert to Fourier_space
inline void Convert_to_Fourier_space(TinyVector<complx,3> V, TinyVector<complx,3> &VFour)
{
	if ((global.program.sincostr_switch == "SFF") || (global.program.sincostr_switch == "S0F")) 
		VFour = (-I)*V(0), V(1), V(2);
	
	else if ((global.program.sincostr_switch == "CFF") || (global.program.sincostr_switch == "C0F"))
		VFour = V(0), (-I)*V(1), (-I)*V(2);
	
	if (global.program.sincostr_switch == "SCF") 
		VFour = (-I)*V(0), (-I)*V(1), V(2);
	
	else if (global.program.sincostr_switch == "CSF")
		VFour = (-I)*V(0), (-I)*V(1), -V(2);
	
	else if (global.program.sincostr_switch == "SSF")
		VFour = -V(0), (-I)*V(1), (-I)*V(2);
	
	else if (global.program.sincostr_switch == "CCF")
		VFour = V(0), -V(1), (-I)*V(2);
}

// SSS basis fn has similar sign, so most often it does not change the energy.
inline void Convert_to_Fourier_space(TinyVector<DP,3> V, TinyVector<complx,3> &VFour)
{
	if (global.program.sincostr_switch == "SCC") 
		VFour = complx(0, -V(0)), complx(0, -V(1)), complx(0, -V(2));
	
	if (global.program.sincostr_switch == "CSS") 
		VFour = complx(-V(0), 0), complx(-V(1), 0), complx(-V(2), 0);
	
	if (global.program.sincostr_switch == "CCS") 
		VFour = complx(0, -V(0)), complx(0, V(1)), complx(0, -V(2));
	
	if (global.program.sincostr_switch == "SSC") 
		VFour = complx(-V(0), 0), complx(V(1), 0), complx(-V(2), 0);
	
	if (global.program.sincostr_switch == "CSC") 
		VFour = complx(0, -V(0)), complx(0, -V(1)), complx(0, V(2));
	
	if (global.program.sincostr_switch == "SCS") 
		VFour = complx(-V(0), 0), complx(-V(1), 0), complx(V(2), 0);
	
	if (global.program.sincostr_switch == "CCC") 
		VFour = complx(V(0), 0), complx(-V(1), 0), complx(-V(2), 0);
	
	if (global.program.sincostr_switch == "SSS") 
		VFour = complx(0, V(0)), complx(0, -V(1)), complx(0, -V(2));
}

	///////////

	// If G in some other basis, covert to Fourier_space; G as the first component of Vect V
inline void Convert_from_Fourier_space(complx G_Four, complx &G)
{
	if ((global.program.sincostr_switch == "SFF") || (global.program.sincostr_switch == "S0F") || (global.program.sincostr_switch == "SCF") || (global.program.sincostr_switch == "CSF")) 
		G = I*G_Four;
	
	else if ((global.program.sincostr_switch == "CFF") || (global.program.sincostr_switch == "C0F") || (global.program.sincostr_switch == "CCF"))
		G = G_Four;
	
	else if (global.program.sincostr_switch == "SSF")
		G = -G_Four;
}

inline void Convert_from_Fourier_space(complx G_Four, DP &G)
{
	if ((global.program.sincostr_switch == "SCC") || (global.program.sincostr_switch == "CCS") || (global.program.sincostr_switch == "CSC") || (global.program.sincostr_switch == "S0C") || (global.program.sincostr_switch == "C0S")) 
		G = -imag(G_Four);
	
	else if (global.program.sincostr_switch == "SSS")
		G = imag(G_Four);
	
	else if ((global.program.sincostr_switch == "CCC") || (global.program.sincostr_switch == "C0C"))
		G = real(G_Four);
	
	else if ((global.program.sincostr_switch == "CSS") || (global.program.sincostr_switch == "SSC") || (global.program.sincostr_switch == "SCS") || (global.program.sincostr_switch == "S0S"))
		G = -real(G_Four);
}


// If V computed for Fourier_space, covert it to appropriate basis
inline void Convert_from_Fourier_space(TinyVector<complx,3> VFour, TinyVector<complx,3> &V)
{
	if ((global.program.sincostr_switch == "SFF") || (global.program.sincostr_switch == "S0F")) 
		V = I*VFour(0), VFour(1), VFour(2);
	
	else if ((global.program.sincostr_switch == "CFF") || (global.program.sincostr_switch == "C0F"))
		V = VFour(0), I*VFour(1), I*VFour(2);
	
	if (global.program.sincostr_switch == "SCF") 
		V = I*VFour(0), I*VFour(1), VFour(2);
	
	else if (global.program.sincostr_switch == "CSF")
		V = I*VFour(0), I*VFour(1), -VFour(2);
	
	else if (global.program.sincostr_switch == "SSF")
		V = -VFour(0), I*VFour(1), I*VFour(2);
	
	else if (global.program.sincostr_switch == "CCF")
		V = VFour(0), -VFour(1), I*VFour(2);
}


	// If V computed for Fourier_space, covert it to appropriate basis
inline void Convert_from_Fourier_space(TinyVector<complx,3> VFour, TinyVector<DP,3> &V)
{
	if (global.program.sincostr_switch == "SCC") 
		V = -imag(VFour(0)), -imag(VFour(1)), -imag(VFour(2));
	
	if (global.program.sincostr_switch == "CSS") 
		V = -real(VFour(0)), -real(VFour(1)), -real(VFour(2));
	
	if (global.program.sincostr_switch == "CCS") 
		V = -imag(VFour(0)), imag(VFour(1)), -imag(VFour(2));
	
	if (global.program.sincostr_switch == "SSC")
		V = -real(VFour(0)), real(VFour(1)), -real(VFour(2));
	
	if (global.program.sincostr_switch == "CSC") 
		V = -imag(VFour(0)), imag(VFour(1)), imag(VFour(2));
	
	if (global.program.sincostr_switch == "SCS") 
		V = -real(VFour(0)), -real(VFour(1)), real(VFour(2));
	
	if (global.program.sincostr_switch == "CCC") 
		V = real(VFour(0)),  -real(VFour(1)), -real(VFour(2));
	
	if (global.program.sincostr_switch == "SSS") 
		V = imag(VFour(0)), -imag(VFour(1)), -imag(VFour(2));
	
	if (global.program.sincostr_switch == "S0S") 
		VFour = -real(VFour(0)), 0, real(VFour(2));
	
	if (global.program.sincostr_switch == "C0C") 
		VFour = real(VFour(0)), 0, -real(VFour(2));
	
	if (global.program.sincostr_switch == "S0C") 
		V = -imag(VFour(0)), 0, -imag(VFour(2));
	
	if (global.program.sincostr_switch == "C0S") 
		V = -imag(VFour(0)), 0, -imag(VFour(2));
}

//
//
/*! \brief Returns the polar angle, the angle K vector makes with the anisotropic axis
 * 
 * The range of angle is \f$ \Theta = 0:\Theta_{max}\f$.
 *
 * \return \f$ \tan^{-1}(K_{\perp}/K_{||}) \f$.
 * \return \f$ \pi/2 \f$ if \f$ K_{||} = 0 \f$.
 */	

inline DP Get_polar_angle(DP kkperp, DP kkpll)
{
	DP temp;
	
	if (abs(kkperp) > MYEPS) {
		if (abs(kkpll) > MYEPS)
			temp = atan(kkperp/kkpll);
		
		else
			temp = M_PI/2;
	}
	
	else {		// along pll axis
		if (kkpll >= 0)
			temp = 0.0;
		else
			temp = M_PI;
	}
		
	return (temp >= 0) ? temp : temp + M_PI; 
}


//
//
/*! \brief Returns the azimuthal angle, the angle K_perp vector makes with the h1 axis.
 * 
 * The range of angle is \f$ [0: 2\pi] \f$.
 *
 * \return \f$ \cos^{-1}(K_{||1}/K_{\rho}) \f$.
 */	

inline DP Get_azimuthal_angle(DP kkh1, DP kkh2)
{
	DP angle;
	
	DP kkperp = sqrt(pow2(kkh1) + pow2(kkh2));
	
	if (abs(kkperp) > MYEPS) {
		angle = acos(kkh1/kkperp);

		if (kkh2 >= 0)
			return angle;
		else
			return (2*M_PI - angle);
        // when kkh2 < 0, angle is negative. Convert it positive by adding 2 pi.
	}
	
	else // for origin-- to make sure program does not blow up. Avoid it.
		return  0.0;
}


//*********************************************************************************************

/*! @brief computer Fourier index for the last wavenumber given real-space index.
 *
 * @param	i_last  Real-space index for last wavenumber (e.g., kz for 3D).
 *
 * @return  k_last  Wavenumber index for the last wavenumber
 * @return  is_real return 1 if real-part else 0.
 */
inline void Real_to_fourier_index(int i_last, int& k_last, int& is_real)
{
	k_last = i_last/2;
	
	if ((i_last % 2) == 0)
		is_real = 1;
	
	else
		is_real = 0;

}

#endif

//***************************** end of basicfn_inline.h *********************************


