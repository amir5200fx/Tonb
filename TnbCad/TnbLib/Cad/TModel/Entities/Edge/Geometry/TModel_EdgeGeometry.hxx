#pragma once
#ifndef _TModel_EdgeGeometry_Header
#define _TModel_EdgeGeometry_Header

#include <Standard_TypeDef.hxx>
#include <Global_AccessMethod.hxx>
#include <Global_Serialization.hxx>
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

		std::shared_ptr<TModel_Curve> theCurve_;
		std::shared_ptr<TModel_ParaCurve> theParaCurve_;

		mutable std::shared_ptr<Entity3d_Polygon> theMesh_;

		Standard_Boolean theSense_;


		//- private functions and operators

		auto& ChangeMesh() const
		{
			return theMesh_;
		}

		TNB_SERIALIZATION(TnbCad_EXPORT);

	protected:


		TModel_EdgeGeometry()
		{}

		TModel_EdgeGeometry
		(
			const std::shared_ptr<TModel_Curve>& theCurve, 
			const std::shared_ptr<TModel_ParaCurve>& thePara,
			const Standard_Boolean theSense = Standard_True
		)
			: theCurve_(theCurve)
			, theParaCurve_(thePara)
			, theSense_(theSense)
		{}


		void SetGeometry(std::shared_ptr<TModel_Curve>&& theCurve)
		{
			theCurve_ = std::move(theCurve);
		}

	public:

		auto Sense() const
		{
			return theSense_;
		}

		const auto& Curve() const
		{
			return theCurve_;
		}

		const auto& ParaCurve() const
		{
			return theParaCurve_;
		}

		const auto& Mesh() const
		{
			return theMesh_;
		}

		TnbCad_EXPORT void Discrete
		(
			const std::shared_ptr<Geo_ApprxCurve_Info>& theInfo
		) const;

		//- Macros
		
	};
}

#endif // !_TModel_EdgeGeometry_Header
