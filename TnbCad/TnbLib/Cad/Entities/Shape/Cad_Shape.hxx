#pragma once
#ifndef _Cad_Shape_Header
#define _Cad_Shape_Header

#include <Standard_Handle.hxx>
#include <Global_Serialization.hxx>
#include <Global_Named.hxx>
#include <Global_Indexed.hxx>
#include <Cad_Module.hxx>
#include <Entity3d_BoxFwd.hxx>

#include <TopoDS_Shape.hxx>

namespace tnbLib
{

	class Cad_Shape
		: public Global_Indexed
		, public Global_Named
	{

		/*Private Data*/

		TopoDS_Shape theShape_;

		std::shared_ptr<Entity3d_Box> theBoundingBox_;


		//- private functions and operators

		TNB_SERIALIZATION(TnbCad_EXPORT);

		void CalcBoundingBox();

		//- default constructor

		Cad_Shape()
		{}

	public:

		static TnbCad_EXPORT const std::string extension;

		//- default constructors


		//- constructors

		TnbCad_EXPORT Cad_Shape(const TopoDS_Shape& theShape);

		TnbCad_EXPORT Cad_Shape(const Standard_Integer theIndex, const word& theName, const TopoDS_Shape& theShape);

		TnbCad_EXPORT Cad_Shape(TopoDS_Shape&& theShape);

		TnbCad_EXPORT Cad_Shape(const Standard_Integer theIndex, const word& theName, TopoDS_Shape&& theShape);


		//- public functions and operators

		const auto& Shape() const
		{
			return theShape_;
		}

		const auto& BoundingBox() const
		{
			return theBoundingBox_;
		}

	};
}

#endif // !_Cad_Shape_Header
