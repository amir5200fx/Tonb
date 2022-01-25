#pragma once
#ifndef _Cad_CurveSplitter_Header
#define _Cad_CurveSplitter_Header

#include <Global_Done.hxx>
#include <Cad_Module.hxx>

#include <Standard_Handle.hxx>

// Forward Declarations [1/16/2022 Amir]
class Geom_Curve;

namespace tnbLib
{

	// Forward Declarations [1/20/2022 Amir]
	class Cad_CurveSplitter_Info;

	class Cad_CurveSplitter
		: public Global_Done
	{

		/*Private Data*/


		// inputs [1/20/2022 Amir]

		Handle(Geom_Curve) theCurve_;

		std::shared_ptr<Cad_CurveSplitter_Info> theInfo_;

		Standard_Integer theNbSegments_;

		// results [1/20/2022 Amir]
		std::vector<Standard_Real> theParameters_;

	public:

		static TnbCad_EXPORT const std::shared_ptr<Cad_CurveSplitter_Info> DEFAULT_INFO;
		static TnbCad_EXPORT const Standard_Integer DEFAULT_NB_SEGMENTS;

		// default constructor [1/16/2022 Amir]

		Cad_CurveSplitter()
		{}


		// constructors [1/16/2022 Amir]

		explicit Cad_CurveSplitter
		(
			const Handle(Geom_Curve)& theGeometry,
			const Standard_Integer theNbSegments = DEFAULT_NB_SEGMENTS
		)
			: theCurve_(theGeometry)
			, theNbSegments_(theNbSegments)
		{}

		Cad_CurveSplitter
		(
			const Handle(Geom_Curve)& theGeometry,
			const Standard_Integer theNbSegments,
			const std::shared_ptr<Cad_CurveSplitter_Info>& theInfo
		)
			: theCurve_(theGeometry)
			, theNbSegments_(theNbSegments)
			, theInfo_(theInfo)
		{}

		// public functions and operators [1/16/2022 Amir]

		const auto& GetInfo() const
		{
			return theInfo_;
		}

		const auto& Curve() const
		{
			return theCurve_;
		}

		auto NbSegments() const
		{
			return theNbSegments_;
		}

		const auto& ResultsPrameters() const
		{
			return theParameters_;
		}

		TnbCad_EXPORT void Perform(const Standard_Real theU0, const Standard_Real theU1);
		TnbCad_EXPORT void Perform();

		void SetCurve(const Handle(Geom_Curve)& theGeometry)
		{
			theCurve_ = theGeometry;
		}

		void SetNbSegments(const Standard_Integer theNbSegments)
		{
			theNbSegments_ = theNbSegments;
		}

		void OverrideInfo(const std::shared_ptr<Cad_CurveSplitter_Info>& theInfo)
		{
			theInfo_ = theInfo;
		}
	};
}

#endif // !_Cad_CurveSplitter_Header
