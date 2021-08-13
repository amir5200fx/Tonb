#pragma once
#ifndef _InitCamberLoc_Header
#define _InitCamberLoc_Header

#include "config.hxx"
#include "makers.hxx"

#include <PtdModel_Pars.hxx>
#include <PtdModel_BladeFormNo1_CamberLoc.hxx>

#define CamberLocClass tnbLib::ptdModel::BladeFormNo1_CamberLoc

namespace tnbLib
{

	InitBndParameter(LOWER_BLADE_MAXCAMBERLOC, UPPER_BLADE_MAXCAMBERLOC, DEFAULT_BLADE_MAXCAMBERLOC, 0.3, 0.7, 0.4, myBladeMaxCamberX);

	DefFixedParameter(CamberLocClass::MAX_CAMBER_LOC, myBladeMaxCamberX, myBladeMaxCamber);

	void createMaxCamberLocForm();
}

#endif // !_InitCamberLoc_Header
