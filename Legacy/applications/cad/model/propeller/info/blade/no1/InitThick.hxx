#pragma once
#ifndef _InitThick_Header
#define _InitThick_Header

#include "config.hxx"
#include "makers.hxx"

#include <PtdModel_Pars.hxx>
#include <PtdModel_BladeFormNo1_Thickness.hxx>

#define ThickClass tnbLib::ptdModel::BladeFormNo1_Thickness

namespace tnbLib
{

	InitBndParameter(LOWER_ROOT_THICK, UPPER_ROOT_THICK, DEFAULT_ROOT_THICK, 0.0, 12.0, 6.0, myRootThickX);
	InitBndParameter(LOWER_TIP_THICK, UPPER_TIP_THICK, DEFAULT_TIP_THICK, 0.0, 12.0, 0.3, myTipThickX);
	InitBndParameter(LOWER_ROOTSTEEP_THICK, UPPER_ROOTSTEEP_THICK, DEFAULT_ROOTSTEEP_THICK, 0.0, 1.0, 0.5, myRootSteepThickX);
	InitBndParameter(LOWER_TIPSTEEP_THICK, UPPER_TIPSTEEP_THICK, DEFAULT_TIPSTEEP_THICK, 0.0, 1.0, 0.5, myTipSteepThickX);

	DefFixedParameter(ThickClass::ROOT_THICK, myRootThickX, myRootThick);
	DefFixedParameter(ThickClass::TIP_THICK, myTipThickX, myTipThick);
	DefFixedParameter(ThickClass::ROOT_STEEP, myRootSteepThickX, myRootSteepThick);
	DefFixedParameter(ThickClass::TIP_STEEP, myTipSteepThickX, myTipSteepThick);

	void createThickForm();
}

#endif // !_InitThick_Header
