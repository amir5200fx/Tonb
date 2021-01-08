#pragma once
#ifndef _Aft2d_NodeAnIso_Header
#define _Aft2d_NodeAnIso_Header

#include <Aft_Node.hxx>
#include <Aft2d_NodeAnIsoTraits.hxx>

namespace tnbLib
{

	typedef Aft_Node<Aft2d_NodeAnIsoTraits> Aft2d_NodeAnIso;

	template<>
	static TnbMesh_EXPORT const std::shared_ptr<Aft2d_NodeAnIso> Aft2d_NodeAnIso::null_ptr;
}

#endif // !_Aft2d_NodeAnIso_Header