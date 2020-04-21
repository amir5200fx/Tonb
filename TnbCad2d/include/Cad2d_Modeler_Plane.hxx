#pragma once
#ifndef _Cad2d_Modeler_Plane_Header
#define _Cad2d_Modeler_Plane_Header

#include <Standard_TypeDef.hxx>

#include <map>
#include <memory>

namespace tnbLib
{

	// Forward Declarations
	class Cad2d_Plane;

	class Cad2d_Modeler_Plane
	{

		/*Private Data*/

		std::map<Standard_Integer, std::shared_ptr<Cad2d_Plane>>
			thePlanes_;

	protected:

		Cad2d_Modeler_Plane();


		auto NbPlanes() const
		{
			return (Standard_Integer)thePlanes_.size();
		}

		const auto& Planes() const
		{
			return thePlanes_;
		}

		std::shared_ptr<Cad2d_Plane> 
			RemoveFromPlanes
			(
				const Standard_Integer theIndex
			);

		void InsertToPlanes
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<Cad2d_Plane>& thePlane
		);

	};
}

#endif // !_Cad2d_Modeler_Plane_Header
