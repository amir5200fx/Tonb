#pragma once
#ifndef _Marine_Section_Header
#define _Marine_Section_Header

#include <Marine_Entity.hxx>

#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class Pln_Wire;

	class Marine_Section
		: public Marine_Entity
	{

		/*Private Data*/

		std::shared_ptr<Pln_Wire> theWire_;


		static void CheckWire(const Pln_Wire& theWire, const char* theName);

	public:

		Marine_Section
		(
			const std::shared_ptr<Pln_Wire>& theWire
		);

		Marine_Section
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<Pln_Wire>& theWire
		);

		Marine_Section
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::shared_ptr<Pln_Wire>& theWire
		);


		const auto& Wire() const
		{
			return theWire_;
		}


		//- static functions

		static Standard_Real 
			GetXcoord
			(
				const std::shared_ptr<Marine_Section>& theSection
			);
	};
}

#endif // !_Marine_Section_Header
