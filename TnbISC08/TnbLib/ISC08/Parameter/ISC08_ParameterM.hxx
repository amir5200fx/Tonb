#pragma once
#ifndef _ISC08_ParameterM_Header
#define _ISC08_ParameterM_Header

#include <ISC08_Parameter.hxx>
#include <dimensionSet.hxx>

#define ISC08_PARAM(CLASS_NAME, PARAM_NAME, PARAM_DIM)							\
	class CLASS_NAME															\
		: public ISC08_Parameter												\
	{																			\
																				\
	public:																		\
		static const CLASS_NAME null;											\
		explicit CLASS_NAME(const Standard_Real theValue)						\
			: ISC08_Parameter(PARAM_NAME, PARAM_DIM, theValue) {}				\
																				\
		Standard_Boolean IsNull() const											\
		{return this == &null;}													\
	};

#define ISC08_PARAM_IMP(CLASS_NAME)										\
	const tnbLib::isc08Lib::CLASS_NAME tnbLib::isc08Lib::CLASS_NAME::null(0);

#endif // !_ISC08_ParameterM_Header
