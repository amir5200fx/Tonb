#pragma once
#ifndef _BoundarySizeMap3d_UniformFaceTool_Header
#define _BoundarySizeMap3d_UniformFaceTool_Header

#include <BoundarySizeMap3d_FaceTool.hxx>

namespace tnbLib
{

	// Forward Declarations [9/6/2022 Amir]
	class BoundarySizeMap3d_UniformFaceTool_Info;

	class BoundarySizeMap3d_UniformFaceTool
		: public BoundarySizeMap3d_FaceTool
	{

		/*Private Data*/

		std::shared_ptr<BoundarySizeMap3d_UniformFaceTool_Info> theInfo_;

		// private functions and operators [7/20/2022 Amir]

		TNB_SERIALIZATION(TnbMesh_EXPORT);

	protected:

		// default constructor [7/17/2022 Amir]

		BoundarySizeMap3d_UniformFaceTool()
		{}

	public:


		static TnbMesh_EXPORT Standard_Boolean POST_BALANCE;
		static TnbMesh_EXPORT Standard_Integer DEFAULT_BUCKET_SIZE;
		static TnbMesh_EXPORT Standard_Integer DEFAULT_UNBALANCING;

		// constructors [7/17/2022 Amir]

		BoundarySizeMap3d_UniformFaceTool
		(
			const std::shared_ptr<Mesh3d_ReferenceValues>& theRef,
			const std::shared_ptr<Entity3d_Box>& theDomain,
			const std::shared_ptr<Geo3d_PatchCloud>& theCloud,
			const std::shared_ptr<Cad_TModel>& theModel,
			const std::shared_ptr<BoundarySizeMap3d_UniformFaceTool_Info>& theInfo
		)
			: BoundarySizeMap3d_FaceTool(theRef, theDomain, theCloud, theModel)
			, theInfo_(theInfo)
		{}

		// public functions and operators [7/17/2022 Amir]

		const auto& AlgInfo() const
		{
			return theInfo_;
		}

		TnbMesh_EXPORT void Perform() override;

		void SetAlgInfo(const std::shared_ptr<BoundarySizeMap3d_UniformFaceTool_Info>& theInfo)
		{
			theInfo_ = theInfo;
		}

		void SetAlgInfo(std::shared_ptr<BoundarySizeMap3d_UniformFaceTool_Info>&& theInfo)
		{
			theInfo_ = std::move(theInfo);
		}

	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::BoundarySizeMap3d_UniformFaceTool);

#endif // !_BoundarySizeMap3d_UniformFaceTool_Header
