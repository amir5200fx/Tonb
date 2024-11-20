#pragma once
#ifndef _MeshPost3d_StellarOpt_Header
#define _MeshPost3d_StellarOpt_Header
#include <Entity3d_TetrahedralizationFwd.hxx>
#include <Global_Done.hxx>

#include <memory>

// Forward Declarations
struct behavior;

namespace tnbLib
{
	class MeshPost3d_StellarOpt
		: public Global_Done
	{
		/*Private Data*/
		std::shared_ptr<Entity3d_Tetrahedralization> theMesh_;

		std::shared_ptr<Entity3d_Tetrahedralization> theModified_;

		void Init(behavior*);

	public:
		static unsigned short verbose;
		// default constructor
		MeshPost3d_StellarOpt() = default;

		// constructors

		// Public functions and operators
		const auto& Mesh() const { return theMesh_; }
		const auto& Modified() const { return theModified_; }

		void Perform();
	};
}

#endif