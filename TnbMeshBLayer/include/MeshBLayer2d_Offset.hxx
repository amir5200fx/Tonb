#pragma once
#ifndef _MeshBLayer2d_Offset_Header
#define _MeshBLayer2d_Offset_Header

#include <MeshBLayer_Module.hxx>
#include <Entity2d_QuadMeshFwd.hxx>
#include <Entity2d_PolygonFwd.hxx>
#include <Global_Done.hxx>
#include <Global_TypeDef.hxx>

#include <memory>

namespace tnbLib
{

	class MeshBLayer2d_Offset
		: public Global_Done
	{

		/*Private Data*/

		std::shared_ptr<Entity2d_Polygon> thePolygon_;
		std::shared_ptr<Entity2d_Polygon> theOffset_;

		Standard_Integer theClusterSize_;
		Standard_Real theRate_;

		// The result
		std::shared_ptr<Entity2d_QuadMesh> theMesh_;

	public:

		// Default constructor [9/9/2023 Payvand]

		MeshBLayer2d_Offset()
		= default;

		// constructors [9/9/2023 Payvand]

		// Public functions and operators [9/9/2023 Payvand]

		[[nodiscard]] const auto& Polygon() const { return thePolygon_; }
		[[nodiscard]] const auto& Offset() const { return theOffset_; }

		[[nodiscard]] const auto& Mesh() const { return theMesh_; }

		auto ClusterSize() const { return theClusterSize_; }
		auto Rate() const { return theRate_; }

		TnbMeshBLayer_EXPORT void Perform();

		void SetPolygon(const std::shared_ptr<Entity2d_Polygon>& thePolygon)
		{ thePolygon_ = thePolygon; }
		void SetOffset(const std::shared_ptr<Entity2d_Polygon>& thePolygon)
		{ theOffset_ = thePolygon; }

		void SetClusterSize(const Standard_Integer theSize) { theClusterSize_ = theSize; }
		void SetRate(const Standard_Real theRate) { theRate_ = theRate; }

		// Refer to the computational fluid dynamics by hoffmann vol.1 (p. 378, Eq. 9-57) [9/9/2023 Payvand]
		static TnbMeshBLayer_EXPORT Standard_Real
		CalcRate(const Standard_Real theBeta, const Standard_Real theEta);
	};

}

#endif // !_MeshBLayer2d_Offset_Header
