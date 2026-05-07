#pragma once
#ifndef _MeshPost_LaplacianSmoothing_Info_Header
#define _MeshPost_LaplacianSmoothing_Info_Header

#include <MeshPost_Module.hxx>
#include <Global_Serialization.hxx>
#include <Global_TypeDef.hxx>

namespace tnbLib
{

	class MeshPost_LaplacianSmoothing_Info
	{

		/*Private Data*/

		Standard_Real theUnderRelaxation_;

		Standard_Integer theNbLevels_;


		// private functions and operators [9/19/2022 Amir]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar & theUnderRelaxation_;
			ar & theNbLevels_;
		}

	public:


		static TnbMeshPost_EXPORT const Standard_Real DEFAULT_UNDER_RELAXATION;
		static TnbMeshPost_EXPORT const Standard_Integer DEFAULT_NB_LEVELS;

		// default constructor [9/19/2022 Amir]

		MeshPost_LaplacianSmoothing_Info()
			: theUnderRelaxation_(DEFAULT_UNDER_RELAXATION)
			, theNbLevels_(DEFAULT_NB_LEVELS)
		{}

		// constructors [9/19/2022 Amir]


		// public functions and operators [9/19/2022 Amir]

		// Macros [9/19/2022 Amir]

		auto UnderRelaxation() const
		{
			return theUnderRelaxation_;
		}

		auto NbLevels() const
		{
			return theNbLevels_;
		}

		void SetUnderRelaxation(const Standard_Real theUR)
		{
			theUnderRelaxation_ = theUR;
		}

		void SetNbLevels(const Standard_Integer n)
		{
			theNbLevels_ = n;
		}
	};
}

#endif // !_MeshPost_LaplacianSmoothing_Info_Header
