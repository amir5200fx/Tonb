#pragma once
#ifndef _InitCamber_Header
#define _InitCamber_Header

#include "config.hxx"
#include "makers.hxx"

#include <PtdModel_Pars.hxx>
#include <PtdModel_BladeFormNo1_Camber.hxx>

#define CamberClass tnbLib::ptdModel::BladeFormNo1_Camber

namespace tnbLib
{

	InitBndParameter(LOWER_ROOT_CAMBER, UPPER_ROOT_CAMBER, DEFAULT_ROOT_CAMBER, 0.0, 0.2, 0.004, myRootCamberX);
	InitBndParameter(LOWER_TIP_CAMBER, UPPER_TIP_CAMBER, DEFAULT_TIP_CAMBER, 0.0, 0.2, 0.0, myTipCamberX);
	InitBndParameter(LOWER_MAX_CAMBER, UPPER_MAX_CAMBER, DEFAULT_MAX_CAMBER, 0.0, 0.2, 0.01, myMaxCamberX);
	InitBndParameter(LOWER_LOC_MAX_CAMBER, UPPER_LOC_MAX_CAMBER, DEFAULT_LOC_MAX_CAMBER, 0.0, 1.0, 0.5, myLocMaxCamberX);
	InitBndParameter(LOWER_ROOT_WEIGHT_CAMBER, UPPER_ROOT_WEIGHT_CAMBER, DEFAULT_ROOT_WEIGHT_CAMBER, 0.1, 3.0, 1.0, myWightRootCamberX);
	InitBndParameter(LOWER_TIP_WEIGHT_CAMBER, UPPER_TIP_WEIGHT_CAMBER, DEFAULT_TIP_WEIGHT_CAMBER, 0.1, 3.0, 1.0, myWeightTipCamberX);
	
	DefFixedParameter(CamberClass::ROOT_CAMBER, myRootCamberX, myRootCamber);
	DefFixedParameter(CamberClass::TIP_CAMBER, myTipCamberX, myTipCamber);
	DefFixedParameter(CamberClass::MAX_CAMBER, myMaxCamberX, myMaxCamber);
	DefFixedParameter(CamberClass::MAX_CAMBER_LOCATION, myLocMaxCamberX, myMaxCamberLoc);
	DefFixedParameter(CamberClass::ROOT_WEIGHT, myWightRootCamberX, myRootCamberWeight);
	DefFixedParameter(CamberClass::TIP_WEIGHT, myWeightTipCamberX, myTipCamberWeight);

	void createCamberForm();
}

#endif // !_InitCamber_Header
