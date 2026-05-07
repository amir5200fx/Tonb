#pragma once
#ifndef _Geo_MxCifQuadtree_Quadrant_Header
#define _Geo_MxCifQuadtree_Quadrant_Header

#include <Global_AccessMethod.hxx>
#include <Global_Indexed.hxx>
#include <Entity2d_Box.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations
	template<class T>
	class Geo_MxCifQuadtree_Node;

	template<class T>
	class Geo_MxCifQuadtree_Quadrant
		: public Global_Indexed
	{

		typedef Geo_MxCifQuadtree_Node<T> node;
		typedef Geo_MxCifQuadtree_Quadrant<T> quad;

		/*Private Data*/

		std::shared_ptr<node> theAxisX_;
		std::shared_ptr<node> theAxisY_;

		std::shared_ptr<quad> theNW_;
		std::shared_ptr<quad> theNE_;
		std::shared_ptr<quad> theSW_;
		std::shared_ptr<quad> theSE_;

	public:

		static std::shared_ptr<quad> null;

		Geo_MxCifQuadtree_Quadrant()
		{}

		//- Macros
		GLOBAL_ACCESS_SINGLE(std::shared_ptr<node>, AxisX)
			GLOBAL_ACCESS_SINGLE(std::shared_ptr<node>, AxisY)

			GLOBAL_ACCESS_SINGLE(std::shared_ptr<quad>, NW)
			GLOBAL_ACCESS_SINGLE(std::shared_ptr<quad>, NE)
			GLOBAL_ACCESS_SINGLE(std::shared_ptr<quad>, SW)
			GLOBAL_ACCESS_SINGLE(std::shared_ptr<quad>, SE)
	};
}

#endif // !_Geo_MxCifQuadtree_Quadrant_Header
