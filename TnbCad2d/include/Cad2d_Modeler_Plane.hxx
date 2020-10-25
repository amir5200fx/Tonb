#pragma once
#ifndef _Cad2d_Modeler_Plane_Header
#define _Cad2d_Modeler_Plane_Header

#include <Standard_TypeDef.hxx>

#include <map>
#include <vector>
#include <memory>

namespace tnbLib
{

	// Forward Declarations
	class Cad2d_Plane;

	namespace cad2dLib
	{

		class Modeler_Plane
		{

			/*Private Data*/

			std::map<Standard_Integer, std::shared_ptr<Cad2d_Plane>>
				thePlanes_;

		protected:

			Modeler_Plane();

			void InsertToPlanes
			(
				const Standard_Integer theIndex,
				const std::shared_ptr<Cad2d_Plane>& thePlane
			);

			void InsertToPlanes
			(
				const Standard_Integer theIndex,
				std::shared_ptr<Cad2d_Plane>&& thePlane
			);

		public:

			Standard_Boolean 
				IsContainPlane
				(
					const Standard_Integer theIndex
				) const;

			Standard_Boolean 
				IsContain
				(
					const std::shared_ptr<Cad2d_Plane>& thePlane
				) const;

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

			std::shared_ptr<Cad2d_Plane>
				SelectPlane
				(
					const Standard_Integer theIndex
				) const;

			std::vector<std::shared_ptr<Cad2d_Plane>> 
				RetrievePlanes() const;

			void RetrievePlanesTo
			(
				std::vector<std::shared_ptr<Cad2d_Plane>>& thePlanes
			) const;

		};
	}
}

#endif // !_Cad2d_Modeler_Plane_Header
