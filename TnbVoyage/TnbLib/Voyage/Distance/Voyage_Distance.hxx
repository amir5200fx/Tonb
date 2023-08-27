#pragma once
#ifndef _Voyage_Distance_Header
#define _Voyage_Distance_Header

#include <Global_Done.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations [8/26/2023 aamir]
	class VoyageGeo_Path2;
	class Voyage_MetricInfo;
	class Mesh_Curve_Info;

	class Voyage_Distance
		: public Global_Done
	{

		/*Private Data*/

		std::shared_ptr<VoyageGeo_Path2> thePath_;
		std::shared_ptr<Voyage_MetricInfo> theInfo_;

		// results [8/26/2023 aamir]
		Standard_Real theValue_;

	public:

		// default constructor [8/26/2023 aamir]

		Voyage_Distance()
		{}

		// constructors [8/26/2023 aamir]

		Voyage_Distance
		(
			const std::shared_ptr<VoyageGeo_Path2>& thePath, 
			const std::shared_ptr<Voyage_MetricInfo>& theInfo
		)
			: thePath_(thePath)
			, theInfo_(theInfo)
		{}

		// Public functions and operators [8/26/2023 aamir]

		const auto& Path() const { return thePath_; }
		const auto& GetInfo() const { return theInfo_; }

		Standard_Real Value() const;

		void Perform();

		void SetPath(const std::shared_ptr<VoyageGeo_Path2>& thePath) { thePath_ = thePath; }
		void SetInfo(const std::shared_ptr<Voyage_MetricInfo>& theInfo) { theInfo_ = theInfo; }
	};
}

#endif // !_Voyage_Distance_Header
