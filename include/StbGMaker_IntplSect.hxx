#pragma once
#ifndef _StbGMaker_IntplSect_Header
#define _StbGMaker_IntplSect_Header

#include <Global_Done.hxx>
#include <StbGMaker_Module.hxx>

#include <memory>

class gp_Pln;

namespace tnbLib
{

	// Forward Declarations
	class Marine_CmpSection;

	class StbGMaker_IntplSect
		: public Global_Done
	{

		/*Private Data*/

		std::shared_ptr<Marine_CmpSection> theSect0_;
		std::shared_ptr<Marine_CmpSection> theSect1_;

		std::shared_ptr<Marine_CmpSection> theIntrpolated_;

	protected:

		StbGMaker_IntplSect()
		{}

		StbGMaker_IntplSect
		(
			const std::shared_ptr<Marine_CmpSection>& theS0,
			const std::shared_ptr<Marine_CmpSection>& theS1
		)
			: theSect0_(theS0)
			, theSect1_(theS1)
		{}

		auto& ChangeInterpolated()
		{
			return theIntrpolated_;
		}

	public:

		const auto& Sect0() const
		{
			return theSect0_;
		}

		const auto& Sect1() const
		{
			return theSect1_;
		}

		const auto& Interpolated() const
		{
			return theIntrpolated_;
		}

		virtual void Perform(const gp_Pln& thePln) = 0;

		void LoadSect0(const std::shared_ptr<Marine_CmpSection>& theS0)
		{
			theSect0_ = theS0;
		}

		void LoadSect1(const std::shared_ptr<Marine_CmpSection>& theS1)
		{
			theSect1_ = theS1;
		}

		
	};
}

#endif // !_StbGMaker_IntplSect_Header
