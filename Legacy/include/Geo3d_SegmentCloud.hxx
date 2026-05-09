#pragma once
#ifndef _Geo3d_SegmentCloud_Header
#define _Geo3d_SegmentCloud_Header

#include <Mesh_Module.hxx>
#include <Entity2d_PolygonFwd.hxx>
#include <Global_Serialization.hxx>
#include <Global_Done.hxx>

#include <memory>
#include <vector>

namespace tnbLib
{

	class Geo3d_SegmentCloud
	{

		/*Private Data*/


		// Private functions and operators [10/19/2022 Amir]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			// empty body [10/19/2022 Amir]
		}

	protected:

		// default constructor [10/19/2022 Amir]

		Geo3d_SegmentCloud()
		{}


		// constructors [10/19/2022 Amir]\


	public:

		// public functions and operators [10/19/2022 Amir]

		virtual std::vector<Standard_Real> CalcCloud(const std::vector<Standard_Real>&) const = 0;

	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::Geo3d_SegmentCloud);

#endif // !_Geo3d_SegmentCloud_Header
