#pragma once
#ifndef _ShipModeler_Basic_MakerAux_Header
#define _ShipModeler_Basic_MakerAux_Header

#include <Standard_TypeDef.hxx>
#include <Entity2d_BoxFwd.hxx>

#include <gp_Ax2.hxx>

#include <memory>

namespace tnbLib
{

	namespace shipModelerLib
	{

		class Basic_MakerAux
		{

			/*Private Data*/

			gp_Ax2 theAx2_;

			std::shared_ptr<Entity2d_Box> theBoundingBox_;

		protected:

			Basic_MakerAux()
			{}

		public:

			const auto& Ax2() const
			{
				return theAx2_;
			}

			const auto& Domain() const
			{
				return theBoundingBox_;
			}

			void SetDomain
			(
				const std::shared_ptr<Entity2d_Box>&& theBox
			)
			{
				theBoundingBox_ = std::move(theBox);
			}

			void SetAx2(const gp_Ax2&& theAx)
			{
				theAx2_ = std::move(theAx);
			}
		};
	}
}

#endif // !_ShipModeler_Basic_MakerAux_Header
