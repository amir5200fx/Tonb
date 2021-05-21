#pragma once
#ifndef _Mesh2d_SolutionData_Header
#define _Mesh2d_SolutionData_Header

#include <Global_Serialization.hxx>
#include <Mesh_Module.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations
	class Cad2d_Plane;
	class Mesh_ReferenceValues;

	namespace meshLib
	{

		class SolutionData
		{

			/*Private Data*/

			std::shared_ptr<Cad2d_Plane> thePlane_;
			std::shared_ptr<Mesh_ReferenceValues> theReferences_;


		};
	}
}

#endif // !_Mesh2d_SolutionData_Header
