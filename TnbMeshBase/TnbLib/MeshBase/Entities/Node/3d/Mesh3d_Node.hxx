#pragma once
#ifndef _Mesh3d_Node_Header
#define _Mesh3d_Node_Header

#include <Mesh_Node.hxx>
#include <Mesh3d_NodeTraits.hxx>

namespace tnbLib
{

	typedef Mesh_Node<Mesh3d_NodeTraits> Mesh3d_Node;
}

BOOST_CLASS_EXPORT_KEY(tnbLib::Mesh3d_Node);

#endif // !_Mesh3d_Node_Header