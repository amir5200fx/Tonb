#pragma once
#ifndef _Geo3d_PatchCloud_Header
#define _Geo3d_PatchCloud_Header

#include <Mesh_Module.hxx>
#include <Entity2d_TriangulationFwd.hxx>
#include <Global_Serialization.hxx>
#include <Global_Done.hxx>

#include <memory>
#include <vector>

namespace tnbLib
{

	// Forward Declarations [10/15/2022 Amir]


	class Pnt2d;

	class Geo3d_PatchCloud
	{

		/*Private Data*/


		// Private functions and operators [10/16/2022 Amir]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			// empty body [10/16/2022 Amir]
		}


	protected:

		// default constructor [10/15/2022 Amir]

		Geo3d_PatchCloud()
		{}

		// constructors [10/15/2022 Amir]


	public:

		// public functions and operators [10/15/2022 Amir]


		virtual std::vector<Pnt2d> CalcCloud(const Entity2d_Triangulation&) const = 0;

	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::Geo3d_PatchCloud);

#endif // !_Geo3d_PatchCloud_Header
