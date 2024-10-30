#pragma once
#ifndef _Voyage_SizeMap_Header
#define _Voyage_SizeMap_Header

#include <Voyage_Module.hxx>
#include <Geo2d_SizeFunctionFwd.hxx>
#include <Global_Done.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations [9/3/2023 Payvand]
	class VoyageMesh_BaseSizeInfo;
	class Voyage_MetricInfo;
	class VoyageGeo_Path2;

	class Voyage_SizeMap
		: public Global_Done
	{
	

		/*Private Data*/

		std::shared_ptr<VoyageMesh_BaseSizeInfo> theSizeDistb_;

		std::shared_ptr<VoyageGeo_Path2> thePath_;
		std::shared_ptr<Voyage_MetricInfo> theInfo_;

		// results [9/3/2023 Payvand]

		std::shared_ptr<Geo2d_SizeFunction> theStarboard_;
		std::shared_ptr<Geo2d_SizeFunction> thePort_;

	public:

		static TnbVoyage_EXPORT unsigned short verbose;
		

		// default constructor [9/3/2023 Payvand]

		Voyage_SizeMap()
		= default;

		// constructors [9/3/2023 Payvand]

		Voyage_SizeMap
		(
			const std::shared_ptr<VoyageGeo_Path2>& thePath, 
			const std::shared_ptr<Voyage_MetricInfo>& theInfo,
			const std::shared_ptr<VoyageMesh_BaseSizeInfo>& theSizeDistb
		)
			: thePath_(thePath)
			, theInfo_(theInfo)
			, theSizeDistb_(theSizeDistb)
		{}

		// Public functions and operators [9/3/2023 Payvand]

		const auto& Path() const { return thePath_; }
		const auto& GetInfo() const { return theInfo_; }

		const auto& Startboard() const { return theStarboard_; }
		const auto& Port() const { return thePort_; }

		TnbVoyage_EXPORT void Perform();

		void SetPath(const std::shared_ptr<VoyageGeo_Path2>& thePath) { thePath_ = thePath; }
		void SetInfo(const std::shared_ptr<Voyage_MetricInfo>& theInfo) { theInfo_ = theInfo; }
		void SetSizeDistb(const std::shared_ptr<VoyageMesh_BaseSizeInfo>& theSizeDistb) { theSizeDistb_ = theSizeDistb; }


	};

}

#endif // !_Voyage_SizeMap_Header
