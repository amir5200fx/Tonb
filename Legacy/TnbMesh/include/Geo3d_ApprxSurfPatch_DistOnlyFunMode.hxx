#pragma once
#ifndef _Geo3d_ApprxSurfPatch_DistOnlyFunMode_Header
#define _Geo3d_ApprxSurfPatch_DistOnlyFunMode_Header

#include <Geo3d_ApprxSurfPatch_FunMode.hxx>

namespace tnbLib
{

	// Forward Declarations [9/5/2022 Amir]
	class Geo3d_ApprxSurfPatch_Samples;

	class Geo3d_ApprxSurfPatch_DistOnlyFunMode
		: public Geo3d_ApprxSurfPatch_FunMode
	{

		/*Private Data*/

		std::shared_ptr<Geo3d_ApprxSurfPatch_Samples> theSamples_;

	public:

		// default constructor [9/1/2022 Amir]

		Geo3d_ApprxSurfPatch_DistOnlyFunMode()
		{}


		// constructors [9/1/2022 Amir]

		Geo3d_ApprxSurfPatch_DistOnlyFunMode
		(
			const std::shared_ptr<Geo3d_ApprxSurfPatch_Samples>& theSamples
		)
			: theSamples_(theSamples)
		{}

		Geo3d_ApprxSurfPatch_DistOnlyFunMode
		(
			std::shared_ptr<Geo3d_ApprxSurfPatch_Samples>&& theSamples
		)
			: theSamples_(std::move(theSamples))
		{}


		// public functions and operators [9/1/2022 Amir]

		const auto& Samples() const
		{
			return theSamples_;
		}

		void SetSamples(const std::shared_ptr<Geo3d_ApprxSurfPatch_Samples>& theSamples)
		{
			theSamples_ = theSamples;
		}

		void SetSamples(std::shared_ptr<Geo3d_ApprxSurfPatch_Samples>&& theSamples)
		{
			theSamples_ = std::move(theSamples);
		}

		TnbMesh_EXPORT Standard_Boolean 
			DoSubdivide
			(
				const Entity2d_Box& theRegion,
				const Geom_Surface& theGeometry,
				const Standard_Real theTol
			) const override;
	};
}

#endif // !_Geo3d_ApprxSurfPatch_DistOnlyFunMode_Header
