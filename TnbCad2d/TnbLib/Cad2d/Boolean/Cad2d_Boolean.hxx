#pragma once
#ifndef _Cad2d_Boolean_Header
#define _Cad2d_Boolean_Header

#include <Cad2d_Module.hxx>
#include <Global_TypeDef.hxx>

#include <memory>
#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class Cad2d_Plane;
	class Pnt2d;

	class Cad2d_Boolean
	{

	public:

		//static TnbCad2d_EXPORT Standard_Real Tolerance;

		static TnbCad2d_EXPORT std::shared_ptr<Cad2d_Plane>
			Union
			(
				const std::shared_ptr<Cad2d_Plane>& thePlane0, 
				const std::shared_ptr<Cad2d_Plane>& thePlane1,
				const Standard_Real theTol = 1.0E-6
			);

		static TnbCad2d_EXPORT std::vector<std::shared_ptr<Cad2d_Plane>>
			Subtract
			(
				const std::shared_ptr<Cad2d_Plane>& thePlane0,
				const std::shared_ptr<Cad2d_Plane>& thePlane1,
				const Standard_Real theTol = 1.0E-6
			);

		static TnbCad2d_EXPORT std::vector<std::shared_ptr<Cad2d_Plane>>
			Intersection
			(
				const std::shared_ptr<Cad2d_Plane>& thePlane0,
				const std::shared_ptr<Cad2d_Plane>& thePlane1,
				const Standard_Real theTol = 1.0E-6
			);
	};
}

#endif // !_Cad2d_Boolean_Header
