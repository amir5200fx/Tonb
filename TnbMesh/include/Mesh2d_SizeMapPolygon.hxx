#pragma once
#ifndef _Mesh2d_SizeMapPolygon_Header
#define _Mesh2d_SizeMapPolygon_Header

#include <Mesh2d_SizeMapVolume.hxx>
#include <Entity2d_PolygonFwd.hxx>

namespace tnbLib
{

	// Forward Declaration
	
	class Mesh2d_SizeMapPolygon
		: public Mesh2d_SizeMapVolume
	{

		/*Private Data*/

		std::shared_ptr<Entity2d_Polygon> theVolume_;

		// Private functions and operators

		TNB_SERIALIZATION(TnbMesh_EXPORT);

	public:

		// default constructors

		Mesh2d_SizeMapPolygon() = default;


		// constructors
		
		Mesh2d_SizeMapPolygon(const std::shared_ptr<Entity2d_Polygon>& theVolume)
			: theVolume_(theVolume)
		{}

		Mesh2d_SizeMapPolygon(std::shared_ptr<Entity2d_Polygon>&& theVolume)
			: theVolume_(std::move(theVolume))
		{}
		
		// Public function and operators

		TnbMesh_EXPORT Entity2d_Box CalcBoundingBox() const override;
		TnbMesh_EXPORT Standard_Boolean IsPolygon() const override;

		TnbMesh_EXPORT void Perform() override;

		const auto& Volume() const { return theVolume_; }

		void SetVolume(const std::shared_ptr<Entity2d_Polygon>& theVolume) { theVolume_ = theVolume; }
		void SetVolume(std::shared_ptr<Entity2d_Polygon>&& theVolume) { theVolume_ = std::move(theVolume); }
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::Mesh2d_SizeMapPolygon)

#endif