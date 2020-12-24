#pragma once
#ifndef _HydStatic_Trim_Header
#define _HydStatic_Trim_Header

#include <Global_Done.hxx>
#include <Marine_VesselParams.hxx>

namespace tnbLib
{

	class HydStatic_Trim
		: public Global_Done
	{

		/*Private Data*/

		marineLib::TA theTa_;
		marineLib::TF theTf_;

	protected:

		HydStatic_Trim()
			: theTa_(0)
			, theTf_(0)
		{}

	public:

		const auto& TA() const
		{
			return theTa_;
		}

		const auto& TF() const
		{
			return theTf_;
		}
	};
}

#endif // !_HydStatic_Trim_Header
