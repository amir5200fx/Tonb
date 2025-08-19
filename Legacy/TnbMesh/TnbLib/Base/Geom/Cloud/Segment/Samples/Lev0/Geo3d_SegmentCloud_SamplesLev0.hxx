#pragma once
#ifndef _Geo3d_SegmentCloud_SamplesLev0_Header
#define _Geo3d_SegmentCloud_SamplesLev0_Header

#include <Geo3d_SegmentCloud_Samples.hxx>

namespace tnbLib
{

	class Geo3d_SegmentCloud_SamplesLev0
		: public Geo3d_SegmentCloud_Samples
	{

		/*private Data*/

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & boost::serialization::base_object<Geo3d_SegmentCloud_Samples>(*this);
		}

	public:

		// default constructor [10/19/2022 Amir]

		Geo3d_SegmentCloud_SamplesLev0()
		{}


		// constructors [10/19/2022 Amir]


		// public functions and operators [10/19/2022 Amir]

		TnbMesh_EXPORT std::vector<Standard_Real> 
			CalcSamples
			(
				const Standard_Real x0,
				const Standard_Real x1
			) const override;
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::Geo3d_SegmentCloud_SamplesLev0);

#endif // !_Geo3d_SegmentCloud_SamplesLev0_Header
