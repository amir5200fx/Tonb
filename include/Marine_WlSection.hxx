#pragma once
#ifndef _Marine_WlSection_Header
#define _Marine_WlSection_Header

#include <Marine_Section.hxx>

namespace tnbLib
{

	class Marine_WlSection
		: public Marine_Section
	{

		/*Private Data*/

	public:

		Marine_WlSection
		(
			const std::shared_ptr<Pln_Wire>& theWire
		);

		Marine_WlSection
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<Pln_Wire>& theWire
		);

		Marine_WlSection
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::shared_ptr<Pln_Wire>& theWire
		);


		Standard_Boolean IsWaterLine() const override
		{
			return Standard_True;
		}

		std::shared_ptr<Marine_Section> Copy() const override;
	};
}

#endif // !_Marine_WlSection_Header
