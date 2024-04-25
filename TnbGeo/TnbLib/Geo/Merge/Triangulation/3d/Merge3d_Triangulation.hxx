#pragma once
#ifndef _Merge3d_Triangulation_Header
#define _Merge3d_Triangulation_Header

#include <Entity3d_TriangulationFwd.hxx>
#include <Global_Done.hxx>
#include <vector>
#include <memory>

namespace tnbLib
{
	
	class Merge3d_Triangulation
		: public Global_Done
	{
		/*Private Data*/
		std::vector<std::shared_ptr<Entity3d_Triangulation>> theTriangulations_;
	public:
		// default constructor
		Merge3d_Triangulation() = default;
		// constructors

		// Public functions and operators
		const auto& Triangulations() const { return theTriangulations_; }

		void Perform();
		void SetTriangulations(const std::vector<std::shared_ptr<Entity3d_Triangulation>>& theTris) { theTriangulations_ = theTris; }
		void SetTriangulations(std::vector<std::shared_ptr<Entity3d_Triangulation>>&& theTris) { theTriangulations_ = std::move(theTris); }
	};
}

#endif