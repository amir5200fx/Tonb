#pragma once
#ifndef _Mesh2d_VolumeSizeMapTool_Header
#define _Mesh2d_VolumeSizeMapTool_Header

#include <Mesh2d_SizeMapTool.hxx>
#include <Entity2d_PolygonFwd.hxx>

#include <map>

namespace tnbLib
{

	// Forward Declarations [7/13/2023 Payvand]
	class Mesh2d_VolumeSizeMapTool_Info;
	class Mesh2d_SizeMapVolume;

	class Mesh2d_VolumeSizeMapTool
		: public Mesh2d_SizeMapTool
	{

		/*Private Data*/

		std::map<Standard_Integer, std::shared_ptr<Mesh2d_SizeMapVolume>>
			theVolumes_;

		std::shared_ptr<Mesh2d_VolumeSizeMapTool_Info> theInfo_;
		Standard_Boolean theAdaptFlag_;


		// Private functions and operators [7/19/2023 Payvand]

		TNB_SERIALIZATION(TnbMesh_EXPORT);

		static TnbMesh_EXPORT std::vector<Pnt2d>
			RetrieveInsidePoints
			(
				const std::vector<std::shared_ptr<Pnt2d>>& thePts,
				const Entity2d_Polygon&
			);

	protected:

		// default constructor [7/12/2023 Payvand]

		Mesh2d_VolumeSizeMapTool()
			: theAdaptFlag_(Standard_False)
		{}

		

	public:

		// constructors [7/12/2023 Payvand]

		Mesh2d_VolumeSizeMapTool
		(
			const std::shared_ptr<Cad2d_Plane>& thePlane,
			const std::shared_ptr<Entity2d_Box>& theDomain,
			const std::shared_ptr<Mesh2d_ReferenceValues>& theRef,
			const std::shared_ptr<Mesh2d_VolumeSizeMapTool_Info>& theInfo
		)
			: Mesh2d_SizeMapTool(theRef, theDomain, thePlane)
			, theInfo_(theInfo)
			, theAdaptFlag_(Standard_False)
		{}

		// Public functions and operators [7/12/2023 Payvand]

		const auto& Volumes() const { return theVolumes_; }
		const auto& AlgInfo() const { return theInfo_; }
		auto AdaptiveFlag() const { return theAdaptFlag_; }

		TnbMesh_EXPORT void Perform() override;
		TnbMesh_EXPORT void ImportVolume
		(
			const Standard_Integer theIndex, 
			const std::shared_ptr<Mesh2d_SizeMapVolume>&
		);
		TnbMesh_EXPORT void RemoveVolume(const Standard_Integer theIndex);
		void SetAdapt(const Standard_Boolean flag) { theAdaptFlag_ = flag; }
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::Mesh2d_VolumeSizeMapTool);

#endif // !_Mesh2d_VolumeSizeMapTool_Header
