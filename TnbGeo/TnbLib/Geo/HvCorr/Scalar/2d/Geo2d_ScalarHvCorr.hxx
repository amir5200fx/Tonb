#pragma once
#ifndef _Geo2d_ScalarHvCorr_Header
#define _Geo2d_ScalarHvCorr_Header

#include <Geo2d_GraphFwd.hxx>
#include <Entity2d_TriangulationFwd.hxx>
#include <Geo_Module.hxx>
#include <Global_Done.hxx>

#include <vector>

namespace tnbLib
{

	// Forward Declarations [5/29/2022 Amir]
	class Geo_ScalarHvCorrInfo;
	class Pnt2d;

	class Geo2d_ScalarHvCorr
		: public Global_Done
	{

		/*Private Data*/

		// inputs [5/29/2022 Amir]

		const std::shared_ptr<Geo2d_Graph>& theGraph_;
		std::vector<Standard_Real>& theSources_;

		std::shared_ptr<Geo_ScalarHvCorrInfo> theInfo_;

		Standard_Real(*LenFun)(const Standard_Real, const Pnt2d&, const Pnt2d&);
		Standard_Real(*SizeFunc)(const Pnt2d&);

		// results [5/29/2022 Amir]


		// private functions and operators [5/29/2022 Amir]

		auto& SourcesRef()
		{
			return theSources_;
		}



	public:

		static TnbGeo_EXPORT const std::shared_ptr<Geo_ScalarHvCorrInfo> DEFAULT_INFO;

		// default constructor [5/29/2022 Amir]


		// constructors [5/29/2022 Amir]

		Geo2d_ScalarHvCorr
		(
			const std::shared_ptr<Geo2d_Graph>& theGraph,
			std::vector<Standard_Real>& theSources,
			Standard_Real(*theLenFun)(const Standard_Real, const Pnt2d&, const Pnt2d&),
			Standard_Real(*theSizeFunc)(const Pnt2d&)
		)
			: theGraph_(theGraph)
			, theSources_(theSources)
			, LenFun(theLenFun)
			, SizeFunc(theSizeFunc)
			, theInfo_(DEFAULT_INFO)
		{}


		// public functions and operators [5/29/2022 Amir]

		const auto& Graph() const
		{
			return theGraph_;
		}

		const auto& Sources() const
		{
			return theSources_;
		}

		const auto& CorrInfo() const
		{
			return theInfo_;
		}

		TnbGeo_EXPORT void Perform();

		void SetInfo(const std::shared_ptr<Geo_ScalarHvCorrInfo>& theInfo)
		{
			theInfo_ = theInfo;
		}

		void SetInfo(std::shared_ptr<Geo_ScalarHvCorrInfo>&& theInfo)
		{
			theInfo_ = std::move(theInfo);
		}
	};
}

#endif // !_Geo2d_ScalarHvCorr_Header
