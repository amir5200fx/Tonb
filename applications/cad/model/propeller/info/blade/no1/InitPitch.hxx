#pragma once
#ifndef _InitPitch_Header
#define _InitPitch_Header

#include "config.hxx"
#include "makers.hxx"

#include <Geo_Tools.hxx>
#include <PtdModel_Pars.hxx>
#include <PtdModel_BladeFormNo1_Pitch.hxx>

#define PitchClass tnbLib::ptdModel::BladeFormNo1_Pitch

namespace tnbLib
{

	InitBndParameter(LOWER_ROOT_PITCH, UPPER_ROOT_PITCH, DEFAULT_ROOT_PITCH, 0.0, Geo_Tools::DegToRadian(90.0), Geo_Tools::DegToRadian(55.0), myRootPitchX);
	InitBndParameter(LOWER_TIP_PITCH, UPPER_TIP_PITCH, DEFAULT_TIP_PITCH, 0.0, Geo_Tools::DegToRadian(90.0), Geo_Tools::DegToRadian(25.0), myTipPitchX);
	InitBndParameter(LOWER_ROOTSTEEP_PITCH, UPPER_ROOTSTEEP_PITCH, DEFAULT_ROOTSTEEP_PITCH, 0.0, 1.0, 0.5, myRootSteepPitchX);
	InitBndParameter(LOWER_TIPSTEEP_PITCH, UPPER_TIPSTEEP_PITCH, DEFAULT_TIPSTEEP_PITCH, 0.0, 1.0, 0.5, myTipSteepPitchX);

	DefFixedParameter(PitchClass::ROOT_PITCH, myRootPitchX, myRootPitch);
	DefFixedParameter(PitchClass::TIP_PITCH, myTipPitchX, myTipPitch);
	DefFixedParameter(PitchClass::ROOT_STEEP, myRootSteepPitchX, myRootSteepPitch);
	DefFixedParameter(PitchClass::TIP_STEEP, myTipSteepPitchX, myTipSteepPitch);

	void createPitchForm();
}

#endif // !_InitPitch_Header
