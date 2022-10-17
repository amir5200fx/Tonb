#pragma once
#ifndef _Marine_CoeffParamM_Header
#define _Marine_CoeffParamM_Header

#include <Marine_CoeffParam.hxx>
#include <dimensionSet.hxx>
#include <Marine_Module.hxx>

#define MARINE_COEFFPARAM(CLASS_NAME, PARAM_NAME, PARAM_DIM)					\
	class CLASS_NAME															\
		: public Marine_CoeffParam												\
	{																			\
																				\
		friend class boost::serialization::access;								\
		template<class Archive>													\
		void serialize(Archive& ar, const unsigned int file_version)			\
		{																		\
			ar & boost::serialization::base_object<Marine_CoeffParam>(*this);	\
		}																		\
																				\
		CLASS_NAME() {}															\
																				\
	public:																		\
		static TnbMarine_EXPORT const CLASS_NAME null;							\
		explicit CLASS_NAME(const Standard_Real theValue)						\
			: Marine_CoeffParam(PARAM_NAME, PARAM_DIM, theValue) {}				\
																				\
		Standard_Boolean IsNull() const											\
		{return this == &null;}													\
	};

#define MARINE_ENVTPARAM_IMP(CLASS_NAME)										\
	const tnbLib::marineLib::CLASS_NAME tnbLib::marineLib::CLASS_NAME::null(0);

#endif // !_Marine_CoeffParamM_Header
