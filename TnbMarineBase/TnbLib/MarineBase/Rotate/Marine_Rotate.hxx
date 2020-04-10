#pragma once
#ifndef _Marine_Rotate_Header
#define _Marine_Rotate_Header

#include <Global_Done.hxx>
#include <Global_AccessMethod.hxx>

#include <memory>

#include <gp_Ax1.hxx>

namespace tnbLib
{

	// Forward Declarations
	class Marine_Body;

	class Marine_Rotate
		: public Global_Done
	{

		/*Private Data*/

		Standard_Real theTrim_;
		gp_Ax1 theTrimAx_;

		Standard_Real theHeel_;
		gp_Ax1 theHeelAx_;

		std::shared_ptr<Marine_Body> theBody_;

	public:

		Marine_Rotate();

		const auto& Body() const
		{
			return theBody_;
		}

		void Perform();

		void LoadBody(const std::shared_ptr<Marine_Body>& theBody)
		{
			theBody_ = theBody;
		}

		//- Macros
		GLOBAL_ACCESS_SINGLE(gp_Ax1, TrimAx)
			GLOBAL_ACCESS_SINGLE(gp_Ax1, HeelAx)

			GLOBAL_ACCESS_PRIM_SINGLE(Standard_Real, Trim)
			GLOBAL_ACCESS_PRIM_SINGLE(Standard_Real, Heel)
	};
}

#endif // !_Marine_Rotate_Header
