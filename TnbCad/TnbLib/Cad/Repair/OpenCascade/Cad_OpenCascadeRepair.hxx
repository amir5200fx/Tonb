#pragma once
#ifndef _Cad_OpenCascadeRepair_Header
#define _Cad_OpenCascadeRepair_Header

#include <Global_Done.hxx>

#include <Standard_Handle.hxx>

class TopoDS_Shape;

namespace tnbLib
{

	class Cad_OpenCascadeRepair
		: public Global_Done
	{

		/*Private Data*/

		Handle(TopoDS_Shape) theShape_;

	public:

		//- default constructor

		Cad_OpenCascadeRepair()
		{}

		
		//- constructors


		//- public functions and operators

		const auto& Shape() const
		{
			return theShape_;
		}

		void Perform();

		void LoadShape(const Handle(TopoDS_Shape)& theShape)
		{
			theShape_ = theShape;
		}
	};
}

#endif // !_Cad_OpenCascadeRepair_Header
