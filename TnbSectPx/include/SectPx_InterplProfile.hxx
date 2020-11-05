#pragma once
#ifndef _SectPx_InterplProfile_Header
#define _SectPx_InterplProfile_Header

#include <Pnt2d.hxx>
#include <SectPx_TopoProfile.hxx>

#include <vector>

class Geom2d_BSplineCurve;

namespace tnbLib
{

	// Forward Declarations
	class SectPx_Cloud;
	class SectPx_Pnt;

	class SectPx_InterplProfile
		: public SectPx_TopoProfile
	{

		/*Private Data*/

		std::vector<std::weak_ptr<SectPx_Pnt>> thePnts_;

		std::weak_ptr<SectPx_Cloud> theCloud_;

		Standard_Real theTol_;

		//- private functions and operators


		DECLARE_SAVE_LOAD_HEADER(TnbSectPx_EXPORT);

		const auto& Pnts() const
		{
			return thePnts_;
		}

		const auto& Cloud() const
		{
			return theCloud_;
		}

		void SetPnts
		(
			std::vector<std::weak_ptr<SectPx_Pnt>>&& thePnts
		)
		{
			thePnts_ = std::move(thePnts);
		}

		void SetCloud
		(
			const std::shared_ptr<SectPx_Cloud>& theCloud
		)
		{
			theCloud_ = theCloud;
		}

		void Update() const override;

		static std::vector<Standard_Real> 
			RetrieveKnots
			(
				const Geom2d_BSplineCurve&
			);

		static std::vector<Pnt2d> 
			RetrievePoles
			(
				const Geom2d_BSplineCurve&
			);

	public:

		static const char* typeName_;

		template<class... _Types>
		SectPx_InterplProfile(_Types&&... _Args)
			: SectPx_TopoProfile(_Args...)
		{}


		word RegObjTypeName() const override;

		static std::shared_ptr<SectPx_InterplProfile> 
			MakeProfile
			(
				const std::shared_ptr<SectPx_Cloud>& theProfile,
				const std::shared_ptr<SectPx_Registry>& theReg,
				const Standard_Real tol = 1.0E-6
			);
	};
}

#endif // !_SectPx_InterplProfile_Header
