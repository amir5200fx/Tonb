#pragma once
#ifndef _Aft_SizeCorr_FractionInfo_Header
#define _Aft_SizeCorr_FractionInfo_Header

#include <Standard_TypeDef.hxx>

#include <Global_Serialization.hxx>
#include <Global_AccessMethod.hxx>
#include <Mesh_Module.hxx>

namespace tnbLib
{

	class Aft_SizeCorr_FractionInfo
	{

		/*Private Data*/

		Standard_Real theDelta_;
		Standard_Real theCoeff_;


		// private functions and operators [3/1/2022 Amir]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & theDelta_;
			ar & theCoeff_;
		}

	public:

		static TnbMesh_EXPORT const Standard_Real DEFAULT_DELTA;
		static TnbMesh_EXPORT const Standard_Real DEFAULT_COEFF;


		// default constructor [3/1/2022 Amir]

		Aft_SizeCorr_FractionInfo()
			: theDelta_(DEFAULT_DELTA)
			, theCoeff_(DEFAULT_COEFF)
		{}


		// constructors [3/1/2022 Amir]


		//- Macros

		GLOBAL_ACCESS_PRIM_SINGLE(Standard_Real, Delta)
			GLOBAL_ACCESS_PRIM_SINGLE(Standard_Real, Coeff)
	};
}

#endif // !_Aft_SizeCorr_FractionInfo_Header
