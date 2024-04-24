#pragma once
#ifndef _Entity3d_TriShell_Header
#define _Entity3d_TriShell_Header
#include <Entity3d_TriangulationFwd.hxx>
#include <Pnt3d.hxx>
#include <Entity_Connectivity.hxx>

#include <vector>
namespace tnbLib
{
	class Entity3d_TriShell
	{
		/*Private Data*/
		std::vector<Pnt3d> theCoords_;
		std::vector<connectivity::triple> theElements_;

		// Private functions and operators
		
	public:
		// default constructor
		Entity3d_TriShell() = default;

		// constructors
		Entity3d_TriShell(const Entity3d_Triangulation& theMesh);

		// Public functions and operators
		const auto& Coords() const { return theCoords_; }
		const auto& Elements() const { return theElements_; }
		auto& CoordsRef() { return theCoords_; }
		auto& ElementsRef() { return theElements_; }

		TnbGeo_EXPORT void Import(const Entity3d_Triangulation&);

		// io functions
		TnbGeo_EXPORT void ExportToPlt(OFstream&) const;
	};
}
#endif