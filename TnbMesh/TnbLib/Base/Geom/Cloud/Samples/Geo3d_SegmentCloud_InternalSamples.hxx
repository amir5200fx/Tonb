#pragma once
#ifndef _Geo3d_SegmentCloud_InternalSamples_Header
#define _Geo3d_SegmentCloud_InternalSamples_Header

#include <Geo3d_SegmentCloud.hxx>

namespace tnbLib
{


	// Forward Declarations [10/19/2022 Amir]
	class Geo3d_SegmentCloud_Samples;

	class Geo3d_SegmentCloud_InternalSamples
		: public Geo3d_SegmentCloud
	{

		/*Private Data*/

		std::shared_ptr<Geo3d_SegmentCloud_Samples> theSamples_;


		// Private functions and operators [10/19/2022 Amir]

		TNB_SERIALIZATION(TnbMesh_EXPORT);

	public:


		// default constructor [10/19/2022 Amir]

		Geo3d_SegmentCloud_InternalSamples()
		{}


		// constructors [10/19/2022 Amir]

		explicit Geo3d_SegmentCloud_InternalSamples
		(
			const std::shared_ptr<Geo3d_SegmentCloud_Samples>& theSamples
		)
			: theSamples_(theSamples)
		{}

		Geo3d_SegmentCloud_InternalSamples
		(
			std::shared_ptr<Geo3d_SegmentCloud_Samples>&& theSamples
		)
			: theSamples_(std::move(theSamples))
		{}


		// Public functions and operators [10/19/2022 Amir]

		const auto& Samples() const
		{
			return theSamples_;
		}

		TnbMesh_EXPORT std::vector<Standard_Real> CalcCloud(const std::vector<Standard_Real>&) const override;

		void SetSamples(const std::shared_ptr<Geo3d_SegmentCloud_Samples>& theSamples)
		{
			theSamples_ = theSamples;
		}

		void SetSamples(std::shared_ptr<Geo3d_SegmentCloud_Samples>&& theSamples)
		{
			theSamples_ = std::move(theSamples);
		}
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::Geo3d_SegmentCloud_InternalSamples);

#endif // !_Geo3d_SegmentCloud_InternalSamples_Header
