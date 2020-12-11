#pragma once
#ifndef _Marine_Wave_Header
#define _Marine_Wave_Header

#include <Global_Done.hxx>
#include <Global_Indexed.hxx>
#include <Global_Named.hxx>
#include <Global_AccessMethod.hxx>
#include <Pnt2d.hxx>
#include <Pnt3d.hxx>
#include <Dir3d.hxx>
#include <Vec3d.hxx>
#include <EnvtPropt_Density.hxx>
#include <Entity3d_Box.hxx>
#include <Marine_Module.hxx>
#include <Geo_Serialization.hxx>
#include <OpenCascade_Serialization.hxx>

#include <Standard_Handle.hxx>
#include <gp_Ax2.hxx>

class Geom_Surface;
class Geom2d_Curve;

#include <memory>

namespace tnbLib
{

	// Forward Declarations
	namespace marineLib
	{
		class Density;
	}

	class Marine_WaveGeometry
	{

		/*Private Data*/

		Handle(Geom_Surface) theSurfaceGeometry_;
		Handle(Geom2d_Curve) theCurveGeometry_;


		//- private functions and operators

		TNB_SERIALIZATION(TnbMarine_EXPORT);

	protected:

		Marine_WaveGeometry()
		{}

		auto& ChangeSurfaceGeometry()
		{
			return theSurfaceGeometry_;
		}

		auto& ChangeCurveGeometry()
		{
			return theCurveGeometry_;
		}

	public:

		Standard_Boolean HasSurfaceGeometry() const
		{
			return (Standard_Boolean)theSurfaceGeometry_;
		}

		Standard_Boolean HasCurveGeometry() const
		{
			return (Standard_Boolean)theCurveGeometry_;
		}

		const auto& SurfaceGeometry() const
		{
			return theSurfaceGeometry_;
		}

		const auto& CurveGeometry() const
		{
			return theCurveGeometry_;
		}

	};

	class Marine_WaveDensity
	{

		/*Private Data*/

		marineLib::Density theLightFluidDensity_;
		marineLib::Density theHeavyFluidDensity_;


		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & theLightFluidDensity_;
			ar & theHeavyFluidDensity_;
		}

	protected:

		TnbMarine_EXPORT Marine_WaveDensity();

	public:

		//- Macros

		GLOBAL_ACCESS_SINGLE(marineLib::Density, LightFluidDensity)
			GLOBAL_ACCESS_SINGLE(marineLib::Density, HeavyFluidDensity)
	};

	struct Marine_WaveCache
	{
		mutable gp_Trsf originToCurrentTransform;
	};

	class Marine_Wave
		: public Global_Indexed
		, public Global_Named
		, public Global_Done
		, public Marine_WaveDensity
		, public Marine_WaveGeometry
		, public Marine_WaveCache
		, public std::enable_shared_from_this<Marine_Wave>
	{

		/*Private Data*/

		Pnt3d thePointOnWater_;

		Dir3d theVerticalDirection_;
		
		Vec3d theCurrent_;
		Vec3d theWind_;

		std::shared_ptr<Entity3d_Box> theDomain_;
		gp_Ax2 theOrigin_;


		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & boost::serialization::base_object<Global_Indexed>(*this);
			ar & boost::serialization::base_object<Global_Named>(*this);
			ar & boost::serialization::base_object<Global_Done>(*this);
			ar & boost::serialization::base_object<Marine_WaveDensity>(*this);
			ar & boost::serialization::base_object<Marine_WaveGeometry>(*this);
			
			ar & thePointOnWater_;
			ar & theVerticalDirection_;
			ar & theCurrent_;
			ar & theWind_;
			ar & theDomain_;
			ar & theOrigin_;
		}

		TnbMarine_EXPORT Pnt3d ProjectedCoordOnSurface() const;

		TnbMarine_EXPORT Entity3d_Box BoundingBoxOfRotatedDomain(const Entity3d_Box& theDomain) const;

		TnbMarine_EXPORT void TransformOriginToCurrent() const;

	protected:

		//- default constructor

		Marine_Wave()
		{}


		//- constructor

		Marine_Wave(const std::shared_ptr<Entity3d_Box>& theDomain)
			: theDomain_(theDomain)
		{}

		virtual Dir3d SurfaceDirection() const = 0;

		virtual void MakeProfileCurve(const Pnt2d& x0, const Pnt2d& x1) = 0;

		TnbMarine_EXPORT void MakeGeometrySurface(const Standard_Real y0, const Standard_Real y1);

		TnbMarine_EXPORT void TransportGeometrySurface();

		TnbMarine_EXPORT void TranslateSurfaceToPointOnWater(const Pnt3d& theProj);

	public:


		//- public functions and operators

		const auto& Origin() const
		{
			return theOrigin_;
		}

		const auto& Domain() const
		{
			return theDomain_;
		}

		TnbMarine_EXPORT gp_Ax2 SurfaceCoordinateSystem() const;

		TnbMarine_EXPORT void Perform();


		static TnbMarine_EXPORT void Save(TNB_oARCH_TYPE& ar, const std::shared_ptr<Marine_Wave>& wave);
		static TnbMarine_EXPORT void Load(TNB_iARCH_TYPE& ar, std::shared_ptr<Marine_Wave>& wave);

		//- Macros
		GLOBAL_ACCESS_SINGLE(Pnt3d, PointOnWater)

			GLOBAL_ACCESS_SINGLE(Dir3d, VerticalDirection)
			GLOBAL_ACCESS_SINGLE(Vec3d, Current)
			GLOBAL_ACCESS_SINGLE(Vec3d, Wind)

			
	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::Marine_Wave);

#endif // !_Marine_Wave_Header
