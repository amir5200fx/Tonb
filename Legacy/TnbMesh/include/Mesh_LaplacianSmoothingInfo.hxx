#pragma once
#ifndef _Mesh_LaplacianSmoothingInfo_Header
#define _Mesh_LaplacianSmoothingInfo_Header

#include <Global_Serialization.hxx>
#include <Global_TypeDef.hxx>

namespace tnbLib
{

	class Mesh_LaplacianSmoothingInfo
	{

		/*Private Data*/

		Standard_Integer theNbLevels_;
		Standard_Real theUnderRelaxation_;


		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & theNbLevels_;
			ar & theUnderRelaxation_;
		}

	public:

		static const Standard_Integer DEFAULT_MAX_NB_LEVELS;
		static const Standard_Real DEFAULT_UNDER_RELAXATION;

		Mesh_LaplacianSmoothingInfo()
			: theNbLevels_(DEFAULT_MAX_NB_LEVELS)
			, theUnderRelaxation_(DEFAULT_UNDER_RELAXATION)
		{}

		auto NbLevels() const
		{
			return theNbLevels_;
		}

		auto UnderRelaxation() const
		{
			return theUnderRelaxation_;
		}

		void SetNbLevels(const Standard_Integer nb)
		{
			theNbLevels_ = nb;
		}

		void SetUnderRelaxation(const Standard_Real theUr)
		{
			theUnderRelaxation_ = theUr;
		}
	};
}

#endif // !_Mesh_LaplacianSmoothingInfo_Header
