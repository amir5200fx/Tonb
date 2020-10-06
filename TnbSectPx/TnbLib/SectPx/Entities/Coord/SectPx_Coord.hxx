#pragma once
#ifndef _SectPx_Coord_Header
#define _SectPx_Coord_Header

#include <Pnt2d.hxx>
#include <SectPx_ParentAdaptor.hxx>

#include <memory>

namespace tnbLib
{

	class SectPx_Coord
		/*: public SectPx_ParentAdaptor*/
	{

		/*Private Data*/

	protected:

		SectPx_Coord()
		{}

	public:

		virtual Standard_Real xCoord() const = 0;

		virtual Standard_Real yCoord() const = 0;

		virtual Pnt2d Coord() const = 0;

		virtual Standard_Boolean IsComplete() const = 0;

		virtual Standard_Boolean IsDatum() const;
	};
}

#endif // !_SectPx_Coord_Header
