#pragma once
#ifndef _dimensionSet_Serialization_Header
#define _dimensionSet_Serialization_Header

#include <Global_Serialization.hxx>

namespace tnbLib
{

	class dimensionSet;
}

namespace boost
{
	namespace serialization
	{

		template<class Archive>
		void save(Archive & ar, const tnbLib::dimensionSet& d, const unsigned int version)
		{
			FatalErrorIn(FunctionSIG)
				<< "this function is supposed to be not calling" << tnbLib::endl
				<< tnbLib::abort(tnbLib::FatalError);
		}

		template<class Archive>
		void load(Archive & ar, tnbLib::dimensionSet& d, const unsigned int version)
		{
			FatalErrorIn(FunctionSIG)
				<< "this function is supposed to be not calling" << tnbLib::endl
				<< tnbLib::abort(tnbLib::FatalError);
		}

		template<>
		TnbGlobal_EXPORT void save<TNB_oARCH_TYPE>
			(
				TNB_oARCH_TYPE& ar,
				const tnbLib::dimensionSet& d,
				const unsigned int version
				);

		template<>
		TnbGlobal_EXPORT void load<TNB_iARCH_TYPE>
			(
				TNB_iARCH_TYPE& ar,
				tnbLib::dimensionSet& d, 
				const unsigned int version
				);
	}
}

BOOST_SERIALIZATION_SPLIT_FREE(tnbLib::dimensionSet)

#endif // !_dimensionSet_Serialization_Header
