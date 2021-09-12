#pragma once
#ifndef _ShapePx_TopoCtrlNet_Header
#define _ShapePx_TopoCtrlNet_Header

#include <ShapePx_Entity.hxx>

#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class ShapePx_TopoSection;

	class ShapePx_TopoCtrlNet
		: public ShapePx_Entity
	{

		/*Private Data*/

		std::vector<std::shared_ptr<ShapePx_TopoSection>> theSections_;

		std::vector<std::pair<Standard_Real, Standard_Integer>> theKnots_;
		Standard_Integer theRowDeg_;

		//- private functions and operators

		TNB_SERIALIZATION(TnbShapePx_EXPORT);

	public:

		//- default constructor

		ShapePx_TopoCtrlNet()
			: theRowDeg_(3)
		{}


		//- constructors

		ShapePx_TopoCtrlNet
		(
			const std::vector<std::shared_ptr<ShapePx_TopoSection>>& theSections
		)
			: theSections_(theSections)
			, theRowDeg_(3)
		{}

		ShapePx_TopoCtrlNet
		(
			const Standard_Integer theIndex,
			const word& theName, 
			const std::vector<std::shared_ptr<ShapePx_TopoSection>>& theSections
		)
			: ShapePx_Entity(theIndex, theName)
			, theSections_(theSections)
			, theRowDeg_(3)
		{}

		ShapePx_TopoCtrlNet
		(
			std::vector<std::shared_ptr<ShapePx_TopoSection>>&& theSections
		)
			: theSections_(std::move(theSections))
			, theRowDeg_(3)
		{}

		ShapePx_TopoCtrlNet
		(
			const Standard_Integer theIndex,
			const word& theName,
			std::vector<std::shared_ptr<ShapePx_TopoSection>>&& theSections
		)
			: ShapePx_Entity(theIndex, theName)
			, theSections_(std::move(theSections))
			, theRowDeg_(3)
		{}


		//- public functions and operators

		const auto& Sections() const
		{
			return theSections_;
		}

		auto& SectionsRef()
		{
			return theSections_;
		}

		auto RowDegree() const
		{
			return theRowDeg_;
		}

		const auto& Knots() const
		{
			return theKnots_;
		}

		auto& KnotsRef()
		{
			return theKnots_;
		}

		void SetSections
		(
			const std::vector<std::shared_ptr<ShapePx_TopoSection>>& theSections
		)
		{
			theSections_ = theSections;
		}

		void SetSections
		(
			std::vector<std::shared_ptr<ShapePx_TopoSection>>&& theSections
		)
		{
			theSections_ = std::move(theSections);
		}

		void SetRowDegree(const Standard_Integer theDeg)
		{
			theRowDeg_ = theDeg;
		}

		void SetKnots
		(
			const std::vector<std::pair<Standard_Real, Standard_Integer>>& theKnots
		)
		{
			theKnots_ = theKnots;
		}

		void SetKnots
		(
			std::vector<std::pair<Standard_Real, Standard_Integer>>&& theKnots
		)
		{
			theKnots_ = std::move(theKnots);
		}
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::ShapePx_TopoCtrlNet);

#endif // !_ShapePx_TopoCtrlNet_Header
