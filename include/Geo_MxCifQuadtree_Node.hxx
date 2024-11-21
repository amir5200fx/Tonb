#pragma once
#ifndef _Geo_MxCifQuadtree_Node_Header
#define _Geo_MxCifQuadtree_Node_Header

#include <Global_AccessMethod.hxx>
#include <Global_TypeDef.hxx>

#include <memory>
#include <map>

namespace tnbLib
{

	template<class T>
	class Geo_MxCifQuadtree_Node
	{

		/*Private Data*/

		std::shared_ptr<Geo_MxCifQuadtree_Node<T>> theLeft_;
		std::shared_ptr<Geo_MxCifQuadtree_Node<T>> theRight_;

		std::map<Standard_Integer, std::shared_ptr<T>> theItems_;

	public:

		static std::shared_ptr<Geo_MxCifQuadtree_Node<T>> null;

		Geo_MxCifQuadtree_Node()
		{}

		auto NbItems() const
		{
			return (Standard_Integer)theItems_.size();
		}

		const auto& Items() const
		{
			return theItems_;
		}

		auto& Items()
		{
			return theItems_;
		}

		std::shared_ptr<T> Remove
		(
			const Standard_Integer theIndex
		);

		void Insert
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<T>& theItem
		);


		//- Macros
		GLOBAL_ACCESS_SINGLE(std::shared_ptr<Geo_MxCifQuadtree_Node<T>>, Left)
			GLOBAL_ACCESS_SINGLE(std::shared_ptr<Geo_MxCifQuadtree_Node<T>>, Right)
	};
}

#include <Geo_MxCifQuadtree_NodeI.hxx>

#endif // !_Geo_MxCifQuadtree_Node_Header
