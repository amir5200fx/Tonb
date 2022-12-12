#pragma once
#ifndef _Cad_ParaDegenCurve_Header
#define _Cad_ParaDegenCurve_Header

#include <word.hxx>
#include <Global_Serialization.hxx>

#include <Standard_TypeDef.hxx>
#include <Standard_Handle.hxx>

class Geom2d_Curve;

namespace tnbLib
{

	// Forward Declarations [12/12/2022 Payvand]
	class Cad_ParaCurve;

	template<class CurveType>
	class Cad_ParaDegenCurve
		: public CurveType
	{

		/*Private Data*/

		// private functions and operators [12/12/2022 Payvand]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar& boost::serialization::base_object<CurveType>(*this);
		}


	public:

		// default constructor [12/12/2022 Payvand]

		Cad_ParaDegenCurve()
		{}


		// constructors [12/12/2022 Payvand]

		explicit Cad_ParaDegenCurve(const Handle(Geom2d_Curve)& theGeometry)
			: CurveType(theGeometry)
		{}

		Cad_ParaDegenCurve(const Standard_Integer theIndex, const Handle(Geom2d_Curve)& theGeoemtry)
			: CurveType(theIndex, theGeoemtry)
		{}

		Cad_ParaDegenCurve
		(
			const Standard_Integer theIndex,
			const word& theName,
			const Handle(Geom2d_Curve)& theGeoemtry
		)
			: CurveType(theIndex, theName, theGeoemtry)
		{}

		Cad_ParaDegenCurve(Handle(Geom2d_Curve) && theGeometry)
			: CurveType(std::move(theGeometry))
		{}

		Cad_ParaDegenCurve
		(
			const Standard_Integer theIndex,
			Handle(Geom2d_Curve) && theGeometry
		)
			: CurveType(theIndex, std::move(theGeometry))
		{}

		Cad_ParaDegenCurve
		(
			const Standard_Integer theIndex,
			const word& theName,
			Handle(Geom2d_Curve) && theGeometry
		)
			: CurveType(theIndex, theName, std::move(theGeometry))
		{}


		// override functions and operators [12/12/2022 Payvand]

		Standard_Boolean IsDegenerated() const override
		{
			return Standard_True;
		}

		std::shared_ptr<CurveType>
			CreateCurve
			(
				const Standard_Integer theIndex,
				const word& theName, 
				const Handle(Geom2d_Curve)& theGeometry
			) const override;

		// public functions and operators [12/12/2022 Payvand]


	};
}

#include <Cad_ParaDegenCurveI.hxx>

#endif // !_Cad_ParaDegenCurve_Header
