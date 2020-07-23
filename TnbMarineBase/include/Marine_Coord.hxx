#pragma once
#ifndef _Marine_Coord_Header
#define _Marine_Coord_Header

#include <Marine_Entity.hxx>
#include <Pnt3d.hxx>

namespace tnbLib
{

	class Marine_Coord
		: public Marine_Entity
	{

		/*Private Data*/

		Pnt3d theCoord_;

	public:

		Marine_Coord
		(
			const Pnt3d& theCoord
		);

		Marine_Coord
		(
			Pnt3d&& theCoord
		);

		Marine_Coord
		(
			const Standard_Integer theIndex, 
			const word& theName, 
			const Pnt3d& theCoord
		);

		Marine_Coord
		(
			const Standard_Integer theIndex, 
			const word& theName,
			Pnt3d&& theCoord
		);

		const auto& Value() const
		{
			return theCoord_;
		}

		auto& Value()
		{
			return theCoord_;
		}

		void SetValue(const Pnt3d& theCoord)
		{
			theCoord_ = theCoord;
		}

		void SetValue(Pnt3d&& theCoord)
		{
			theCoord_ = std::move(theCoord);
		}
	};
}

#endif // !_Marine_Coord_Header
