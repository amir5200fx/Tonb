#pragma once
#ifndef _Marine_HullModeler_Header
#define _Marine_HullModeler_Header

#include <Cad2d_Modeler.hxx>

namespace tnbLib
{

	class Marine_HullModeler
		: public Cad2d_Modeler
	{

		/*Private Data*/

	public:

		Marine_HullModeler()
		{}


		Standard_Integer Import
		(
			const std::shared_ptr<Pln_Edge>& theEdge
		) override;

		Standard_Integer Import
		(
			std::shared_ptr<Pln_Edge>&& theEdge
		) override;

		void Import
		(
			const std::vector<std::shared_ptr<Pln_Edge>>& theEdegs
		) override;

		void Import
		(
			std::vector<std::shared_ptr<Pln_Edge>>&& theEdegs
		) override;
	};
}

#endif // !_Marine_HullModeler_Header
