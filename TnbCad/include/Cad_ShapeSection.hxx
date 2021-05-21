#pragma once
#ifndef _Cad_ShapeSection_Header
#define _Cad_ShapeSection_Header

#include <Standard_TypeDef.hxx>
#include <Global_Done.hxx>
#include <Cad_Module.hxx>

#include <TopoDS_Shape.hxx>


//- Forward Declarations
class gp_Pln;
class TopoDS_Shape;

namespace tnbLib
{

	class Cad_ShapeSection
		: public Global_Done
	{

		/*Private Data*/

		const gp_Pln& thePlane_;
		const TopoDS_Shape& theShape_;

		Standard_Boolean Approx_;
		Standard_Boolean pPlaneCurve_;
		Standard_Boolean pShapeCurve_;

		Standard_Boolean ParallelMode_;


		TopoDS_Shape theSection_;

	public:


		//- default constructor


		//- constructors

		TnbCad_EXPORT Cad_ShapeSection
		(
			const gp_Pln& thePlane,
			const TopoDS_Shape& theShape
		);


		//- public functions and operators

		const auto& Section() const
		{
			return theSection_;
		}

		TnbCad_EXPORT void Perform();

		void SetApproximation(const Standard_Boolean approx)
		{
			Approx_ = approx;
		}

		void SetParallelMode(const Standard_Boolean mode)
		{
			ParallelMode_ = mode;
		}

	};
}

#endif // !_Cad_ShapeSection_Header
