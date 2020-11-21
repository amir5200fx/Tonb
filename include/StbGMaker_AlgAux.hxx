#pragma once
#ifndef _StbGMaker_AlgAux_Header
#define _StbGMaker_AlgAux_Header

#include <Standard_TypeDef.hxx>
#include <Entity2d_BoxFwd.hxx>
#include <Global_Serialization.hxx>
#include <StbGMaker_Module.hxx>

#include <gp_Ax2.hxx>

#include <memory>

namespace tnbLib
{

	class StbGMaker_AlgAux
	{

		/*Private Data*/

		gp_Ax2 theAx2_;

		std::shared_ptr<Entity2d_Box> theBoundingBox_;


		DECLARE_SAVE_LOAD_HEADER(TnbStbGMaker_EXPORT);

	protected:

		StbGMaker_AlgAux()
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

#endif // !_StbGMaker_AlgAux_Header
