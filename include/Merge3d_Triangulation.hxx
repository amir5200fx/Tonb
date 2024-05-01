#pragma once
#ifndef _Merge3d_Triangulation_Header
#define _Merge3d_Triangulation_Header

#include <Entity3d_TriangulationFwd.hxx>
#include <Geo_Module.hxx>
#include <Global_Done.hxx>
#include <vector>
#include <memory>

namespace tnbLib
{
	
	class Merge3d_Triangulation
		: public Global_Done
	{
		/*Private Data*/
		std::shared_ptr<Entity3d_Triangulation> theTriangulation_;

		Standard_Integer theRadius_ = 1.0e-4;
		// results
		std::shared_ptr<Entity3d_Triangulation> theMerged_;
	public:
		// default constructor
		Merge3d_Triangulation() = default;
		// constructors

		// Public functions and operators
		const auto& Triangulation() const { return theTriangulation_; }
		auto Radius() const { return theRadius_; }

		const auto& Merged() const { return theMerged_; }

		TnbGeo_EXPORT void Perform();
		void SetRadius(const Standard_Real theRadius) { theRadius_ = theRadius; }
		void SetTriangulation(const std::shared_ptr<Entity3d_Triangulation>& theTris) { theTriangulation_ = theTris; }
		void SetTriangulation(std::shared_ptr<Entity3d_Triangulation>&& theTris) { theTriangulation_ = std::move(theTris); }
	};
}

#endif