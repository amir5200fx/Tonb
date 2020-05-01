#pragma once
#ifndef _Cad2d_Modeler_SrchEng_Header
#define _Cad2d_Modeler_SrchEng_Header

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


			//- private functions and operators

			Standard_Boolean CheckDomain() const;

			void CheckDomain(const char* theName) const;

		protected:


			static const std::shared_ptr<cad2dLib::Modeler_Corner> null;
			static const Entity2d_Box null_domain;

			Modeler_SrchEng();

			auto Radius() const
			{
				return theMaxRadius_;
			}

			auto& Radius()
			{
				return theMaxRadius_;
			}

			const std::shared_ptr<cad2dLib::Modeler_Corner>&
				SelectCorner
				(
					const Pnt2d& theCoord
				) const;

			std::shared_ptr<cad2dLib::Modeler_Corner>
				FindCorner
				(
					const std::shared_ptr<Pln_Vertex>& theVtx
				) const;

			void ReArrangeSrchEngine();

			void InsertToSrchEngine
			(
				const std::shared_ptr<cad2dLib::Modeler_Corner>& theCorner
			);

			void RemoveFromSrchEngine
			(
				const std::shared_ptr<cad2dLib::Modeler_Corner>& theCorner
			);

			void SetMaxRadius
			(
				const Standard_Real theRadius
			);

		public:

			void SetDomain
			(
				const Entity2d_Box& theDomain
			);

		protected:

			//- static functions

			static Standard_Boolean
				IsNull
				(
					const std::shared_ptr<cad2dLib::Modeler_Corner>& theCorner
				);

			static const std::shared_ptr<cad2dLib::Modeler_Corner>&
				MinDist
				(
					const std::vector<std::shared_ptr<cad2dLib::Modeler_Corner>>& theCorners,
					const Pnt2d& theCentre
				);

		};
	}

	
}

#endif // !_Cad2d_Modeler_SrchEng_Header
