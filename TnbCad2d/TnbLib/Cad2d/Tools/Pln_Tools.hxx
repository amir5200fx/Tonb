#pragma once
#ifndef _Pln_Tools_Header
#define _Pln_Tools_Header

#include <vector>
#include <memory>

namespace tnbLib
{

	// Forward Declarations
	class Pln_Edge;
	class Pln_CmpEdge;

	class Pln_Tools
	{

	public:

		static std::shared_ptr<Pln_CmpEdge> MakeCompoundEdge
		(
			const std::vector<std::shared_ptr<Pln_Edge>>& theEdges
		);
	};
}

#endif // !_Pln_Tools_Header
