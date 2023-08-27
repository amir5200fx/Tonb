#pragma once
#ifndef _Voyage_PathDiscret_Header
#define _Voyage_PathDiscret_Header

#include <Voyage_Module.hxx>
#include <Global_Done.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations [8/26/2023 Payvand]
	class VoyageGeo_Path2;
	class Voyage_MetricInfo;

	class Voyage_PathDiscret
		: public Global_Done
	{

		/*Private Data*/

		std::shared_ptr<VoyageGeo_Path2> thePath_;
		std::shared_ptr<Voyage_MetricInfo> theInfo_;

		Standard_Real theSize_;

	public:

		// default constructor [8/26/2023 Payvand]

		Voyage_PathDiscret()
			: theSize_(0)
		{}

		Voyage_PathDiscret
		(
			const std::shared_ptr<VoyageGeo_Path2>& thePath, 
			const std::shared_ptr<Voyage_MetricInfo>& theInfo,
			const Standard_Real theSize
		)
			: thePath_(thePath)
			, theSize_(theSize)
			, theInfo_(theInfo_)
		{}


		// Public functions and operators [8/26/2023 Payvand]

		const auto& Path() const { return thePath_; }
		const auto& AlgInfo() const { return theInfo_; }

		auto Size() const { return theSize_; }

		TnbVoyage_EXPORT void Perform();

		void SetPath(const std::shared_ptr<VoyageGeo_Path2>& thePath) { thePath_ = thePath; }
		void SetSize(const Standard_Real theSize) { theSize_ = theSize; }
		void OverrideInfo(const std::shared_ptr<Voyage_MetricInfo>& theInfo) { theInfo_ = theInfo; }
	};
}

#endif // !_Voyage_PathDiscret_Header
