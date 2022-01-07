#pragma once
#ifndef _TModel_ParaWire_Header
#define _TModel_ParaWire_Header

#include <TModel_Entity.hxx>
#include <Entity2d_BoxFwd.hxx>

namespace tnbLib
{

	// Forward Declarations
	class TModel_CmpParaCurve;

	class TModel_ParaWire
		: public TModel_Entity
	{

		/*Private Data*/

		std::shared_ptr<TModel_CmpParaCurve> theCurve_;


		//- public functions and operators

		TNB_SERIALIZATION(TnbCad_EXPORT);


	protected:


		//- default constructor

		TModel_ParaWire()
		{}


	public:


		//- constructors

		TnbCad_EXPORT explicit TModel_ParaWire
		(
			const std::shared_ptr<TModel_CmpParaCurve>& theCurve
		);

		TnbCad_EXPORT TModel_ParaWire
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<TModel_CmpParaCurve>& theCurve
		);

		TnbCad_EXPORT TModel_ParaWire
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::shared_ptr<TModel_CmpParaCurve>& theCurve
		);


		// public functions and operators [1/5/2022 Amir]


	};
}


BOOST_CLASS_EXPORT_KEY(tnbLib::TModel_ParaWire);

#endif // !_TModel_ParaWire_Header
