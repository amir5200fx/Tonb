#pragma once
#ifndef _Mesh2d_VolumeSizeMapTool_Header
#define _Mesh2d_VolumeSizeMapTool_Header

#include <Mesh2d_SizeMapTool.hxx>

#include <map>

namespace tnbLib
{

	// Forward Declarations [7/13/2023 Payvand]
	class Mesh2d_VolumeSizeMapTool_Info;

	class Mesh2d_VolumeSizeMapTool
		: public Mesh2d_SizeMapTool
	{

		/*Private Data*/

		std::map<Standard_Integer, std::shared_ptr<Cad2d_Plane>>
			theShapes_;

		std::shared_ptr<Mesh2d_VolumeSizeMapTool_Info> theInfo_;

	protected:

		// default constructor [7/12/2023 Payvand]

		Mesh2d_VolumeSizeMapTool()
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
		{}

		// Public functions and operators [7/12/2023 Payvand]

		const auto& Shapes() const { return theShapes_; }

		const auto& AlgInfo() const { return theInfo_; }

		void Perform() override;

	};
}

#endif // !_Mesh2d_VolumeSizeMapTool_Header
