#pragma once
#ifndef _Marine_DisplacerModeler_Header
#define _Marine_DisplacerModeler_Header

#include <Cad2d_Modeler.hxx>

namespace tnbLib
{

	class Marine_DisplacerModeler
		: public Cad2d_Modeler
	{

		/*Private Data*/

		TnbCad2d_EXPORT void CheckCurveType(const std::shared_ptr<Pln_Edge>& theEdge, const char* name) const override;

	public:

		Marine_DisplacerModeler()
		{}

	};
}

#endif // !_Marine_DisplacerModeler_Header
