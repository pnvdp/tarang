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
 * De
 * You should have received a copy of the GNU General Public License
 * along with Tarang-2; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, U
 */


/*! \file  universal_basic.h
 * 
 * @brief  Universal functions based on basis fns (MPI)
 *
 * @author  M. K. Verma
 * @version 4.0 MPI
 * @date Sept 2008
 * @bug	No known bugs
 */


#ifndef _FFFW_SLAB_H
#define _FFFW_SLAB_H

#include "def_vars.h"
#include "basicfn_inline.h"
#include "spectral_transform.h"
#include "universal.h"
#include "ArrayOps.h"

using namespace blitz;

//*********************************************************************************************	


class FFFW_SLAB:public Universal
{				
public:
	FFFW_SLAB();
	#include "universal_fn_names.h"
	void Array_exp_ksqr(Array<complx,3> A, DP factor);
	
	void Array_exp_ksqr(Array<complx,3> A, DP factor, DP hyper_factor, int hyper_exponent);
	
	void Compute_divergence(Array<complx,3> Ax, Array<complx,3> Ay, Array<complx,3> Az, Array<complx,3> div, string field_or_nlin, DP &total_abs_div, bool print_switch);

	void Get_XY_plane(Array<complx,3> A, Array<complx,2> plane_xy, int kz);
};

#endif


//******************************** End of .h  **************************************


