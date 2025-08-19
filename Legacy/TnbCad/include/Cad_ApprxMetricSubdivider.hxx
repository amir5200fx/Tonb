#pragma once
#ifndef _Cad_ApprxMetricSubdivider_Header
#define _Cad_ApprxMetricSubdivider_Header

#include <Cad_Module.hxx>
#include <Entity2d_BoxFwd.hxx>
#include <Global_Handle.hxx>

#include <memory>

// Forward Declarations [12/25/2021 Amir]
class Geom_Surface;

namespace tnbLib
{

	// Forward Declarations [12/27/2021 Amir]
	class Cad_ApprxMetricCriterion;
	class Geo2d_SamplePoints;

	class Cad_ApprxMetricSubdivider
	{

		/*Private Data*/

		Handle(Geom_Surface) theGeometry_;

		std::shared_ptr<Cad_ApprxMetricCriterion> theCriterion_;
		std::shared_ptr<Geo2d_SamplePoints> theSamples_;

	public:

		static TnbCad_EXPORT const std::shared_ptr<Cad_ApprxMetricCriterion> DEFAULT_CRITERION;
		static TnbCad_EXPORT const std::shared_ptr<Geo2d_SamplePoints> DEFAULT_SAMPLES;

		// default constructor [12/25/2021 Amir]


		// constructors [12/27/2021 Amir]

		Cad_ApprxMetricSubdivider
		(
			const Handle(Geom_Surface)& theGeometry
		)
			: theGeometry_(theGeometry)
			, theCriterion_(DEFAULT_CRITERION)
			, theSamples_(DEFAULT_SAMPLES)
		{}

		Cad_ApprxMetricSubdivider
		(
			const Handle(Geom_Surface)& theGeometry,
			const std::shared_ptr<Cad_ApprxMetricCriterion>& theCriterion,
			const std::shared_ptr<Geo2d_SamplePoints>& theSamples
		)
			: theGeometry_(theGeometry)
			, theCriterion_(theCriterion)
			, theSamples_(theSamples)
		{}


		// public functions and operators [12/25/2021 Amir]

		const auto& Geometry() const
		{
			return theGeometry_;
		}

		const auto& Criterion() const
		{
			return theCriterion_;
		}

		const auto& Samples() const
		{
			return theSamples_;
		}

		void SetSamples(const std::shared_ptr<Geo2d_SamplePoints>& theSamples)
		{
			theSamples_ = theSamples;
		}

		void SetCriterion(const std::shared_ptr<Cad_ApprxMetricCriterion>& theCriterion)
		{
			theCriterion_ = theCriterion;
		}

		static TnbCad_EXPORT Standard_Boolean 
			Subdivide
			(
				const Entity2d_Box& theDomain,
				const Cad_ApprxMetricSubdivider*
			);
	};
}

#endif // !_Cad_ApprxMetricSubdivider_Header
