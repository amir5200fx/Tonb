#pragma once
#ifndef _Cad_PolesNetPrcssr_Header
#define _Cad_PolesNetPrcssr_Header

#include <Cad_Module.hxx>
#include <Global_TypeDef.hxx>
#include <Global_Handle.hxx>
class Geom_BSplineSurface;

#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class Pnt3d;
	class Vec3d;

	class Cad_PolesNetPrcssr
	{

		/*Private Data*/

		Handle(Geom_BSplineSurface) theSurface_;

	public:

		//- default constructor

		Cad_PolesNetPrcssr()
		{}


		//- constructors

		Cad_PolesNetPrcssr(const Handle(Geom_BSplineSurface)& theSurface)
			: theSurface_(theSurface)
		{}


		//- public functions and operators

		const auto& Surface() const
		{
			return theSurface_;
		}

		TnbCad_EXPORT Standard_Integer NbRows() const;
		TnbCad_EXPORT Standard_Integer NbColumns() const;

		inline Standard_Integer NbVectorRows() const;
		inline Standard_Integer NbVectorColumns() const;

		TnbCad_EXPORT std::vector<std::pair<Pnt3d, Standard_Real>> FirstPoleRow() const;
		TnbCad_EXPORT std::vector<std::pair<Pnt3d, Standard_Real>> LastPoleRow() const;
		TnbCad_EXPORT std::vector<std::pair<Pnt3d, Standard_Real>> FirstPoleColumn() const;
		TnbCad_EXPORT std::vector<std::pair<Pnt3d, Standard_Real>> LastPoleColumn() const;

		//TnbCad_EXPORT std::pair<Pnt3d, Pnt3d> CalcVectorRow(const Standard_Integer theIndex) const;
		//TnbCad_EXPORT std::pair<Pnt3d, Pnt3d> CalcVectorColumn(const Standard_Integer theIndex) const;

		//TnbCad_EXPORT std::pair<Pnt3d, Pnt3d> CalcVectorRowRev(const Standard_Integer theIndex) const;
		//TnbCad_EXPORT std::pair<Pnt3d, Pnt3d> CalcVectorColumnRev(const Standard_Integer theIndex) const;

		TnbCad_EXPORT std::vector<std::pair<Pnt3d, Standard_Real>> PoleRow(const Standard_Integer) const;
		TnbCad_EXPORT std::vector<std::pair<Pnt3d, Standard_Real>> PoleColumn(const Standard_Integer) const;

		void SetSurface(const Handle(Geom_BSplineSurface)& theSurface)
		{
			theSurface_ = theSurface;
		}

	};
}

#include <Cad_PolesNetPrcssrI.hxx>

#endif // !_Cad_PolesNetPrcssr_Header
