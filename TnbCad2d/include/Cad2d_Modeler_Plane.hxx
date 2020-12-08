#pragma once
#ifndef _Cad2d_Modeler_Plane_Header
#define _Cad2d_Modeler_Plane_Header

#include <Standard_TypeDef.hxx>
#include <Cad2d_Module.hxx>
#include <Global_Serialization.hxx>

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


			/*private functions and operators*/
			TNB_SERIALIZATION(TnbCad2d_EXPORT);


			auto& ChangePlanes()
			{
				return thePlanes_;
			}

		protected:

			TnbCad2d_EXPORT Modeler_Plane();

			TnbCad2d_EXPORT void InsertToPlanes
			(
				const Standard_Integer theIndex,
				const std::shared_ptr<Cad2d_Plane>& thePlane
			);

			TnbCad2d_EXPORT void InsertToPlanes
			(
				const Standard_Integer theIndex,
				std::shared_ptr<Cad2d_Plane>&& thePlane
			);

		public:

			TnbCad2d_EXPORT Standard_Boolean
				IsContainPlane
				(
					const Standard_Integer theIndex
				) const;

			TnbCad2d_EXPORT Standard_Boolean
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

			TnbCad2d_EXPORT std::shared_ptr<Cad2d_Plane>
				RemoveFromPlanes
				(
					const Standard_Integer theIndex
				);

			TnbCad2d_EXPORT std::shared_ptr<Cad2d_Plane>
				SelectPlane
				(
					const Standard_Integer theIndex
				) const;

			TnbCad2d_EXPORT std::vector<std::shared_ptr<Cad2d_Plane>>
				RetrievePlanes() const;

			TnbCad2d_EXPORT void RetrievePlanesTo
			(
				std::vector<std::shared_ptr<Cad2d_Plane>>& thePlanes
			) const;

			TnbCad2d_EXPORT void ClearPlanes();
		};
	}
}

#endif // !_Cad2d_Modeler_Plane_Header
