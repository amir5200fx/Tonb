#pragma once
#ifndef _StbGMaker_Volume_Header
#define _StbGMaker_Volume_Header

#include <StbGMaker_Entity.hxx>

namespace tnbLib
{

	// Forward Declarations
	class Marine_Body;


	class StbGMaker_Volume
		: public StbGMaker_Entity
	{

		/*Private Data*/

		std::shared_ptr<Marine_Body> theBody_;

	protected:

		StbGMaker_Volume
		(
			const std::shared_ptr<Marine_Body>& theBody
		);

		StbGMaker_Volume
		(
			const std::shared_ptr<Marine_Body>&& theBody
		);

		StbGMaker_Volume
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<Marine_Body>& theBody
		);

		StbGMaker_Volume
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<Marine_Body>&& theBody
		);

		StbGMaker_Volume
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::shared_ptr<Marine_Body>& theBody
		);

		StbGMaker_Volume
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::shared_ptr<Marine_Body>&& theBody
		);

	public:

		const auto& Body() const
		{
			return theBody_;
		}

		virtual Standard_Boolean IsHull() const
		{
			return Standard_False;
		}

		virtual Standard_Boolean IsTank() const
		{
			return Standard_False;
		}

		virtual Standard_Boolean IsSail() const
		{
			return Standard_False;
		}
	};
}

#endif // !_StbGMaker_Volume_Header
