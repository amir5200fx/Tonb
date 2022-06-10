#pragma once
#ifndef _Cad_MergeParaCurvesTools_Header
#define _Cad_MergeParaCurvesTools_Header

#include <Mesh_Module.hxx>

#include <vector>
#include <memory>

namespace tnbLib
{

	namespace cadLib
	{
		namespace mergeParaCurves
		{

			// Forward Declarations [6/4/2022 Amir]
			class Node;
			class Link;
			class Segment;
			class Ring;
			class Curve;
			class Wire;
		}
	}

	class Cad_MergeParaCurvesTools
	{

	public:

		static std::vector<std::shared_ptr<cadLib::mergeParaCurves::Node>> RetrieveNodes(const std::vector<std::shared_ptr<cadLib::mergeParaCurves::Link>>&);
		static std::vector<std::shared_ptr<cadLib::mergeParaCurves::Node>> RetrieveIntsctNodes(const std::vector<std::shared_ptr<cadLib::mergeParaCurves::Node>>&);
	};
}

#endif // !_Cad_MergeParaCurvesTools_Header
