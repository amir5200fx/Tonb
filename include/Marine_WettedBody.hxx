#pragma once
#ifndef _Marine_WettedBody_Header
#define _Marine_WettedBody_Header

#include <Marine_HullBody.hxx>

namespace tnbLib
{

	class Marine_WettedBody
		: public Marine_HullBody
	{

		/*private Data*/

		std::shared_ptr<Marine_CmpSection> theWater_;
		std::shared_ptr<Marine_CmpSection> theMid_;

	public:

		Marine_WettedBody();

		Marine_WettedBody
		(
			const Standard_Integer theIndex
		);

		Marine_WettedBody
		(
			const Standard_Integer theIndex,
			const word& theName
		);

		Standard_Boolean IsWetted() const override
		{
			return Standard_True;
		}

		auto& ChangeWater()
		{
			return theWater_;
		}

		auto& ChangeMid()
		{
			return theMid_;
		}

		const auto& WL() const
		{
			return theWater_;
		}

		const auto& Mid() const
		{
			return theMid_;
		}
	};
}

#endif // !_Marine_WettedBody_Header
