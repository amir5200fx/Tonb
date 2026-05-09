#pragma once
#ifndef _Geo3d_SpaceCloud_Header
#define _Geo3d_SpaceCloud_Header

#include <Mesh_Module.hxx>
#include <Entity3d_TetrahedralizationFwd.hxx>
#include <Global_Serialization.hxx>
#include <Global_Done.hxx>

#include <memory>
#include <vector>

namespace tnbLib
{

	// Forward Declarations [10/28/2022 Amir]
	class Pnt3d;

	class Geo3d_SpaceCloud
	{

		/*Private Data*/

		// Private functions and operators [10/28/2022 Amir]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			// empty body [10/28/2022 Amir]
		}

	protected:

		// default constructor [10/28/2022 Amir]

		Geo3d_SpaceCloud()
		{}


		// constructors [10/28/2022 Amir]


	public:


		// Public functions and operators [10/28/2022 Amir]

		virtual std::vector<Pnt3d> CalcCloud(const Entity3d_Tetrahedralization&) const = 0;
	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::Geo3d_SpaceCloud);

#endif // !_Geo3d_SpaceCloud_Header
