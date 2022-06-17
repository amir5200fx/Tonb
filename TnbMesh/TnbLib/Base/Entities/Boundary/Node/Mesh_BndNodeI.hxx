#pragma once
#include <TnbError.hxx>
#include <OSstream.hxx>
template<class BndNodeTraits>
inline std::shared_ptr<typename tnbLib::Mesh_BndNode<BndNodeTraits>::edgeType> 
tnbLib::Mesh_BndNode<BndNodeTraits>::BlowThisUp()
{
	FatalErrorIn(FunctionSIG)
		<< "it's not supposed to be called." << endl
		<< abort(FatalError);
	return nullptr;
}