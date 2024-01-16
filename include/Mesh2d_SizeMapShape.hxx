#pragma once
#ifndef _Mesh2d_SizeMapShape_Header
#define _Mesh2d_SizeMapShape_Header

#include <Mesh2d_SizeMapVolume.hxx>

namespace tnbLib
{

	// Forward Declarations
	class Cad2d_Plane;
	class Discret_CurveInfo;

	class Mesh2d_SizeMapShape
		: public Mesh2d_SizeMapVolume
	{

		/*Private Data*/

		std::shared_ptr<Cad2d_Plane> theVolume_;
		std::shared_ptr<Discret_CurveInfo> theInfo_;
		Standard_Integer theNbSamples_;
		Standard_Real theSize_;

		// Private functions and operators

		TNB_SERIALIZATION(TnbMesh_EXPORT);

	public:

		static TnbMesh_EXPORT std::shared_ptr<Discret_CurveInfo> DEFAULT_INFO;
		static TnbMesh_EXPORT const Standard_Integer DEFAULT_NB_SAMPLES;

		// default constructors

		Mesh2d_SizeMapShape()
			: theInfo_(DEFAULT_INFO)
			, theNbSamples_(DEFAULT_NB_SAMPLES)
			, theSize_(0)
		{}


		// cosntructors
		
		Mesh2d_SizeMapShape(const std::shared_ptr<Cad2d_Plane>& theVolume)
			: theVolume_(theVolume)
			, theInfo_(DEFAULT_INFO)
			, theNbSamples_(DEFAULT_NB_SAMPLES)
			, theSize_(0)
		{}

		Mesh2d_SizeMapShape(std::shared_ptr<Cad2d_Plane>&& theVolume)
			: theVolume_(std::move(theVolume))
			, theInfo_(DEFAULT_INFO)
			, theNbSamples_(DEFAULT_NB_SAMPLES)
			, theSize_(0)
		{}
		
		// Public functions and operators

		TnbMesh_EXPORT Entity2d_Box CalcBoundingBox() const override;
		TnbMesh_EXPORT Standard_Boolean IsShape() const override;

		TnbMesh_EXPORT void Perform() override;

		const auto& Volume() const { return theVolume_; }
		const auto& DiscretInfo() const { return theInfo_; }
		auto NbSamples() const { return theNbSamples_; }
		auto Size() const { return theSize_; }

		void SetVolume(const std::shared_ptr<Cad2d_Plane>& theVolume) { theVolume_ = theVolume; }
		void SetVolume(std::shared_ptr<Cad2d_Plane>&& theVolume) { theVolume_ = std::move(theVolume); }
		void SetNbSamples(const Standard_Integer n) { theNbSamples_ = n; }
		void SetSize(const Standard_Real h) { theSize_ = h; }
		void SetInfo(const std::shared_ptr<Discret_CurveInfo>& theInfo) { theInfo_ = theInfo; }
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::Mesh2d_SizeMapShape);

#endif
