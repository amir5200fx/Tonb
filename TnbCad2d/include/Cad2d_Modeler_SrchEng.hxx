#pragma once
#ifndef _Cad2d_Modeler_SrchEng_Header
#define _Cad2d_Modeler_SrchEng_Header

#include <Geo_ItemCounter.hxx>
#include <Geo_AdTree.hxx>
#include <Entity2d_Box.hxx>
#include <Cad2d_Modeler_Corner.hxx>

namespace tnbLib
{

	// Forward Declarations
	class Pln_Vertex;

	namespace cad2dLib
	{

		class Modeler_SrchEng
		{

			/*Private Data*/

			Geo_AdTree<std::shared_ptr<cad2dLib::Modeler_Corner>>
				theCorners_;

			Standard_Real theMaxRadius_;

			mutable Geo_ItemCounter theCornerCounter_;


			//- private functions and operators

			TNB_SERIALIZATION(TnbCad2d_EXPORT);


			const auto& Corners() const
			{
				return theCorners_;
			}

			auto& ChangeCorners()
			{
				return theCorners_;
			}

			auto& ChangeMaxRadius()
			{
				return theMaxRadius_;
			}

			TnbCad2d_EXPORT Standard_Boolean CheckDomain() const;

			TnbCad2d_EXPORT void CheckDomain(const char* theName) const;

		public:


			static TnbCad2d_EXPORT const std::shared_ptr<cad2dLib::Modeler_Corner> null;
			static TnbCad2d_EXPORT const Entity2d_Box null_domain;

			TnbCad2d_EXPORT Modeler_SrchEng();

			TnbCad2d_EXPORT Standard_Integer Size() const;

			TnbCad2d_EXPORT Standard_Boolean IsEmpty() const;

			auto Radius() const
			{
				return theMaxRadius_;
			}

			auto& Radius()
			{
				return theMaxRadius_;
			}

			auto& CornerCounter() const
			{
				return theCornerCounter_;
			}

			TnbCad2d_EXPORT std::shared_ptr<cad2dLib::Modeler_Corner>
				SelectCorner
				(
					const Pnt2d& theCoord
				) const;

			TnbCad2d_EXPORT std::shared_ptr<cad2dLib::Modeler_Corner>
				FindCorner
				(
					const std::shared_ptr<Pln_Vertex>& theVtx
				) const;

			TnbCad2d_EXPORT void ReArrangeSrchEngine();

			TnbCad2d_EXPORT void InsertToSrchEngine
			(
				const std::shared_ptr<cad2dLib::Modeler_Corner>& theCorner
			);

			TnbCad2d_EXPORT void RemoveFromSrchEngine
			(
				const std::shared_ptr<cad2dLib::Modeler_Corner>& theCorner
			);

			TnbCad2d_EXPORT void RetrieveCornersTo
			(
				std::vector<std::shared_ptr<cad2dLib::Modeler_Corner>>& theCorners
			) const;

			TnbCad2d_EXPORT void SetMaxRadius
			(
				const Standard_Real theRadius
			);

			TnbCad2d_EXPORT void SetDomain
			(
				const Entity2d_Box& theDomain
			);

			TnbCad2d_EXPORT void Clear();

			//- static functions

			static TnbCad2d_EXPORT Standard_Boolean
				IsNull
				(
					const std::shared_ptr<cad2dLib::Modeler_Corner>& theCorner
				);

			static TnbCad2d_EXPORT const std::shared_ptr<cad2dLib::Modeler_Corner>&
				MinDist
				(
					const std::vector<std::shared_ptr<cad2dLib::Modeler_Corner>>& theCorners,
					const Pnt2d& theCentre
				);

		};
	}

	
}

#endif // !_Cad2d_Modeler_SrchEng_Header
