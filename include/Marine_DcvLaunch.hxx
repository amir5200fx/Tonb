#pragma once
#ifndef _Marine_DcvLaunch_Header
#define _Marine_DcvLaunch_Header

#include <Marine_Launch.hxx>

namespace tnbLib
{

	// Forward Declarations
	class NumAlg_FalsePos_Info;
	class NumAlg_Secant_Info;
	class Marine_Body;

	class Marine_DcvLaunch
		: public Marine_Launch
	{

		/*Private Data*/

		std::shared_ptr<Marine_Body> theBody_;

	public:

		static const std::shared_ptr<NumAlg_FalsePos_Info> FalsePosInfo;
		static const std::shared_ptr<NumAlg_Secant_Info> SecantInfo;

		Marine_DcvLaunch();

		void Perform();

		void LoadBody
		(
			const std::shared_ptr<Marine_Body>& theBody
		)
		{
			theBody_ = theBody;
		}
	};
}

#endif // !_Marine_DcvLaunch_Header
