#pragma once
#ifndef _VoyageGeo_Path2_Header
#define _VoyageGeo_Path2_Header

#include <Voyage_Entity.hxx>

#include <Standard_TypeDef.hxx>

#include <memory>
#include <vector>

namespace tnbLib
{

	//- Forward Declarations
	class Pln_Edge;

	class VoyageGeo_Path2
		: public Voyage_Entity
	{

		/*Private Data*/

		std::vector<std::shared_ptr<Pln_Edge>> theCurves_;

	public:

		//- default constructor

		VoyageGeo_Path2()
		{}

		//- constructors

		VoyageGeo_Path2(const std::vector<std::shared_ptr<Pln_Edge>>& theCurves)
			: theCurves_(theCurves)
		{}

		VoyageGeo_Path2(std::vector<std::shared_ptr<Pln_Edge>>&& theCurves)
			: theCurves_(std::move(theCurves))
		{}

		//- Public functions and operators

		Standard_Integer NbCurves() const { return theCurves_.size(); }

		const auto& Curves() const { return theCurves_; }

		void SetCurves(const std::vector<std::shared_ptr<Pln_Edge>>& theCurves) { theCurves_ = theCurves; }
		void SetCurves(std::vector<std::shared_ptr<Pln_Edge>>&& theCurves) { theCurves_ = std::move(theCurves); }

	};
}

#endif // !_VoyageGeo_Path2_Header
