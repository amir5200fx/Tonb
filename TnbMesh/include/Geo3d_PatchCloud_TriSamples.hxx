#pragma once
#ifndef _Geo3d_PatchCloud_TriSamples_Header
#define _Geo3d_PatchCloud_TriSamples_Header

#include <Mesh_Module.hxx>
#include <Global_Serialization.hxx>

#include <vector>

namespace tnbLib
{

	// Forward Declarations [10/16/2022 Amir]
	class Pnt2d;

	class Geo3d_PatchCloud_TriSamples
	{

		/*Private Data*/

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			// empty body [10/16/2022 Amir]
		}

	protected:

		// default constructor [10/16/2022 Amir]

		Geo3d_PatchCloud_TriSamples()
		{}

		// constructors [10/16/2022 Amir]


	public:

		// public functions and operators [10/16/2022 Amir]

		virtual std::vector<Pnt2d> CalcSamples(const Pnt2d& theP0, const Pnt2d& theP1, const Pnt2d& theP2) const = 0;
	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::Geo3d_PatchCloud_TriSamples);

#endif // !_Geo3d_PatchCloud_TriSamples_Header
