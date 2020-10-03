#pragma once
#ifndef _SectPx_Maker_Header
#define _SectPx_Maker_Header

#include <SectPx_Entity.hxx>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_Registry;

	class SectPx_Maker
		: public SectPx_Entity
	{

		/*Private Data*/

		const std::shared_ptr<SectPx_Registry>& theRegistry_;

	protected:

		SectPx_Maker
		(
			const std::shared_ptr<SectPx_Registry>& theReg
		)
			: theRegistry_(theReg)
		{}


	public:

		const auto& Registry() const
		{
			return theRegistry_;
		}

	};
}

#endif // !_SectPx_Maker_Header
