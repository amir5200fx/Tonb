#pragma once
#ifndef _Geo_MxCifOctree_Node_Header
#define _Geo_MxCifOctree_Node_Header

#include <Global_AccessMethod.hxx>
#include <Global_TypeDef.hxx>

#include <memory>
#include <map>

namespace tnbLib
{

	// Forward Declarations
	template<class T>
	class Geo_MxCifQuadtree;

	template<class T>
	class Geo_MxCifOctree_Node
	{

		/*Private Data*/

		std::shared_ptr<Geo_MxCifQuadtree<T>> theQuad_;

	public:

		static std::shared_ptr<Geo_MxCifOctree_Node> null_node;

		Geo_MxCifOctree_Node()
		{}


		const auto& Quad() const
		{
			return theQuad_;
		}

		auto& Quad()
		{
			return theQuad_;
		}
	};
}

#include <Geo_MxCifOctree_NodeI.hxx>

#endif // !_Geo_MxCifOctree_Node_Header
