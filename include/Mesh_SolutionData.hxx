#pragma once
#ifndef _Mesh_SolutionData_Header
#define _Mesh_SolutionData_Header

#include <Global_Serialization.hxx>
#include <Mesh_Module.hxx>
#include <Mesh_BoundarySizeMapControl.hxx>
#include <Mesh_FeatureSizeMapControl.hxx>
#include <Mesh_VolumetricSizeMapControl.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations
	class Mesh_ReferenceValues;

	template<class GeomType> class Mesh_BoundarySizeMapControl;
	template<class GeomType> class Mesh_FeatureSizeMapControl;
	template<class GeomType> class Mesh_VolumetricSizeMapControl;

	template<class GeomType>
	class Mesh_SolutionData
	{

		/*Private Data*/

		std::shared_ptr<GeomType> theGeometry_;
		std::shared_ptr<Mesh_ReferenceValues> theReferences_;


		Mesh_BoundarySizeMapControl<GeomType> theBoundaries_;
		Mesh_FeatureSizeMapControl<GeomType> theFeatures_;
		Mesh_VolumetricSizeMapControl<GeomType> theVolumetrics_;

		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			//- not supposed to be called!
			NotImplemented;
		}

		//void CreateSizeMap();

		//- default constructor

		Mesh_SolutionData()
		{}

	public:

		
		//static unsigned short verbose;

		//- constructors

		Mesh_SolutionData
		(
			const std::shared_ptr<GeomType>& theGeometry,
			const std::shared_ptr<Mesh_ReferenceValues>& theReferences
		);


		//- public functions and operators


		const auto& Geometry() const
		{
			return theGeometry_;
		}

		const auto& References() const
		{
			return theReferences_;
		}

		//- mesh controllers

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



		/*void LoadGeometry(const std::shared_ptr<GeomType>& theGeom)
		{
			theGeometry_ = theGeom;
		}

		void LoadReferences(const std::shared_ptr<Mesh_ReferenceValues>& theRef)
		{
			theReferences_ = theRef;
		}*/
	};
}

#include <Mesh_SolutionDataI.hxx>

#endif // !_Mesh_SolutionData_Header
