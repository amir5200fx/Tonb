#pragma once
#ifndef _Marine_TankModeler_Header
#define _Marine_TankModeler_Header

#include <Cad2d_Modeler.hxx>

namespace tnbLib
{

	class Marine_TankModeler
		: public Cad2d_Modeler
	{

		/*Private Data*/

		TnbCad2d_EXPORT void CheckCurveType(const std::shared_ptr<Pln_Edge>& theEdge, const char* name) const override;

	public:

		Marine_TankModeler()
		{}

	};
}

#endif // !_Marine_TankModeler_Header
