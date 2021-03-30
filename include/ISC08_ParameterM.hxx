#pragma once
#ifndef _ISC08_ParameterM_Header
#define _ISC08_ParameterM_Header

#include <ISC08_Parameter.hxx>
#include <ISC08_Module.hxx>
#include <dimensionSet.hxx>

#define ISC08_PARAM(CLASS_NAME, PARAM_NAME, PARAM_DIM)							\
	class CLASS_NAME															\
		: public ISC08_Parameter												\
	{																			\
																				\
																				\
		friend class boost::serialization::access;								\
		template<class Archive>													\
		void serialize(Archive& ar, const unsigned int file_version)			\
		{																		\
			ar & boost::serialization::base_object<ISC08_Parameter>(*this);		\
		}																		\
																				\
	public:																		\
		static const CLASS_NAME null;											\
																				\
		CLASS_NAME() : ISC08_Parameter(PARAM_NAME, PARAM_DIM){}					\
																				\
		explicit CLASS_NAME(const Standard_Real theValue)						\
			: ISC08_Parameter(PARAM_NAME, PARAM_DIM, theValue) {}				\
																				\
		Standard_Boolean IsNull() const											\
		{return this == &null;}													\
	};

#define ISC08_PARAM_IMP(CLASS_NAME)										\
	const tnbLib::isc08Lib::CLASS_NAME tnbLib::isc08Lib::CLASS_NAME::null(0);

#endif // !_ISC08_ParameterM_Header
