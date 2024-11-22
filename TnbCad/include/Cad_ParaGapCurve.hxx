#pragma once
#ifndef _Cad_ParaGapCurve_Header
#define _Cad_ParaGapCurve_Header

#include <word.hxx>
#include <Global_Serialization.hxx>
#include <Global_TypeDef.hxx>
#include <Global_Handle.hxx>

class Geom2d_Curve;

namespace tnbLib
{

	template<class CurveType>
	class Cad_ParaGapCurve
		: public CurveType
	{

		/*Private Data*/



		// private functions and operators [5/12/2022 Amir]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar & boost::serialization::base_object<CurveType>(*this);
		}

	public:

		// default constructor [5/12/2022 Amir]

		Cad_ParaGapCurve()
		{}


		// constructors [5/12/2022 Amir]

		explicit Cad_ParaGapCurve(const Handle(Geom2d_Curve)& theGeometry)
			: CurveType(theGeometry)
		{}

		Cad_ParaGapCurve(const Standard_Integer theIndex, const Handle(Geom2d_Curve)& theGeoemtry)
			: CurveType(theIndex, theGeoemtry)
		{}

		Cad_ParaGapCurve
		(
			const Standard_Integer theIndex, 
			const word& theName, 
			const Handle(Geom2d_Curve)& theGeoemtry
		)
			: CurveType(theIndex, theName, theGeoemtry)
		{}

		Cad_ParaGapCurve(Handle(Geom2d_Curve)&& theGeometry)
			: CurveType(std::move(theGeometry))
		{}

		Cad_ParaGapCurve
		(
			const Standard_Integer theIndex,
			Handle(Geom2d_Curve) && theGeometry
		)
			: CurveType(theIndex, std::move(theGeometry))
		{}

		Cad_ParaGapCurve
		(
			const Standard_Integer theIndex,
			const word& theName,
			Handle(Geom2d_Curve) && theGeometry
		)
			: CurveType(theIndex, theName, std::move(theGeometry))
		{}


		// override functions and operators [5/12/2022 Amir]

		Standard_Boolean IsGap() const override
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

		// public functions and operators [5/12/2022 Amir]


		
	};
}

#include <Cad_ParaGapCurveI.hxx>

#endif // !_Cad_ParaGapCurve_Header
