#pragma once
#ifndef _Geo3d_PatchCloud_InternalSamples_Header
#define _Geo3d_PatchCloud_InternalSamples_Header

#include <Geo3d_PatchCloud.hxx>

namespace tnbLib
{

	// Forward Declarations [10/16/2022 Amir]
	class Geo3d_PatchCloud_EdgeSamples;
	class Geo3d_PatchCloud_TriSamples;

	class Geo3d_PatchCloud_InternalSamples
		: public Geo3d_PatchCloud
	{

		/*Private Data*/

		std::shared_ptr<Geo3d_PatchCloud_EdgeSamples> theEdgeSamples_;
		std::shared_ptr<Geo3d_PatchCloud_TriSamples> theTriSamples_;


		// Private functions and operators [10/16/2022 Amir]

		TNB_SERIALIZATION(TnbMesh_EXPORT);

	public:

		// default constructor [10/16/2022 Amir]

		Geo3d_PatchCloud_InternalSamples()
		{}


		// constructors [10/16/2022 Amir]

		Geo3d_PatchCloud_InternalSamples
		(
			const std::shared_ptr<Geo3d_PatchCloud_EdgeSamples>& theEdgeSamples,
			const std::shared_ptr<Geo3d_PatchCloud_TriSamples>& theTriSamples
		)
			: theEdgeSamples_(theEdgeSamples)
			, theTriSamples_(theTriSamples)
		{}

		Geo3d_PatchCloud_InternalSamples
		(
			std::shared_ptr<Geo3d_PatchCloud_EdgeSamples>&& theEdgeSamples,
			std::shared_ptr<Geo3d_PatchCloud_TriSamples>&& theTriSamples
		)
			: theEdgeSamples_(std::move(theEdgeSamples))
			, theTriSamples_(std::move(theTriSamples))
		{}

		// public functions and operators [10/16/2022 Amir]

		const auto& EdgeSamples() const
		{
			return theEdgeSamples_;
		}

		const auto& TriSamples() const
		{
			return theTriSamples_;
		}

		TnbMesh_EXPORT std::vector<Pnt2d> CalcCloud(const Entity2d_Triangulation&) const override;

		void SetEdgeSamples(const std::shared_ptr<Geo3d_PatchCloud_EdgeSamples>& theSamples)
		{
			theEdgeSamples_ = theSamples;
		}

		void SetEdgeSamples(std::shared_ptr<Geo3d_PatchCloud_EdgeSamples>&& theSamples)
		{
			theEdgeSamples_ = std::move(theSamples);
		}

		void SetTriSamples(const std::shared_ptr<Geo3d_PatchCloud_TriSamples>& theSamples)
		{
			theTriSamples_ = theSamples;
		}

		void SetTriSamples(std::shared_ptr<Geo3d_PatchCloud_TriSamples>&& theSamples)
		{
			theTriSamples_ = std::move(theSamples);
		}
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::Geo3d_PatchCloud_InternalSamples);

#endif // !_Geo3d_PatchCloud_InternalSamples_Header
