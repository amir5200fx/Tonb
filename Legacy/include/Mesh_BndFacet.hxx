#pragma once
#ifndef _Mesh_BndFacet_Header
#define _Mesh_BndFacet_Header

#include <Standard_TypeDef.hxx>

#include <vector>
#include <memory>

namespace tnbLib
{

	template<class BndFacetTraits>
	class Mesh_BndFacet
		: public BndFacetTraits::facetType
	{

	public:

		typedef typename BndFacetTraits::facetType facetType;

	private:

		/*Private Data*/

		// Private functions and operators

	public:

		//- default constructors

		Mesh_BndFacet() = default;

		//- constructors

		Mesh_BndFacet(const Standard_Integer theIndex)
			: facetType(theIndex)
		{}


		Standard_Boolean IsBoundary() const override;

		//- Static functions and operators
		
	};
}

#endif // !_Mesh_BndFacet_Header
