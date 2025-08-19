#pragma once
#ifndef _Voyage_AdaptPath_Header
#define _Voyage_AdaptPath_Header

#include <Voyage_Module.hxx>
#include <Entity2d_PolygonFwd.hxx>
#include <Global_Done.hxx>

#include <memory>
#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class Voyage_AdaptPath_Info;
	
	class Voyage_AdaptPath
		: public Global_Done
	{

	public:

		typedef  std::shared_ptr<Entity2d_Polygon> SubPath;

	private:

		/*Private Data*/

		std::vector<SubPath> thePath_;
		std::shared_ptr<Voyage_AdaptPath_Info> theInfo_;

		// results

		std::vector<SubPath> theRefined_;


		// Private functions and operators

		TnbVoyage_EXPORT std::vector<Pnt2d> SubPoints(const Pnt2d& THeP0, const Pnt2d& theP1) const;
		TnbVoyage_EXPORT std::pair<SubPath, SubPath> Subdivide(const SubPath& thePath0, const SubPath& thePath1) const;
		static TnbVoyage_EXPORT SubPath Copy(const SubPath&);
		static TnbVoyage_EXPORT std::vector<SubPath> Copy(const std::vector<SubPath>&);

	public:

		// default constructor

		Voyage_AdaptPath() = default;

		// constructors

		TnbVoyage_EXPORT Voyage_AdaptPath
		(
			const std::vector<std::shared_ptr<Entity2d_Polygon>>& thePath,
			const std::shared_ptr<Voyage_AdaptPath_Info>& theInfo
		)
			: thePath_(thePath)
			, theInfo_(theInfo)
		{}

		// Public functions and operators

		const auto& Path() const { return thePath_; }
		const auto& GetInfo() const { return theInfo_; }

		const auto& Refined() const { return theRefined_; }

		TnbVoyage_EXPORT void Perform();

		void SetPath(const std::vector<std::shared_ptr<Entity2d_Polygon>>& thePath) { thePath_ = thePath; }
		void SetPath(std::vector<std::shared_ptr<Entity2d_Polygon>>&& thePath) { thePath_ = std::move(thePath); }
		void SetInfo(const std::shared_ptr<Voyage_AdaptPath_Info>& theInfo) { theInfo_ = theInfo; }
		
	};
}

#endif