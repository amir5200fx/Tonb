#pragma once
#ifndef _InitChord_Header
#define _InitChord_Header

#include "config.hxx"
#include "makers.hxx"

#include <PtdModel_Pars.hxx>
#include <PtdModel_BladeFormNo1_Chord.hxx>

#define ChordClass tnbLib::ptdModel::BladeFormNo1_Chord

namespace tnbLib
{

	InitBndParameter(LOWER_ROOT_CHORD, UPPER_ROOT_CHORD, DEFAULT_ROOT_CHORD, 0.0, 150.0, 20.0, myRootChordX);
	InitBndParameter(LOWER_TIP_CHORD, UPPER_TIP_CHORD, DEFAULT_TIP_CHORD, 0.0, 150.0, 2.0, myTipChordX);
	InitBndParameter(LOWER_MAXCHORD, UPPER_MAXCHORD, DEFAULT_MAXCHORD, 0.0, 150, 80.0, myMaxChordX);
	InitBndParameter(LOWER_MAXCHORDLOC, UPPER_MAXCHORDLOC, DEFAULT_MAXCHORDLOC, 0.0, 1.0, 0.6, myMaxChordLocX);
	InitBndParameter(LOWER_ROOT_WEIGHT_CHORD, UPPER_ROOT_WEIGHT_CHORD, DEFAULT_ROOT_WEIGHT_CHORD, 0.1, 3.0, 1.0, myRootChordWeightX);
	InitBndParameter(LOWER_TIP_WEIGHT_CHORD, UPPER_TIP_WEIGHT_CHORD, DEFAULT_TIP_WEIGHT_CHORD, 0.1, 3.0, 1.0, myTipChordWeightX);

	DefFixedParameter(ChordClass::ROOT_CHORD, myRootChordX, myRootChord);
	DefFixedParameter(ChordClass::TIP_CHORD, myTipChordX, myTipChord);
	DefFixedParameter(ChordClass::MAX_CHORD, myMaxChordX, myMaxChord);
	DefFixedParameter(ChordClass::MAX_CHORD_LOCATION, myMaxChordLocX, myMaxChordLoc);
	DefFixedParameter(ChordClass::ROOT_WEIGHT, myRootChordWeightX, myRootChordWeight);
	DefFixedParameter(ChordClass::TIP_WEIGHT, myTipChordWeightX, myTipChordWeight);

	void createChordForm();
}

#endif // !_InitChord_Header
