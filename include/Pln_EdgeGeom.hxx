#pragma once
#ifndef _Pln_EdgeGeom_Header
#define _Pln_EdgeGeom_Header

#include <Standard_TypeDef.hxx>
#include <Entity2d_PolygonFwd.hxx>
#include <Global_AccessMethod.hxx>
#include <Global_Serialization.hxx>
#include <Cad2d_Module.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations
	class Pln_Curve;
	class Geo_ApprxCurve_Info;

	class Pln_EdgeGeom
	{

		/*Private Data*/

		std::shared_ptr<Pln_Curve> theCurve_;

		Standard_Boolean Sense_;

		mutable std::shared_ptr<Entity2d_Polygon> theMesh_;


		/*private functions and operators*/

		TNB_SERIALIZATION(TnbCad2d_EXPORT);

	protected:

		Pln_EdgeGeom()
			: Sense_(Standard_True)
		{}

		Pln_EdgeGeom
		(
			const Standard_Boolean theSense
		)
			: Sense_(theSense)
		{}

		Pln_EdgeGeom
		(
			const std::shared_ptr<Pln_Curve>& theCurve,
			const Standard_Boolean theSense
		)
			: theCurve_(theCurve)
			, Sense_(theSense)
		{}

		Pln_EdgeGeom
		(
			const std::shared_ptr<Pln_Curve>&& theCurve,
			const Standard_Boolean theSense
		)
			: theCurve_(std::move(theCurve))
			, Sense_(theSense)
		{}

		Standard_Boolean& ChangeSense()
		{
			return Sense_;
		}

	public:

		Standard_Boolean Sense() const
		{
			return Sense_;
		}

		TnbCad2d_EXPORT Pnt2d FirstCoord() const;
		TnbCad2d_EXPORT Pnt2d LastCoord() const;

		TnbCad2d_EXPORT Pnt2d FirstCoord(const Standard_Boolean theSense) const;
		TnbCad2d_EXPORT Pnt2d LastCoord(const Standard_Boolean theSense) const;

		std::shared_ptr<Entity2d_Polygon>& Mesh() const
		{
			return theMesh_;
		}

		TnbCad2d_EXPORT void Approx
		(
			const std::shared_ptr<Geo_ApprxCurve_Info>& theInfo
		) const;

		void ClearMesh()
		{
			Mesh().reset();
		}

		void set_curve(const std::shared_ptr<Pln_Curve> & c)
		{
			theCurve_ = c;
		}

		//- Macros
		GLOBAL_ACCESS_SINGLE(std::shared_ptr<Pln_Curve>, Curve)
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::Pln_EdgeGeom);

#endif // !_Pln_EdgeGeom_Header