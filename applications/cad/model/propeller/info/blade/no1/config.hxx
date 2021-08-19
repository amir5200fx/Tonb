#pragma once
#ifndef _config_Header
#define _config_Header

#include <PtdModel_BndValue.hxx>
#include <PtdModel_Pars.hxx>

#define InitBndParameter(LOWER,UPPER,DEFAULT,LOWER_VALUE,UPPER_VALUE,DEFAULT_VALUE, PAR)	\
	static const auto LOWER = LOWER_VALUE;													\
	static const auto UPPER = UPPER_VALUE;													\
	static const auto DEFAULT = DEFAULT_VALUE;												\
	static auto PAR = PtdModel_BndValue(LOWER, UPPER, DEFAULT)

#define DefFixedParameter(NAME, ParX, PAR)  \
	static auto PAR = std::make_shared<PtdModel_FixedPar>(0, NAME, ParX);

#define ImportToForm(FORM, PAR)	\
	FORM->SetParameter(PAR->Name(), PAR)
	

#endif // !_config_Header
