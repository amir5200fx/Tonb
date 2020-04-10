#pragma once
#ifndef _Marine_BasicDim_Header
#define _Marine_BasicDim_Header

#include <Global_Done.hxx>
#include <Marine_VesselParams.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations
	class Marine_Body;

	class Marine_BasicDim
		: public Global_Done
	{

		/*Private Data*/

		//- Length overall
		marineLib::LOA theLoa_;

		//- Breadth
		marineLib::B theB_;

		//- Depth
		marineLib::D theD_;


		std::shared_ptr<Marine_Body> theBody_;


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

		Marine_BasicDim();

		Marine_BasicDim
		(
			const std::shared_ptr<Marine_Body>& theBody
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

		void LoadBody(const std::shared_ptr<Marine_Body>& theBody)
		{
			theBody_ = theBody;
		}


	};
}

#endif // !_Marine_BasicDim_Header
