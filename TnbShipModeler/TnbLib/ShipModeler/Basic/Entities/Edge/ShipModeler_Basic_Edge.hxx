#pragma once
#ifndef _ShipModeler_Basic_Edge_Header
#define _ShipModeler_Basic_Edge_Header

#include <Pln_Edge.hxx>

namespace tnbLib
{

	// Forward Declarations
	class NModel_Curve;

	namespace shipModelerLib
	{

		class Basic_Edge
			: public Pln_Edge
		{

			/*Private Data*/

			std::shared_ptr<NModel_Curve> theCurve3d_;

		public:

			template<class... _Types>
			Basic_Edge(const _Types&&... Args)
				: Pln_Edge(Args)
			{}

			const auto& Curve3d() const
			{
				return theCurve3d_;
			}

			void SetCurve3d
			(
				const std::shared_ptr<NModel_Curve>&& theCurve
			)
			{
				theCurve3d_ = std::move(theCurve);
			}
		};
	}
}


#endif // !_ShipModeler_Basic_Edge_Header
