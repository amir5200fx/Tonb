#pragma once
#ifndef _Mesh_Region_Header
#define _Mesh_Region_Header

#include <Global_Serialization.hxx>
#include <Global_Done.hxx>
#include <Mesh_Module.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations
	class Mesh_ReferenceValues;

	template<class GeomType> class Mesh_BoundarySizeMapControl;
	template<class GeomType> class Mesh_FeatureSizeMapControl;
	template<class GeomType> class Mesh_VolumetricSizeMapControl;


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

		std::shared_ptr<Mesh_ReferenceValues> theReferences_;
		std::shared_ptr<GeomType> theGeometry_;

		boundarySizeMapControl theBoundaries_;
		featureSizeMapControl theFeatures_;
		volumetricSizeMapControl theVolumetrics_;

		std::shared_ptr<metricPrcsr> theMetricPrcsr_;
		std::shared_ptr<topoMesh> theTopoMesh_;

	public:

		unsigned short verbose;


	};
}

#endif // !_Mesh_Region_Header
