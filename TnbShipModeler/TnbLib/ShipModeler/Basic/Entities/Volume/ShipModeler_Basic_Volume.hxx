#pragma once
#ifndef _ShipModeler_Basic_Volume_Header
#define _ShipModeler_Basic_Volume_Header

#include <ShipModeler_Basic_Entity.hxx>

namespace tnbLib
{

	// Forward Declarations
	class Marine_Body;

	namespace shipModelerLib
	{

		class Basic_Volume
			: public Basic_Entity
		{

			/*Private Data*/

			std::shared_ptr<Marine_Body> theBody_;

		protected:

			Basic_Volume
			(
				const std::shared_ptr<Marine_Body>& theBody
			);

			Basic_Volume
			(
				const std::shared_ptr<Marine_Body>&& theBody
			);

			Basic_Volume
			(
				const Standard_Integer theIndex,
				const std::shared_ptr<Marine_Body>& theBody
			);

			Basic_Volume
			(
				const Standard_Integer theIndex,
				const std::shared_ptr<Marine_Body>&& theBody
			);

			Basic_Volume
			(
				const Standard_Integer theIndex,
				const word& theName,
				const std::shared_ptr<Marine_Body>& theBody
			);

			Basic_Volume
			(
				const Standard_Integer theIndex,
				const word& theName,
				const std::shared_ptr<Marine_Body>&& theBody
			);

		public:

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
}

#endif // !_ShipModeler_Basic_Volume_Header
