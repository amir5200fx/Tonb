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

		void MakeModeler();

	public:

		StbGMaker_WP();

		StbGMaker_WP(const Standard_Real theX);

		StbGMaker_WP
		(
			const Standard_Integer theIndex,
			const Standard_Real theX
		);

		StbGMaker_WP
		(
			const Standard_Integer theIndex,
			const word& theName, 
			const Standard_Real theX
		);


		Standard_Integer NbPlanes() const;

		std::shared_ptr<Entity3d_Chain> MakeMesh() const;

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

		gp_Pln gpPln(const gp_Ax2& theAx) const;

		std::vector<std::shared_ptr<Cad2d_Plane>> 
			RetrievePlanes() const;

		void SetX(const Standard_Real theX)
		{
			theX_ = theX;
		}

		void Approx(const std::shared_ptr<Pln_Edge>& theEdge);

		void RetrievePlanesTo
		(
			std::vector<std::shared_ptr<Cad2d_Plane>>& thePlanes
		) const;


	};
}

#endif // !_StbGMaker_WP_Header
