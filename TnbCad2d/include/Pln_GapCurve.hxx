#pragma once
#ifndef _Pln_GapCurve_Header
#define _Pln_GapCurve_Header

#include <Pln_Curve.hxx>

namespace tnbLib
{

	class Pln_GapCurve
		: public Pln_Curve
	{

		/*Private Data*/


		// Private functions and operators [1/24/2023 Payvand]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar& boost::serialization::base_object<Pln_Curve>(*this);
		}

	public:

		// default constructor [1/24/2023 Payvand]

		Pln_GapCurve()
		{}

		// constructors [1/24/2023 Payvand]

		Pln_GapCurve(const Standard_Integer theIndex, const Handle(Geom2d_Curve)& theGeom)
			: Pln_Curve(theIndex, theGeom)
		{}

		Pln_GapCurve(const Standard_Integer theIndex, Handle(Geom2d_Curve)&& theGeom)
			: Pln_Curve(theIndex, std::move(theGeom))
		{}

		explicit Pln_GapCurve(const Handle(Geom2d_Curve)& theGeom)
			: Pln_Curve(theGeom)
		{}

		Pln_GapCurve(Handle(Geom2d_Curve)&& theGeom)
			: Pln_Curve(std::move(theGeom))
		{}

		Pln_GapCurve
		(
			const Standard_Integer theIndex,
			const word& theName, 
			const Handle(Geom2d_Curve)& theGeom
		)
			: Pln_Curve(theIndex, theName, theGeom)
		{}

		Pln_GapCurve
		(
			const Standard_Integer theIndex,
			const word& theName,
			Handle(Geom2d_Curve)&& theGeom
		)
			: Pln_Curve(theIndex, theName, std::move(theGeom))
		{}


		// Public functions and operators [1/24/2023 Payvand]

		inline Standard_Boolean IsGap() const override;

		TnbCad2d_EXPORT std::shared_ptr<Pln_Curve> 
			CreateCurve
			(
				const Standard_Integer theIndex,
				const word& theName,
				const Handle(Geom2d_Curve)&
			) const override;
	};
}

#include <Pln_GapCurveI.hxx>

#endif // !_Pln_GapCurve_Header
