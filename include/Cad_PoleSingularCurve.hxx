#pragma once
#ifndef _Cad_PoleSingularCurve_Header
#define _Cad_PoleSingularCurve_Header

#include <Cad_SingularCurve.hxx>
#include <Pnt2d.hxx>

namespace tnbLib
{

	template<class CurveType>
	class Cad_PoleSingularCurve
		: public Cad_SingularCurve<CurveType>
	{

	public:

		typedef typename cad_singular_curve_traits<CurveType>::baseCurveType baseCurveType;

	private:

		/*Private Data*/

		Pnt2d theMid_;

		// private functions and operators [12/31/2021 Amir]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & boost::serialization::base_object<Cad_SingularCurve<CurveType>>(*this);
			ar & theMid_;
		}

	public:

		//typedef typename CurveType::geomType geomType;

		// default constructor [12/31/2021 Amir]


		// constructors [12/31/2021 Amir]

		explicit Cad_PoleSingularCurve(const std::shared_ptr<baseCurveType>& theCurve)
			: Cad_SingularCurve<CurveType>(theCurve)
			, theMid_(Pnt2d::null)
		{}

		Cad_PoleSingularCurve(const std::shared_ptr<baseCurveType>& theCurve, const Pnt2d& theMid)
			: Cad_SingularCurve<CurveType>(theCurve)
			, theMid_(theMid)
		{}

		Cad_PoleSingularCurve(std::shared_ptr<baseCurveType>&& theCurve)
			: Cad_SingularCurve<CurveType>(std::move(theCurve))
			, theMid_(Pnt2d::null)
		{}

		Cad_PoleSingularCurve(std::shared_ptr<baseCurveType>&& theCurve, Pnt2d&& theMid)
			: Cad_SingularCurve<CurveType>(std::move(theCurve))
			, theMid_(std::move(theMid))
		{}


		// override functions and operators [3/30/2022 Amir]

		Standard_Boolean IsPole() const override
		{
			return Standard_True;
		}

		Standard_Boolean HasSubcurves() const override
		{
			return Standard_False;
		}

		void CalcSubcurves() const override;

		// public functions and operators [12/31/2021 Amir]

		const auto& MidCoord() const
		{
			return theMid_;
		}

		void SetMidCoord(const Pnt2d& theCoord)
		{
			theMid_ = theCoord;
		}

		void SetMidCoord(Pnt2d&& theCoord)
		{
			theMid_ = std::move(theCoord);
		}
	};
}

#include <Cad_PoleSingularCurveI.hxx>

#endif // !_Cad_PoleSingularCurve_Header
