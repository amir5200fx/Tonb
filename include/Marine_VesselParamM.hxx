#pragma once
#ifndef _Marine_VesselParamM_Header
#define _Marine_VesselParamM_Header

#include <Marine_VesselParam.hxx>
#include <dimensionSet.hxx>

#define MARINE_VESSELPARAM(CLASS_NAME, PARAM_NAME, PARAM_DIM)					\
	class CLASS_NAME															\
		: public Marine_VesselParam												\
	{																			\
																				\
	public:																		\
		static const CLASS_NAME null;											\
		explicit CLASS_NAME(const Standard_Real theValue)						\
			: Marine_VesselParam(PARAM_NAME, PARAM_DIM, theValue) {}			\
																				\
		Standard_Boolean IsNull() const											\
		{return this == &null;}													\
	};

#define MARINE_VESSELPARAM_IMP(CLASS_NAME)										\
	const tnbLib::marineLib::CLASS_NAME tnbLib::marineLib::CLASS_NAME::null(0);

#endif // !_Marine_VesselParamM_Header
