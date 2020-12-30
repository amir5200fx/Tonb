#pragma once
#ifndef _Marine_SailModeler_Header
#define _Marine_SailModeler_Header

#include <Cad2d_Modeler.hxx>

namespace tnbLib
{

	class Marine_SailModeler
		: public Cad2d_Modeler
	{

		/*Private Data*/

		TnbCad2d_EXPORT void CheckCurveType(const std::shared_ptr<Pln_Edge>& theEdge, const char* name) const override;

	public:

		Marine_SailModeler()
		{}

	};
}

#endif // !_Marine_SailModeler_Header
