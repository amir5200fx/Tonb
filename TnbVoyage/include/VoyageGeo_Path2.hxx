#pragma once
#ifndef _VoyageGeo_Path2_Header
#define _VoyageGeo_Path2_Header

#include <Voyage_Entity.hxx>
#include <Entity2d_PolygonFwd.hxx>

#include <Standard_TypeDef.hxx>

#include <memory>
#include <vector>

namespace tnbLib
{

	//- Forward Declarations
	class VoyageGeo_Earth;
	class Pln_Edge;

	class VoyageGeo_Path2
		: public Voyage_Entity
	{

		/*Private Data*/

		std::vector<std::shared_ptr<Pln_Edge>> theCurves_;
		std::shared_ptr<VoyageGeo_Earth> theEarth_;

	public:

		//- default constructor

		VoyageGeo_Path2()
		{}

		//- constructors

		VoyageGeo_Path2
		(
			const std::vector<std::shared_ptr<Pln_Edge>>& theCurves,
			const std::shared_ptr<VoyageGeo_Earth>& theEarth
		)
			: theCurves_(theCurves)
			, theEarth_(theEarth)
		{}

		VoyageGeo_Path2
		(
			std::vector<std::shared_ptr<Pln_Edge>>&& theCurves,
			std::shared_ptr<VoyageGeo_Earth>&& theEarth
		)
			: theCurves_(std::move(theCurves))
			, theEarth_(std::move(theEarth))
		{}

		//- Public functions and operators

		auto NbCurves() const { return theCurves_.size(); }

		const auto& Curves() const { return theCurves_; }
		const auto& Earth() const { return theEarth_; }

		void SetCurves(const std::vector<std::shared_ptr<Pln_Edge>>& theCurves) { theCurves_ = theCurves; }
		void SetCurves(std::vector<std::shared_ptr<Pln_Edge>>&& theCurves) { theCurves_ = std::move(theCurves); }
		void SetEarth(const std::shared_ptr<VoyageGeo_Earth>& theEarth) { theEarth_ = theEarth; }
		void SetEarth(std::shared_ptr<VoyageGeo_Earth>&& theEarth) { theEarth_ = std::move(theEarth); }

	};
}

#endif // !_VoyageGeo_Path2_Header
