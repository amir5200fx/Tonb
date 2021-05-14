#pragma once
#ifndef _Mesh2d_SizeMapTool_Header
#define _Mesh2d_SizeMapTool_Header

#include <Mesh_SizeMapToolBase.hxx>
#include <GeoMesh2d_BackgroundFwd.hxx>

#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class Cad2d_Plane;

	class Mesh2d_SizeMapTool
		: public Mesh_SizeMapToolBase<GeoMesh2d_Background>
	{

		/*Private Data*/

		std::shared_ptr<Cad2d_Plane> thePlane_;


	protected:

		//- default constructor
		Mesh2d_SizeMapTool()
		{}


		//- constructor

		Mesh2d_SizeMapTool
		(
			const std::shared_ptr<Mesh_ReferenceValues>& theRef, 
			const std::shared_ptr<Cad2d_Plane>& thePlane
		)
			: Mesh_SizeMapToolBase<GeoMesh2d_Background>(theRef)
			, thePlane_(thePlane)
		{}


	public:


		const auto& Plane() const
		{
			return thePlane_;
		}
	};
}

#endif // !_Mesh2d_SizeMapTool_Header
