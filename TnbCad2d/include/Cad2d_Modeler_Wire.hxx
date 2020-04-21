#pragma once
#ifndef _Cad2d_Modeler_Wire_Header
#define _Cad2d_Modeler_Wire_Header

#include <Standard_TypeDef.hxx>

#include <memory>
#include <map>

namespace tnbLib
{

	// Forward Declarations
	class Pln_Wire;

	class Cad2d_Modeler_Wire
	{

		/*Private Data*/

		std::map<Standard_Integer, std::shared_ptr<Pln_Wire>>
			theWires_;

	protected:

		Cad2d_Modeler_Wire();

		auto NbWires() const
		{
			return (Standard_Integer)theWires_.size();
		}

		const auto& Wires() const
		{
			return theWires_;
		}

		std::shared_ptr<Pln_Wire> 
			RemoveFromWires
			(
				const Standard_Integer theIndex
			);

		void InsertToWires
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<Pln_Wire>& theWire
		);

		
	};
}

#endif // !_Cad2d_Modeler_Wire_Header
