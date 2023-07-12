#pragma once
#ifndef _StbGMaker_WP_Header
#define _StbGMaker_WP_Header

#include <StbGMaker_Entity.hxx>
#include <Entity3d_Chain.hxx>

class gp_Ax2;
class gp_Pln;

#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class Cad2d_Modeler;
	class Pln_Edge;
	class Cad2d_Plane;

	class StbGMaker_WP
		: public StbGMaker_Entity
	{

		/*Private Data*/

		std::shared_ptr<Cad2d_Modeler> theModeler_;

		Standard_Real theX_;


		//- private functions and operators

		TNB_SERIALIZATION(TnbStbGMaker_EXPORT);

	protected:

		//- default constructor

		TnbStbGMaker_EXPORT StbGMaker_WP();


		//- constructors

		TnbStbGMaker_EXPORT explicit StbGMaker_WP(const Standard_Real theX);

		TnbStbGMaker_EXPORT StbGMaker_WP
		(
			const Standard_Integer theIndex,
			const Standard_Real theX
		);

		TnbStbGMaker_EXPORT StbGMaker_WP
		(
			const Standard_Integer theIndex,
			const word& theName, 
			const Standard_Real theX
		);

		auto& ChangeModeler()
		{
			return theModeler_;
		}

	public:

		TnbStbGMaker_EXPORT Standard_Integer NbPlanes() const;

		TnbStbGMaker_EXPORT std::shared_ptr<Entity3d_Chain> MakeMesh() const;

		virtual Standard_Boolean IsHull() const
		{
			return Standard_False;
		}

		virtual Standard_Boolean IsSail() const
		{
			return Standard_False;
		}

		virtual Standard_Boolean IsTank() const
		{
			return Standard_False;
		}

		auto X() const
		{
			return theX_;
		}

		const auto& Modeler() const
		{
			return theModeler_;
		}

		const auto& Modify() const
		{
			return theModeler_;
		}

		TnbStbGMaker_EXPORT gp_Pln gpPln(const gp_Ax2& theAx) const;

		TnbStbGMaker_EXPORT std::vector<std::shared_ptr<Cad2d_Plane>>
			RetrievePlanes() const;

		void SetX(const Standard_Real theX)
		{
			theX_ = theX;
		}

		TnbStbGMaker_EXPORT void Approx(const std::shared_ptr<Pln_Edge>& theEdge);

		void RetrievePlanesTo
		(
			std::vector<std::shared_ptr<Cad2d_Plane>>& thePlanes
		) const;


	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::StbGMaker_WP);

#endif // !_StbGMaker_WP_Header
