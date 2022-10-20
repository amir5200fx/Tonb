#pragma once
#ifndef _Geo3d_SegmentCloud_NoneInternal_Header
#define _Geo3d_SegmentCloud_NoneInternal_Header

#include <Geo3d_SegmentCloud.hxx>

namespace tnbLib
{

	class Geo3d_SegmentCloud_NoneInternal
		: public Geo3d_SegmentCloud
	{

		/*Private Data*/


		// Private functions and operators [10/19/2022 Amir]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar & boost::serialization::base_object<Geo3d_SegmentCloud>(*this);
		}

	public:


		// default constructor [10/19/2022 Amir]

		Geo3d_SegmentCloud_NoneInternal()
		{}


		// constructors [10/19/2022 Amir]


		// public functions and operators [10/19/2022 Amir]

		TnbMesh_EXPORT std::vector<Standard_Real> CalcCloud(const std::vector<Standard_Real>&) const override;

	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::Geo3d_SegmentCloud_NoneInternal);

#endif // !_Geo3d_SegmentCloud_NoneInternal_Header
