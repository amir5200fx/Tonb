#pragma once
#ifndef _Mesh2d_Node_Header
#define _Mesh2d_Node_Header

#include <Mesh2d_NodeTraits.hxx>
#include <Mesh_Node.hxx>

namespace tnbLib
{
	typedef Mesh_Node<Mesh2d_NodeTraits> Mesh2d_Node;
}

BOOST_CLASS_EXPORT_KEY(tnbLib::Mesh2d_Node);

#endif // !_Mesh2d_Node_Header