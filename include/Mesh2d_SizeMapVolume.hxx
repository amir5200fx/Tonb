#pragma once
#ifndef _Mesh2d_SizeMapVolume_Header
#define _Mesh2d_SizeMapVolume_Header

#include <Mesh_Module.hxx>
#include <Entity2d_BoxFwd.hxx>
#include <Entity2d_PolygonFwd.hxx>
#include <Global_Serialization.hxx>
#include <Global_Done.hxx>
#include <Global_Indexed.hxx>
#include <Global_TypeDef.hxx>

#include <memory>

namespace tnbLib
{

	class Mesh2d_SizeMapVolume
		: public Global_Indexed
		, public Global_Done
	{

		/*Private Data*/

		std::shared_ptr<Entity2d_Polygon> theBoundary_;

		// Private function and operators

		TNB_SERIALIZATION(TnbMesh_EXPORT);
		
	protected:

		// default constructor

		Mesh2d_SizeMapVolume() = default;

		auto& BoundaryRef() { return theBoundary_; }
		
	public:
		virtual ~Mesh2d_SizeMapVolume() = default;

		// Public functions and operators

		const auto& Boundary() const { return theBoundary_; }

		virtual Entity2d_Box CalcBoundingBox() const = 0;
		TnbMesh_EXPORT virtual void Perform();

		TnbMesh_EXPORT virtual Standard_Boolean IsShape() const;
		TnbMesh_EXPORT virtual Standard_Boolean IsPolygon() const;
	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::Mesh2d_SizeMapVolume);

#endif
