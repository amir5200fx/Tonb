#pragma once
#ifndef _SectPx_Curve_Header
#define _SectPx_Curve_Header

#include <Standard_Handle.hxx>
#include <Global_Done.hxx>

class Geom2d_Curve;

#include <memory>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_TopoProfile;
	class SectPx_KnotVector;

	class SectPx_Curve
		: public Global_Done
	{

		/*Private Data*/

		Handle(Geom2d_Curve) theCurve_;

		std::shared_ptr<SectPx_TopoProfile> theProfile_;
		std::shared_ptr<SectPx_KnotVector> theKnotAlg_;


		auto& ChangeGeometry()
		{
			return theCurve_;
		}

	public:

		SectPx_Curve()
		{}

		SectPx_Curve
		(
			const std::shared_ptr<SectPx_TopoProfile>& theProfile,
			const std::shared_ptr<SectPx_KnotVector>& theKnotAlg
		)
			: theProfile_(theProfile)
			, theKnotAlg_(theKnotAlg)
		{}

		const auto& Geometry() const
		{
			return theCurve_;
		}

		const auto& Profile() const
		{
			return theProfile_;
		}

		const auto& KnotAlg() const
		{
			return theKnotAlg_;
		}

		void Perform(const Standard_Integer deg);

		void LoadProfile(const std::shared_ptr<SectPx_TopoProfile>& theProfile)
		{
			theProfile_ = theProfile;
		}

		void LoadKnotAlg(const std::shared_ptr<SectPx_KnotVector>& theAlg)
		{
			theKnotAlg_ = theAlg;
		}
	};
}

#endif // !_SectPx_Curve_Header
