#pragma once
#ifndef _Cad2d_IntsctEntity_OrthSegment_Header
#define _Cad2d_IntsctEntity_OrthSegment_Header

#include <Cad2d_IntsctEntity_Segment.hxx>
#include <Pnt2d.hxx>
#include <Cad2d_Module.hxx>

namespace tnbLib
{

	// Forward Declarations
	class Pln_Curve;

	class Cad2d_IntsctEntity_OrthSegment
		: public Cad2d_IntsctEntity_Segment
	{

		/*Private Data*/

		Standard_Real theParameter_;

		Pnt2d theCoord_;

	public:

		TnbCad2d_EXPORT Cad2d_IntsctEntity_OrthSegment();

		TnbCad2d_EXPORT Cad2d_IntsctEntity_OrthSegment(const Standard_Integer theIndex);

		TnbCad2d_EXPORT Cad2d_IntsctEntity_OrthSegment(const Standard_Integer theIndex, const word& theName);


		Standard_Boolean IsOrthogonal() const override
		{
			return Standard_True;
		}

		Standard_Real CharParameter() const override
		{
			return theParameter_;
		}

		static TnbCad2d_EXPORT std::tuple<std::shared_ptr<Pln_Curve>, std::shared_ptr<Pln_Curve>>
			SubdivideCurve
			(
				const Pln_Curve& theCurve, 
				const Cad2d_IntsctEntity_OrthSegment& theEntity
			);


		//- Macros
		GLOBAL_ACCESS_PRIM_SINGLE(Standard_Real, Parameter)

			GLOBAL_ACCESS_SINGLE(Pnt2d, Coord)
	};
}

#endif // !_Cad2d_IntsctEntity_OrthSegment_Header
