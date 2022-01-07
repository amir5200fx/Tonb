#pragma once
#ifndef _TModel_GeneratedEdgeGeometry_Header
#define _TModel_GeneratedEdgeGeometry_Header

#include <Cad_Module.hxx>
#include <Standard_TypeDef.hxx>
#include <Entity3d_PolygonFwd.hxx>
#include <Global_Serialization.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations [1/6/2022 Amir]
	class TModel_Curve;

	class TModel_GeneratedEdgeGeometry
	{

		/*Private Data*/

		std::shared_ptr<TModel_Curve> theCurve_;
		std::shared_ptr<Entity3d_Polygon> theMesh_;

		Standard_Boolean theSense_;


		// private functions and operators [1/6/2022 Amir]

		TNB_SERIALIZATION(TnbCad_EXPORT);

	protected:

		// default constructor [1/6/2022 Amir]

		TModel_GeneratedEdgeGeometry()
			: theSense_(Standard_True)
		{}

		// constructors [1/6/2022 Amir]
		
		TModel_GeneratedEdgeGeometry
		(
			const std::shared_ptr<TModel_Curve>& theCurve,
			const Standard_Boolean theSense
		)
			: theCurve_(theCurve)
			, theSense_(theSense)
		{}

		// protected functions and operators [1/6/2022 Amir]

		void SetGeometry(std::shared_ptr<TModel_Curve>&& theCurve)
		{
			theCurve_ = std::move(theCurve);
		}

	public:


		// public functions and operators [1/6/2022 Amir]

		auto Sense() const
		{
			return theSense_;
		}

		const auto& Curve() const
		{
			return theCurve_;
		}

		const auto& Mesh() const
		{
			return theMesh_;
		}
	};
}

#endif // !_TModel_GeneratedEdgeGeometry_Header
