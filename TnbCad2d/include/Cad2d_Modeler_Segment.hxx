#pragma once
#ifndef _Cad2d_Modeler_Segment_Header
#define _Cad2d_Modeler_Segment_Header

#include <Cad2d_Module.hxx>
#include <Global_Serialization.hxx>
#include <Cad2d_Modeler_Entity.hxx>

#include <map>

namespace tnbLib
{

	class Pln_Edge;

	namespace cad2dLib
	{

		// Forward Declarations
		class Modeler_Corner;

		class Modeler_Segment
			: public Modeler_Entity
		{

			/*Private Data*/

			std::shared_ptr<Modeler_Corner> theCrn0_;
			std::shared_ptr<Modeler_Corner> theCrn1_;

			std::map<Standard_Integer, std::shared_ptr<Pln_Edge>>
				theEdges_;

			/*private functions and operators*/
			DECLARE_SAVE_LOAD_HEADER(TnbCad2d_EXPORT);
			

		protected:

			Modeler_Segment()
			{}

			auto& ChangeCrn0()
			{
				return theCrn0_;
			}

			auto& ChangeCrn1()
			{
				return theCrn1_;
			}

			auto& ChangeEdges()
			{
				return theEdges_;
			}

		public:

			Modeler_Segment
			(
				const std::shared_ptr<Modeler_Corner>& theC0, 
				const std::shared_ptr<Modeler_Corner>& theC1
			);

			Modeler_Segment
			(
				const Standard_Integer theIndex, 
				const std::shared_ptr<Modeler_Corner>& theC0,
				const std::shared_ptr<Modeler_Corner>& theC1
			);

			Modeler_Segment
			(
				const Standard_Integer theIndex,
				const word& theName, 
				const std::shared_ptr<Modeler_Corner>& theC0, 
				const std::shared_ptr<Modeler_Corner>& theC1
			);


			const auto& Crn0() const
			{
				return theCrn0_;
			}

			const auto& Crn1() const
			{
				return theCrn1_;
			}

			auto NbEdges() const
			{
				return (Standard_Integer)theEdges_.size();
			}

			const auto& Edges() const
			{
				return theEdges_;
			}

			virtual Standard_Boolean IsRing() const
			{
				return Standard_False;
			}

			virtual std::shared_ptr<Modeler_Corner> 
				Other
				(
					const std::shared_ptr<Modeler_Corner>& theCrn
				) const;

			std::shared_ptr<Pln_Edge> 
				RemoveFromEdges
				(
					const Standard_Integer theIndex
				);

			void ImportToEdges
			(
				const Standard_Integer theIndex,
				const std::shared_ptr<Pln_Edge>& theEdge
			);


		};

		class Modeler_Ring
			: public Modeler_Segment
		{

			/*Private Data*/


			/*private functions and operators*/
			DECLARE_SAVE_LOAD_HEADER(TnbCad2d_EXPORT);

		protected:

			Modeler_Ring()
			{}

		public:

			Modeler_Ring
			(
				const std::shared_ptr<Modeler_Corner>& theCrn
			);

			Modeler_Ring
			(
				const Standard_Integer theIndex, 
				const std::shared_ptr<Modeler_Corner>& theCrn
			);

			Modeler_Ring
			(
				const Standard_Integer theIndex,
				const word& theName, 
				const std::shared_ptr<Modeler_Corner>& theCrn
			);


			Standard_Boolean IsRing() const override
			{
				return Standard_True;
			}

			std::shared_ptr<Modeler_Corner>
				Other
				(
					const std::shared_ptr<Modeler_Corner>& theCrn
				) const override;
		};
	}
}

#endif // !_Cad2d_Modeler_Segment_Header
