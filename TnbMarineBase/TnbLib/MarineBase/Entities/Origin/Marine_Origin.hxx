#pragma once
#ifndef _Marine_Origin_Header
#define _Marine_Origin_Header

#include <Marine_Entity.hxx>

#include <gp_Ax2.hxx>

namespace tnbLib
{

	class Marine_Origin
		: public Marine_Entity
	{

		/*Private Data*/

		gp_Ax2 theOrigin_;

	public:

		static const gp_Ax2& SystemOrigin();

		Marine_Origin();

		Marine_Origin(const gp_Ax2& theOrigin);


		const auto& Origin() const
		{
			return theOrigin_;
		}

		auto& Origin()
		{
			return theOrigin_;
		}
	};
}

#endif // !_Marine_Origin_Header
