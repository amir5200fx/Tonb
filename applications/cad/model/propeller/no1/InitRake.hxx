#pragma once
#ifndef _InitRake_Header
#define _InitRake_Header

#include "config.hxx"
#include "makers.hxx"

#include <PtdModel_Pars.hxx>
#include <PtdModel_BladeFormNo1_Rake.hxx>

#define RakeClass tnbLib::ptdModel::BladeFormNo1_Rake

namespace tnbLib
{

	InitBndParameter(LOWER_RAKE, UPPER_RAKE, DEFAULT_RAKE, 0.0, 200.0, 0.0, myRakeX);

	DefFixedParameter(RakeClass::TIP_RAKE, myRakeX, myRake);

	void createRakeForm();
}

#endif // !_InitRake_Header
