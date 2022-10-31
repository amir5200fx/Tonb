#pragma once
#ifndef _Geo3d_SpaceCloud_InternalSamples_Header
#define _Geo3d_SpaceCloud_InternalSamples_Header

#include <Geo3d_SpaceCloud.hxx>

namespace tnbLib
{

	// Forward Declarations [10/28/2022 Amir]
	class Geo3d_SpaceCloud_TetSamples;	

	class Geo3d_SpaceCloud_InternalSamples
		: public Geo3d_SpaceCloud
	{

		/*Private Data*/

		std::shared_ptr<Geo3d_SpaceCloud_TetSamples> theTetSamples_;


		// Private functions and operators [10/28/2022 Amir]

		TNB_SERIALIZATION(TnbMesh_EXPORT);

	public:

		// default constructor [10/28/2022 Amir]

		Geo3d_SpaceCloud_InternalSamples()
		{}


		// constructors [10/28/2022 Amir]

		explicit Geo3d_SpaceCloud_InternalSamples
		(
			const std::shared_ptr<Geo3d_SpaceCloud_TetSamples>& theSamples
		)
			: theTetSamples_(theSamples)
		{}

		Geo3d_SpaceCloud_InternalSamples
		(
			std::shared_ptr<Geo3d_SpaceCloud_TetSamples>&& theSamples
		)
			: theTetSamples_(std::move(theSamples))
		{}


		// Public functions and operators [10/28/2022 Amir]

		const auto& TetSamples() const
		{
			return theTetSamples_;
		}

		TnbMesh_EXPORT std::vector<Pnt3d> 
			CalcCloud
			(
				const Entity3d_Tetrahedralization&
			) const override;

		void SetTetSamples(const std::shared_ptr<Geo3d_SpaceCloud_TetSamples>& theSamples)
		{
			theTetSamples_ = theSamples;
		}

		void SetTetSamples(std::shared_ptr<Geo3d_SpaceCloud_TetSamples>&& theSamples)
		{
			theTetSamples_ = std::move(theSamples);
		}
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::Geo3d_SpaceCloud_InternalSamples);

#endif // !_Geo3d_SpaceCloud_InternalSamples_Header
