#pragma once
#ifndef _SectPx_Pnt_Header
#define _SectPx_Pnt_Header

#include <SectPx_Coord.hxx>
#include <SectPx_Parent.hxx>
#include <SectPx_PntType.hxx>

namespace tnbLib
{

	class SectPx_Pnt
		: public SectPx_Coord
		, public SectPx_Parent
	{

		/*Private Data*/

	protected:

		template<class... _Types>
		SectPx_Pnt(_Types&&... _Args)
			: SectPx_Parent(_Args...)
		{}

	public:

		virtual Standard_Boolean IsInner() const;

		virtual Standard_Boolean IsOuter() const;

		virtual Standard_Boolean IsMaster() const;

		virtual Standard_Boolean IsSlave() const;

		virtual Standard_Boolean IsBoundary() const
		{
			return Standard_False;
		}

		virtual sectPxLib::pntType PntType() const = 0;

		Standard_Boolean IsPnt() const override;

		sectPxLib::regObjType RegObjType() const override;

	};
}

#endif // !_SectPx_Pnt_Header
