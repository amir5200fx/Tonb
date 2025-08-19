#pragma once
#ifndef _TModel_EdgeGeometry_Header
#define _TModel_EdgeGeometry_Header

#include <Global_AccessMethod.hxx>
#include <Global_Serialization.hxx>
#include <Global_Handle.hxx>
#include <Entity3d_PolygonFwd.hxx>
#include <Cad_Module.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations
	class TModel_ParaCurve;
	class TModel_Curve;
	class Geo_ApprxCurve_Info;

	class TModel_EdgeGeometry
	{

		/*Private Data*/

		std::shared_ptr<TModel_ParaCurve> theParaCurve_;
		//std::shared_ptr<Entity3d_Polygon> theMesh_;


		//- private functions and operators

		TNB_SERIALIZATION(TnbCad_EXPORT);

	protected:


		// default constructor [1/6/2022 Amir]

		TModel_EdgeGeometry()
		{}

		// constructors [1/6/2022 Amir]

		explicit TModel_EdgeGeometry
		(
			const std::shared_ptr<TModel_ParaCurve>& thePara
		)
			: theParaCurve_(thePara)
		{}


	public:


		// public functions and operators [1/6/2022 Amir]

		const auto& ParaCurve() const
		{
			return theParaCurve_;
		}

		/*const auto& Triangulation() const
		{
			return theMesh_;
		}

		void SetTriangulation(const std::shared_ptr<Entity3d_Polygon>& theMesh)
		{
			theMesh_ = theMesh;
		}

		void SetTriangulation(std::shared_ptr<Entity3d_Polygon>&& theMesh)
		{
			theMesh_ = std::move(theMesh);
		}*/

		/*TnbCad_EXPORT void Discrete
		(
			const std::shared_ptr<Geo_ApprxCurve_Info>& theInfo
		) const;*/

		//- Macros
		
	};
}

#endif // !_TModel_EdgeGeometry_Header
