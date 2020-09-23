#pragma once
#ifndef _SectPx_GeoMap_Header
#define _SectPx_GeoMap_Header

#include <SectPx_Parent.hxx>
#include <Pnt2d.hxx>

#include <memory>

namespace tnbLib
{

	class SectPx_GeoMap
		: public SectPx_Parent
	{

		/*Private Data*/

	protected:

		template<class... _Types>
		SectPx_GeoMap(_Types&&... _Args)
			: SectPx_Parent(_Args...)
		{}

	public:

		Standard_Boolean IsGeoMap() const override;

		sectPxLib::regObjType RegObjType() const override;

		virtual Standard_Boolean IsComplete() const = 0;

		virtual Pnt2d CalcCoord() const = 0;
	};
}

#endif // !_SectPx_GeoMap_Header
