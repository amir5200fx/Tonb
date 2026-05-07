#pragma once
#ifndef _TModel_CmpParaCurve_Header
#define _TModel_CmpParaCurve_Header

#include <TModel_Entity.hxx>
#include <Entity2d_BoxFwd.hxx>

#include <memory>
#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class TModel_ParaCurve;
	class TModel_ParaWire;
	class Cad_Tools;

	class TModel_CmpParaCurve
		: public TModel_Entity
	{

		friend TModel_ParaWire;
		friend Cad_Tools;

		/*Private Data*/

		std::vector<std::shared_ptr<TModel_ParaCurve>> theCurves_;


		//- private functions and operators

		TNB_SERIALIZATION(TnbCad_EXPORT);

	protected:

		void Insert(const std::shared_ptr<TModel_ParaCurve>& theCurve)
		{
			theCurves_.push_back(theCurve);
		}

	public:

		// default constructor [1/5/2022 Amir]

		TModel_CmpParaCurve()
		{}


		// constructors [1/5/2022 Amir]

		explicit TModel_CmpParaCurve
		(
			const Standard_Integer theIndex
		)
			: TModel_Entity(theIndex)
		{}

		TModel_CmpParaCurve
		(
			const Standard_Integer theIndex, 
			const word& theName
		)
			: TModel_Entity(theIndex, theName)
		{}


		//- public functions and operators

		auto NbCurves() const
		{
			return (Standard_Integer)theCurves_.size();
		}

		const auto& Curves() const
		{
			return theCurves_;
		}

		TnbCad_EXPORT Entity2d_Box CalcBoundingBox() const;
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::TModel_CmpParaCurve);

#endif // !_TModel_CmpParaCurve_Header
