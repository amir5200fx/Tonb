#pragma once
#ifndef _PtdModel_Shape_Header
#define _PtdModel_Shape_Header

#include <PtdModel_Entity.hxx>

#include <memory>

namespace tnbLib
{

	// Forward declarations
	class Cad_Shape;

	class PtdModel_Shape
		: public PtdModel_Entity
	{

		/*Private Data*/

		std::shared_ptr<Cad_Shape> theShape_;


		//- private functions and operators

		TNB_SERIALIZATION(TnbPtdModel_EXPORT);

	protected:

		//- default constructor

		PtdModel_Shape()
		{}


		//- constructors

		TnbPtdModel_EXPORT PtdModel_Shape(const std::shared_ptr<Cad_Shape>& theShape);

		TnbPtdModel_EXPORT PtdModel_Shape(std::shared_ptr<Cad_Shape>&& theShape);

		TnbPtdModel_EXPORT PtdModel_Shape
		(
			const Standard_Integer theIndex, 
			const word& theName, 
			const std::shared_ptr<Cad_Shape>& theShape
		);

		TnbPtdModel_EXPORT PtdModel_Shape
		(
			const Standard_Integer theIndex, 
			const word& theName,
			std::shared_ptr<Cad_Shape>&& theShape
		);


	public:

		//- public functions and operators

		const auto& Shape() const
		{
			return theShape_;
		}

		TnbPtdModel_EXPORT void SetShape(const std::shared_ptr<Cad_Shape>&);
		TnbPtdModel_EXPORT void SetShape(std::shared_ptr<Cad_Shape>&&);
	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::PtdModel_Shape);

#endif // !_PtdModel_Shape_Header
