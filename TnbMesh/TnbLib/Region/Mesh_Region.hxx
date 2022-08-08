#pragma once
#ifndef _Mesh_Region_Header
#define _Mesh_Region_Header

#include <Mesh_RegionTraits.hxx>
#include <Global_Serialization.hxx>
#include <Global_Done.hxx>
#include <Mesh_Module.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations
	template<class BoxType>
	class Mesh_ReferenceValues;

	template<class GeomType> class Mesh_BoundarySizeMapControl;
	template<class GeomType> class Mesh_FeatureSizeMapControl;
	template<class GeomType> class Mesh_VolumetricSizeMapControl;

	template<class GeomType, class TopoMesh>
	class Mesh_RegionBase
	{

	public:

		typedef Mesh_BoundarySizeMapControl<GeomType> boundarySizeMapControl;
		typedef Mesh_FeatureSizeMapControl<GeomType> featureSizeMapControl;
		typedef Mesh_VolumetricSizeMapControl<GeomType> volumetricSizeMapControl;

		typedef TopoMesh topoMesh;

		typedef typename mesh_region_box_type<GeomType>::type boxType;
		typedef Mesh_ReferenceValues<boxType> refValues;

	protected:

		/*Private Data*/

		std::shared_ptr<refValues> theReferences_;
		std::shared_ptr<GeomType> theGeometry_;

		boundarySizeMapControl theBoundaries_;
		featureSizeMapControl theFeatures_;
		volumetricSizeMapControl theVolumetrics_;

		// results [7/18/2022 Amir]

		std::shared_ptr<topoMesh> theTopoMesh_;


		// default constructor [7/18/2022 Amir]

		Mesh_RegionBase()
		{}

		// constructors [7/18/2022 Amir]

		Mesh_RegionBase
		(
			const std::shared_ptr<refValues>& theRef, 
			const std::shared_ptr<GeomType>& theModel
		)
			: theReferences_(theRef)
			, theGeometry_(theModel)
		{}

	public:


		// public functions and operators [7/18/2022 Amir]

		const auto& References() const
		{
			return theReferences_;
		}

		const auto& Geoemtry() const
		{
			return theGeometry_;
		}

		const auto& Boundaries() const
		{
			return theBoundaries_;
		}

		auto& BoundariesRef()
		{
			return theBoundaries_;
		}

		const auto& Features() const
		{
			return theFeatures_;
		}

		auto& FeaturesRef()
		{
			return theFeatures_;
		}

		const auto& Volumetrics() const
		{
			return theVolumetrics_;
		}

		auto& VolumetricsRef()
		{
			return theVolumetrics_;
		}

		const auto& Mesh() const
		{
			return theTopoMesh_;
		}
	};

	template<class GeomType, class MetricPrcsr, class TopoMesh>
	class Mesh_Region
		: public Global_Done
	{

	public:

		typedef Mesh_BoundarySizeMapControl<GeomType> boundarySizeMapControl;
		typedef Mesh_FeatureSizeMapControl<GeomType> featureSizeMapControl;
		typedef Mesh_VolumetricSizeMapControl<GeomType> volumetricSizeMapControl;

		typedef MetricPrcsr metricPrcsr;
		typedef TopoMesh topoMesh;

	private:

		/*Private Data*/


	public:

		unsigned short verbose;


	};

	template<class GeomType, class TopoMesh>
	class Mesh_Region<GeomType, void, TopoMesh>
		: public Mesh_RegionBase<GeomType, TopoMesh>
	{

		/*Private Data*/


	public:

		typedef Mesh_RegionBase<GeomType, TopoMesh> base;

		using base::boxType;
		using base::boundarySizeMapControl;
		using base::featureSizeMapControl;
		using base::volumetricSizeMapControl;
		using base::refValues;

		// default constructor [7/18/2022 Amir]


		// constructors [7/18/2022 Amir]

		Mesh_Region
		(
			const std::shared_ptr<refValues>& theRef, 
			const std::shared_ptr<Cad_TModel>& theGeometry
		)
			: base(theRef, theGeometry)
		{}


		// public functions and operators [7/18/2022 Amir]

		void Perform();
	};
}

#endif // !_Mesh_Region_Header
