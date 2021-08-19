#pragma once
#ifndef _InitSkew_Header
#define _InitSkew_Header

#include "config.hxx"
#include "makers.hxx"

#include <PtdModel_Pars.hxx>
#include <PtdModel_BladeFormNo1_Skew.hxx>

#define SkewClass tnbLib::ptdModel::BladeFormNo1_Skew

namespace tnbLib
{

	InitBndParameter(LOWER_TIP_SKEW, UPPER_TIP_SKEW, DEFAULT_TIP_SKEW, 0.0, 200.0, 100.0, myTipSkewX);
	InitBndParameter(LOWER_ROOTSTEEP_SKEW, UPPER_ROOTSTEEP_SKEW, DEFAULT_ROOTSTEEP_SKEW, 0.0, 1.0, 0.5, myRootSteepSkewX);
	InitBndParameter(LOWER_TIPSTEEP_SKEW, UPPER_TIPSTEEP_SKEW, DEFAULT_TIPSTEEP_SKEW, 0.0, 1.0, 0.5, myTipSteepSkewX);


	DefFixedParameter(SkewClass::TIP_SKEW, myTipSkewX, myTipSkew);
	DefFixedParameter(SkewClass::ROOT_STEEP, myRootSteepSkewX, myRootSteepSkew);
	DefFixedParameter(SkewClass::TIP_STEEP, myTipSteepSkewX, myTipSteepSkew);

	void createSkewForm();
}

#endif // !_InitSkew_Header
