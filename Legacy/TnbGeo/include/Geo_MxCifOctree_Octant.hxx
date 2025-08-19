#pragma once
#ifndef _Geo_MxCifOctree_Octant_Header
#define _Geo_MxCifOctree_Octant_Header

#include <Global_AccessMethod.hxx>
#include <Global_Indexed.hxx>
#include <Entity3d_Box.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations
	template<class T>
	class Geo_MxCifOctree_Node;

	template<class T>
	class Geo_MxCifOctree_Octant
		: public Global_Indexed
	{

		/*Private Data*/

		Entity3d_Box theBox_;

		std::shared_ptr<Geo_MxCifOctree_Node<T>> theZXPlane_;
		std::shared_ptr<Geo_MxCifOctree_Node<T>> theXYPlane_;
		std::shared_ptr<Geo_MxCifOctree_Node<T>> theYZPlane_;

		std::shared_ptr<Geo_MxCifOctree_Octant> theBNW_;
		std::shared_ptr<Geo_MxCifOctree_Octant> theBNE_;
		std::shared_ptr<Geo_MxCifOctree_Octant> theBSW_;
		std::shared_ptr<Geo_MxCifOctree_Octant> theBSE_;

		std::shared_ptr<Geo_MxCifOctree_Octant> theFNW_;
		std::shared_ptr<Geo_MxCifOctree_Octant> theFNE_;
		std::shared_ptr<Geo_MxCifOctree_Octant> theFSW_;
		std::shared_ptr<Geo_MxCifOctree_Octant> theFSE_;

	public:

		static std::shared_ptr<Geo_MxCifOctree_Node<T>> null_plane;
		static std::shared_ptr<Geo_MxCifOctree_Octant> null_octant;

		Geo_MxCifOctree_Octant()
		{}



		//- Macros
		GLOBAL_ACCESS_SINGLE(Entity3d_Box, Box)

			GLOBAL_ACCESS_SINGLE(std::shared_ptr<Geo_MxCifOctree_Node<T>>, ZXPlane)
			GLOBAL_ACCESS_SINGLE(std::shared_ptr<Geo_MxCifOctree_Node<T>>, XYPlane)
			GLOBAL_ACCESS_SINGLE(std::shared_ptr<Geo_MxCifOctree_Node<T>>, YZPlane)

			GLOBAL_ACCESS_SINGLE(std::shared_ptr<Geo_MxCifOctree_Octant>, BNW)
			GLOBAL_ACCESS_SINGLE(std::shared_ptr<Geo_MxCifOctree_Octant>, BNE)
			GLOBAL_ACCESS_SINGLE(std::shared_ptr<Geo_MxCifOctree_Octant>, BSW)
			GLOBAL_ACCESS_SINGLE(std::shared_ptr<Geo_MxCifOctree_Octant>, BSE)

			GLOBAL_ACCESS_SINGLE(std::shared_ptr<Geo_MxCifOctree_Octant>, FNW)
			GLOBAL_ACCESS_SINGLE(std::shared_ptr<Geo_MxCifOctree_Octant>, FNE)
			GLOBAL_ACCESS_SINGLE(std::shared_ptr<Geo_MxCifOctree_Octant>, FSW)
			GLOBAL_ACCESS_SINGLE(std::shared_ptr<Geo_MxCifOctree_Octant>, FSE)
	};
}

#endif // !_Geo_MxCifOctree_Octant_Header
