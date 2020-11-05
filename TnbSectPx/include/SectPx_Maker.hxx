#pragma once
#ifndef _SectPx_Maker_Header
#define _SectPx_Maker_Header

#include <SectPx_Entity.hxx>
#include <SectPx_Module.hxx>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_Registry;

	class SectPx_Maker
		: public SectPx_Entity
	{

		/*Private Data*/

		std::shared_ptr<SectPx_Registry> theRegistry_;


		DECLARE_SAVE_LOAD_HEADER(TnbSectPx_EXPORT);


	protected:

		SectPx_Maker()
		{}

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
