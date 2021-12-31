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
	class Cad_ApprxMetricInfo;

	class Cad_ApprxMetric
		: public Global_Done
	{

		/*Private Data*/

		Handle(Geom_Surface) theGeometry_;

		std::shared_ptr<Entity2d_Box> theDomain_;
		std::shared_ptr<Cad_ApprxMetricInfo> theInfo_;


		std::shared_ptr<Entity2d_Triangulation> theTriangulation_;

	public:

		static TnbCad_EXPORT const std::shared_ptr<Cad_ApprxMetricInfo> DEFAULT_INFO;
		static TnbCad_EXPORT unsigned short verbose;

		// default constructor [12/25/2021 Amir]

		Cad_ApprxMetric()
			: theInfo_(DEFAULT_INFO)
		{}


		// constructors [12/27/2021 Amir]

		Cad_ApprxMetric
		(
			const Handle(Geom_Surface)& theGeometry,
			const std::shared_ptr<Entity2d_Box>& theDomain
		)
			: theGeometry_(theGeometry)
			, theDomain_(theDomain)
			, theInfo_(DEFAULT_INFO)
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

		const auto& Info() const
		{
			return theInfo_;
		}

		const auto& Triangulation() const
		{
			return theTriangulation_;
		}

		auto& TriangulationRef()
		{
			return theTriangulation_;
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

		void LoadDomain(std::shared_ptr<Entity2d_Box>&& theDomain)
		{
			theDomain_ = std::move(theDomain);
		}

		void OverrideInfo(const std::shared_ptr<Cad_ApprxMetricInfo>& theInfo)
		{
			theInfo_ = theInfo;
		}

		void OverrideInfo(std::shared_ptr<Cad_ApprxMetricInfo>&& theInfo)
		{
			theInfo_ = std::move(theInfo);
		}
	};
}

#endif // !_Cad_ApprxMetric_Header
