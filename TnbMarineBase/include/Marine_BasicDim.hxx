#pragma once
#ifndef _Marine_BasicDim_Header
#define _Marine_BasicDim_Header

#include <Marine_VesselParams.hxx>
#include <Marine_Analysis.hxx>
#include <Marine_BodiesFwd.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations

	class Marine_BasicDim
		: public Marine_Analysis
	{

		/*Private Data*/

		//- Length overall
		marineLib::LOA theLoa_;

		//- Breadth
		marineLib::B theB_;

		//- Depth
		marineLib::D theD_;


		const std::shared_ptr<marineLib::Body_Dry>& theBody_;


		auto& ChangeLOA()
		{
			return theLoa_;
		}

		auto& ChangeB()
		{
			return theB_;
		}

		auto& ChangeD()
		{
			return theD_;
		}

	public:


		Marine_BasicDim
		(
			const std::shared_ptr<marineLib::Body_Dry>& theBody
		);


		const auto& LOA() const
		{
			return theLoa_;
		}

		const auto& B() const
		{
			return theB_;
		}

		const auto& D() const
		{
			return theD_;
		}

		const auto& Body() const
		{
			return theBody_;
		}

		void Perform();


	};
}

#endif // !_Marine_BasicDim_Header
