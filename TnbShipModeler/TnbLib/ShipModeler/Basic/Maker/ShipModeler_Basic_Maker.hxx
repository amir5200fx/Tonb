#pragma once
#ifndef _ShipModeler_Basic_Maker_Header
#define _ShipModeler_Basic_Maker_Header

#include <Geo_ItemCounter.hxx>
#include <ShipModeler_Basic_Entity.hxx>
#include <ShipModeler_Basic_MakerAux.hxx>

#include <map>

class TopoDS_Shape;

namespace tnbLib
{

	namespace shipModelerLib
	{

		// Forward Declarations
		class Basic_WPlane;

		class Basic_Maker
			: public Basic_Entity
			, public Basic_MakerAux
		{

			/*Private Data*/

			std::map<Standard_Integer, std::shared_ptr<Basic_WPlane>>
				theWorkingPlanes_;

			mutable Geo_ItemCounter theCounter_;

			//- private functions and operators

			//- empty


		protected:

			template<class... _Types>
			Basic_Maker(_Types&&... _Args)
				: Basic_Entity(_Args...)
			{}
			

			std::shared_ptr<Basic_WPlane> 
				RemoveWorkingPlane
				(
					const Standard_Integer theIndex
				);

			void ImportWorkingPlane
			(
				const Standard_Integer theIndex,
				const std::shared_ptr<Basic_WPlane>&& thePlane
			);

			auto& Counter() const
			{
				return theCounter_;
			}


			void CreatePlane
			(
				const TopoDS_Shape& theShape, 
				const Standard_Real x
			);

		public:

			auto NbWorkingPlane() const
			{
				return (Standard_Integer)theWorkingPlanes_.size();
			}

			const auto& WorkingPlanes() const
			{
				return theWorkingPlanes_;
			}

			void CreateWorkingPlane
			(
				const Standard_Real x
			);
		};


	}
}

#endif // !_ShipModeler_Basic_Maker_Header
