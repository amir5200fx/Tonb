#pragma once
#ifndef _Cad_ApprxMetric_Header
#define _Cad_ApprxMetric_Header

#include <Cad_Module.hxx>
#include <Global_Done.hxx>
#include <Standard_Handle.hxx>
#include <Entity2d_BoxFwd.hxx>
#include <Entity2d_TriangulationFwd.hxx>
#include <Entity2d_Metric1.hxx>

#include <memory>
#include <vector>

// Forward Declarations [12/25/2021 Amir]
class Geom_Surface;

namespace tnbLib
{

	// Forward Declarations [12/27/2021 Amir]
	class Geo2d_SamplePoints;
	class Cad_ApprxMetricCriterion;

	class Cad_ApprxMetric
		: public Global_Done
	{

		/*Private Data*/

		Handle(Geom_Surface) theGeometry_;

		std::shared_ptr<Entity2d_Box> theDomain_;

		Standard_Integer theMinLevel_;
		Standard_Integer theMaxLevel_;
		Standard_Integer theUnbalancing_;

		Standard_Real theResolution_;
		Standard_Real theTolerance_;

		std::shared_ptr<Geo2d_SamplePoints> theSamples_;
		std::shared_ptr<Cad_ApprxMetricCriterion> theCriterion_;


		std::shared_ptr<Entity2d_Triangulation> theTriangulation_;
		std::vector<Entity2d_Metric1> theValues_;

	public:

		static TnbCad_EXPORT const Standard_Integer DEFAULT_MIN_LEVEL;
		static TnbCad_EXPORT const Standard_Integer DEFAULT_MAX_LEVEL;
		static TnbCad_EXPORT const Standard_Integer DEFAULT_UNBALANCING;

		static TnbCad_EXPORT const Standard_Real DEFAULT_RESOLUTION;
		static TnbCad_EXPORT const Standard_Real DEFAULT_TOLERANCE;

		static TnbCad_EXPORT unsigned short verbose;

		// default constructor [12/25/2021 Amir]

		Cad_ApprxMetric()
			: theMinLevel_(DEFAULT_MIN_LEVEL)
			, theMaxLevel_(DEFAULT_MAX_LEVEL)
			, theUnbalancing_(DEFAULT_UNBALANCING)
		{}


		// constructors [12/27/2021 Amir]

		Cad_ApprxMetric
		(
			const Handle(Geom_Surface)& theGeometry,
			const std::shared_ptr<Entity2d_Box>& theDomain
		)
			: theGeometry_(theGeometry)
			, theDomain_(theDomain)
		{}

		// public functions and operators [12/27/2021 Amir]

		const auto& Geometry() const
		{
			return theGeometry_;
		}

		const auto& Domain() const
		{
			return theDomain_;
		}

		auto MinLevel() const
		{
			return theMinLevel_;
		}

		auto MaxLevel() const
		{
			return theMaxLevel_;
		}

		auto Unbalancing() const
		{
			return theUnbalancing_;
		}

		auto Resolution() const
		{
			return theResolution_;
		}

		auto Tolerance() const
		{
			return theTolerance_;
		}

		const auto& Triangulation() const
		{
			return theTriangulation_;
		}

		auto& TriangulationRef()
		{
			return theTriangulation_;
		}

		const auto& Values() const
		{
			return theValues_;
		}

		auto& ValuesRef()
		{
			return theValues_;
		}

		const auto& Samples() const
		{
			return theSamples_;
		}

		const auto& Criterion() const
		{
			return theCriterion_;
		}

		TnbCad_EXPORT void Perform();

		void LoadGeoemtry(const Handle(Geom_Surface)& theGeometry)
		{
			theGeometry_ = theGeometry;
		}

		void LoadDomain(const std::shared_ptr<Entity2d_Box>& theDomain)
		{
			theDomain_ = theDomain;
		}

		void OverrideSamples(const std::shared_ptr<Geo2d_SamplePoints>& theSamples)
		{
			theSamples_ = theSamples;
		}

		void OverrideCriterion(const std::shared_ptr<Cad_ApprxMetricCriterion>& theCriterion)
		{
			theCriterion_ = theCriterion;
		}
		
		void SetMinLevel(const Standard_Integer lev)
		{
			theMinLevel_ = lev;
		}

		void SetMaxLevel(const Standard_Integer lev)
		{
			theMaxLevel_ = lev;
		}

		void SetUnbalancing(const Standard_Integer lev)
		{
			theUnbalancing_ = lev;
		}

		void SetResolution(const Standard_Real theRes)
		{
			theResolution_ = theRes;
		}

		void SetTolerance(const Standard_Real theTol)
		{
			theTolerance_ = theTol;
		}
	};
}

#endif // !_Cad_ApprxMetric_Header
