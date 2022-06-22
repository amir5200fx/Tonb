#pragma once
#ifndef _TModel_ParaWire_Header
#define _TModel_ParaWire_Header

#include <Global_Indexed.hxx>
#include <Global_Named.hxx>
#include <Cad_Module.hxx>
#include <Entity2d_BoxFwd.hxx>
#include <OFstream.hxx>

#include <vector>

class gp_Trsf2d;

namespace tnbLib
{

	// Forward Declarations
	class TModel_ParaCurve;

	class TModel_ParaWire
		: public Global_Indexed
		, public Global_Named
	{

		typedef std::vector<std::shared_ptr<TModel_ParaCurve>> curveList;

		/*Private Data*/

		std::shared_ptr<curveList> theCurves_;


		//- public functions and operators

		TNB_SERIALIZATION(TnbCad_EXPORT);


	protected:


		//- default constructor

		TModel_ParaWire()
		{}


	public:

		typedef TModel_ParaCurve paraCurveType;


		//- constructors

		TnbCad_EXPORT explicit TModel_ParaWire
		(
			const std::shared_ptr<curveList>& theCurves
		);

		TnbCad_EXPORT TModel_ParaWire
		(
			std::shared_ptr<curveList>&& theCurves
		);

		TnbCad_EXPORT TModel_ParaWire
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<curveList>& theCurves
		);

		TnbCad_EXPORT TModel_ParaWire
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::shared_ptr<curveList>& theCurves
		);

		TnbCad_EXPORT TModel_ParaWire
		(
			const Standard_Integer theIndex,
			const word& theName,
			std::shared_ptr<curveList>&& theCurves
		);


		// public functions and operators [1/5/2022 Amir]

		TnbCad_EXPORT Standard_Integer NbCurves() const;
		TnbCad_EXPORT Standard_Integer NbEdges() const;

		TnbCad_EXPORT Entity2d_Box CalcBoundingBox() const;

		TnbCad_EXPORT std::shared_ptr<TModel_ParaWire> Copy() const;
		TnbCad_EXPORT std::shared_ptr<TModel_ParaWire> Copy(const gp_Trsf2d&) const;

		const auto& Curves() const
		{
			return *theCurves_;
		}

		const auto& Edges() const
		{
			return *theCurves_;
		}

	};
}

#endif // !_TModel_ParaWire_Header
