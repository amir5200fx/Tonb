#pragma once
#ifndef _SectPx_Tools_Header
#define _SectPx_Tools_Header

#include <Pnt2d.hxx>
#include <SectPx_Segment.hxx>

#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_Parent;
	class SectPx_TopoProfile;
	class SectPx_Pnt;
	class SectPx_Registry;
	class SectPx_Node;

	class SectPx_Tools
	{

	public:

		enum class jointPriority
		{
			left,
			right
		};

		static Standard_Boolean
			IsValidToJoint
			(
				const std::shared_ptr<SectPx_Node>& theNode0,
				const std::shared_ptr<SectPx_Node>& theNode1,
				const jointPriority priority = jointPriority::left
			);

		static Standard_Integer
			MakePair
			(
				const std::shared_ptr<SectPx_Pnt>& theP0,
				const std::shared_ptr<SectPx_Pnt>& theP1,
				const std::shared_ptr<SectPx_Registry>& theReg,
				const jointPriority priority = jointPriority::left
			);

		static std::tuple<Standard_Integer, Standard_Integer>
			MakeJoint
			(
				const std::shared_ptr<SectPx_TopoProfile>& theLeft,
				const std::shared_ptr<SectPx_TopoProfile>& theRight,
				const std::shared_ptr<SectPx_Registry>& theReg,
				const jointPriority priority = jointPriority::left
			);

		static std::vector<Pnt2d>
			RetrieveControlPoints
			(
				const std::vector<std::shared_ptr<SectPx_Segment>>& theSegments
			);

		static void RemoveParentFromChildren
		(
			const std::shared_ptr<SectPx_Parent>& theParent
		);

	};
}

#endif // !_SectPx_Tools_Header
