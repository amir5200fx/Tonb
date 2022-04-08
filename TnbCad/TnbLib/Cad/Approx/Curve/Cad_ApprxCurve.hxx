#pragma once
#ifndef _Cad_ApprxCurve_Header
#define _Cad_ApprxCurve_Header

#include <Global_Done.hxx>
#include <Geo_ApprxCurve.hxx>

#include <memory>

#include <Standard_Handle.hxx>

namespace tnbLib
{

	template<class CurveType, bool RandSamples>
	class Cad_ApprxCurve
		: public Global_Done
	{

	public:

		typedef typename CurveType::geomType geomType;
		typedef typename Geo_ApprxCurve<Handle(geomType), RandSamples>::Point Point;		

	private:

		/*Private Data*/

		// inputs [4/4/2022 Amir]
		std::shared_ptr<CurveType> theCurve_;
		std::shared_ptr<Geo_ApprxCurve_Info> theInfo_;

		// outputs [4/4/2022 Amir]
		std::shared_ptr<Entity_Polygon<Point>> thePolygon_;


		// private functions and operators [4/4/2022 Amir]

		auto& PolygonRef()
		{
			return thePolygon_;
		}

	public:

		// default constructor [4/4/2022 Amir]

		Cad_ApprxCurve()
		{}


		// constructors [4/4/2022 Amir]

		Cad_ApprxCurve
		(
			const std::shared_ptr<CurveType>& theCurve,
			const std::shared_ptr<Geo_ApprxCurve_Info>& theInfo
		)
			: theCurve_(theCurve)
			, theInfo_(theInfo)
		{}


		// public functions and operators [4/4/2022 Amir]

		const auto& Curve() const
		{
			return theCurve_;
		}

		const auto& AlgInfo() const
		{
			return theInfo_;
		}

		const auto& Polygon() const
		{
			return thePolygon_;
		}

		void Perform();

		void SetCurve(const std::shared_ptr<CurveType>& theCurve)
		{
			theCurve_ = theCurve;
		}

		void SetInfo(const std::shared_ptr<Geo_ApprxCurve_Info>& theInfo)
		{
			theInfo_ = theInfo;
		}

	};
}

#include <Cad_ApprxCurveI.hxx>

#endif // !_Cad_ApprxCurve_Header
