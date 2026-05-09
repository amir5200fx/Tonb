#pragma once
#ifndef _Aft2d_StdOptNodeSurface_Calculator_Header
#define _Aft2d_StdOptNodeSurface_Calculator_Header

#include <Aft2d_OptNodeSurface_Calculator.hxx>

namespace tnbLib
{

	// Forward Declarations [2/24/2022 Amir]

	class Aft2d_StdOptNodeSurface_Calculator
		: public Aft2d_OptNodeSurface_Calculator
	{

		/*Private Data*/

		// private functions and operators [2/24/2022 Amir]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & boost::serialization::base_object<Aft2d_OptNodeSurface_Calculator>(*this);
		}


		// private static functions [2/24/2022 Amir]


	public:

		// default constructor [2/24/2022 Amir]

		Aft2d_StdOptNodeSurface_Calculator()
		{}

		// constructors [2/24/2022 Amir]


		// override functions and operators [2/24/2022 Amir]

		TnbMesh_EXPORT void Perform() override;

		// public functions and operators [2/24/2022 Amir]

		/*static TnbMesh_EXPORT Pnt2d
			CorrectCoord
			(
				const Pnt2d& theCentre,
				const Pnt2d& theCoord,
				const Entity2d_Box&
			);*/

	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::Aft2d_StdOptNodeSurface_Calculator);

#endif // !_Aft2d_StdOptNodeSurface_Calculator_Header
