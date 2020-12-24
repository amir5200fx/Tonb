#pragma once
#ifndef _Marine_EnvtParamM_Header
#define _Marine_EnvtParamM_Header

#include <Marine_EnvtParam.hxx>
#include <dimensionSet.hxx>
#include <Marine_Module.hxx>

#define MARINE_ENVTPARAM(CLASS_NAME, PARAM_NAME, PARAM_DIM)						\
	class CLASS_NAME															\
		: public Marine_EnvtParam												\
	{																			\
																				\
		friend class boost::serialization::access;								\
		template<class Archive>													\
		void serialize(Archive& ar, const unsigned int file_version)			\
		{																		\
			ar & boost::serialization::base_object<Marine_EnvtParam>(*this);	\
		}																		\
																				\
		CLASS_NAME() {}															\
																				\
	public:																		\
		static TnbMarine_EXPORT const CLASS_NAME null;							\
		explicit CLASS_NAME(const Standard_Real theValue)						\
			: Marine_EnvtParam(PARAM_NAME, PARAM_DIM, theValue) {}				\
																				\
		Standard_Boolean IsNull() const											\
		{return this == &null;}													\
	};

#define MARINE_ENVTPARAM_IMP(CLASS_NAME)										\
	const tnbLib::marineLib::CLASS_NAME tnbLib::marineLib::CLASS_NAME::null(0);

#endif // !_Marine_EnvtParamM_Header
