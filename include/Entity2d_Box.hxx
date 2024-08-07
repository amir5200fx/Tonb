#pragma once
#ifndef _Entity2d_Box_Header
#define _Entity2d_Box_Header

#include <Entity2d_BoxFwd.hxx>
#include <Entity_Box.hxx>
#include <Pnt2d.hxx>

namespace tnbLib
{

	template<>
	TnbGeo_EXPORT std::ostream& operator<<(std::ostream& os, const Entity2d_Box& theBox);

	template<>
	TnbGeo_EXPORT Ostream& operator<<(Ostream& os, const Entity2d_Box& theBox);

	enum Box2d_SubDivideAlgorithm
	{
		Box2d_SubDivideAlgorithm_Half_Down,
		Box2d_SubDivideAlgorithm_Half_Up,
		Box2d_SubDivideAlgorithm_Half_Left,
		Box2d_SubDivideAlgorithm_Half_Right,
		Box2d_SubDivideAlgorithm_Quad_SW,
		Box2d_SubDivideAlgorithm_Quad_SE,
		Box2d_SubDivideAlgorithm_Quad_NW,
		Box2d_SubDivideAlgorithm_Quad_NE
	};

	enum Box2d_PickAlgorithm
	{
		Box2d_PickAlgorithm_SW,
		Box2d_PickAlgorithm_SE,
		Box2d_PickAlgorithm_NE,
		Box2d_PickAlgorithm_NW
	};

	template<>
	template<>
	TnbGeo_EXPORT Entity2d_Box Entity2d_Box::SubDivide<Box2d_SubDivideAlgorithm>
		(
			const Box2d_SubDivideAlgorithm theAlg
			) const;

	template<>
	template<>
	inline Pnt2d Entity2d_Box::Corner<Box2d_PickAlgorithm>
		(
			const Box2d_PickAlgorithm theAlg
			) const
	{
		switch (theAlg)
		{
		case Box2d_PickAlgorithm_SW:
			return P0();
		case Box2d_PickAlgorithm_SE:
			return Pnt2d(P1().X(), P0().Y());
		case Box2d_PickAlgorithm_NE:
			return P1();
		case Box2d_PickAlgorithm_NW:
			return Pnt2d(P0().X(), P1().Y());
		}
		return Pnt2d();
	}

	template<>
	TnbGeo_EXPORT void Entity2d_Box::ExportToPlt(OFstream&) const;

}

#endif // !_Entity2d_Box_Header