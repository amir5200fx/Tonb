#pragma once
#ifndef _NModel_EdgeGeometry_Header
#define _NModel_EdgeGeometry_Header

#include <Global_AccessMethod.hxx>
#include <Entity3d_ChainFwd.hxx>
#include <Cad_Module.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations
	class NModel_ParaCurve;
	class NModel_Curve;
	class Geo_ApprxCurve_Info;

	class NModel_EdgeGeometry
	{

		/*Private Data*/

		std::shared_ptr<NModel_Curve> theCurve_;
		std::shared_ptr<NModel_ParaCurve> theParaCurve_;

		mutable std::shared_ptr<Entity3d_Chain> theMesh_;

		Standard_Boolean theSense_;

		auto& ChangeMesh() const
		{
			return theMesh_;
		}

	protected:

		NModel_EdgeGeometry
		(
			const std::shared_ptr<NModel_Curve>& theCurve,
			const std::shared_ptr<NModel_ParaCurve>& thePara,
			const Standard_Boolean theSense = Standard_True
		)
			: theCurve_(theCurve)
			, theParaCurve_(thePara)
			, theSense_(theSense)
		{}

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

#endif // !_NModel_EdgeGeometry_Header