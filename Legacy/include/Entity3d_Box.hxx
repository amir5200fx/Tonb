#pragma once
#ifndef _Entity3d_Box_Header
#define _Entity3d_Box_Header

#include <Entity3d_BoxFwd.hxx>
#include <Entity_Box.hxx>
#include <Pnt3d.hxx>

namespace tnbLib
{

	template<>
	TnbGeo_EXPORT std::ostream& operator<<(std::ostream& os, const Entity3d_Box& theBox);

	template<>
	TnbGeo_EXPORT Ostream& operator<<(Ostream& os, const Entity3d_Box& theBox);

	enum Box3d_SubDivideAlgorithm
	{
		Box3d_SubDivideAlgorithm_Half_Down,
		Box3d_SubDivideAlgorithm_Half_Up,
		Box3d_SubDivideAlgorithm_Half_Left,
		Box3d_SubDivideAlgorithm_Half_Right,
		Box3d_SubDivideAlgorithm_Half_Aft,
		Box3d_SubDivideAlgorithm_Half_Fwd,
		Box3d_SubDivideAlgorithm_Fwd_SW,
		Box3d_SubDivideAlgorithm_Fwd_SE,
		Box3d_SubDivideAlgorithm_Fwd_NW,
		Box3d_SubDivideAlgorithm_Fwd_NE,
		Box3d_SubDivideAlgorithm_Aft_SW,
		Box3d_SubDivideAlgorithm_Aft_SE,
		Box3d_SubDivideAlgorithm_Aft_NW,
		Box3d_SubDivideAlgorithm_Aft_NE
	};

	enum Box3d_PickAlgorithm
	{
		Box3d_PickAlgorithm_Fwd_SW,
		Box3d_PickAlgorithm_Fwd_SE,
		Box3d_PickAlgorithm_Fwd_NE,
		Box3d_PickAlgorithm_Fwd_NW,
		Box3d_PickAlgorithm_Aft_SW,
		Box3d_PickAlgorithm_Aft_SE,
		Box3d_PickAlgorithm_Aft_NE,
		Box3d_PickAlgorithm_Aft_NW
	};

	template<>
	template<>
	TnbGeo_EXPORT Entity3d_Box Entity3d_Box::SubDivide<Box3d_SubDivideAlgorithm>
		(
			const Box3d_SubDivideAlgorithm theAlg
			) const;

	template<>
	template<>
	inline Pnt3d Entity3d_Box::Corner<Box3d_PickAlgorithm>
		(
			const Box3d_PickAlgorithm theAlg
			) const
	{
		const auto& P0 = this->P0();
		const auto& P1 = this->P1();

		switch (theAlg)
		{
		case Box3d_PickAlgorithm_Fwd_SW:
			return Pnt3d(P0.X(), P0.Y(), P1.Z());
		case Box3d_PickAlgorithm_Fwd_SE:
			return Pnt3d(P1.X(), P0.Y(), P1.Z());
		case Box3d_PickAlgorithm_Fwd_NE:
			return P1;
		case Box3d_PickAlgorithm_Fwd_NW:
			return Pnt3d(P0.X(), P1.Y(), P1.Z());

		case Box3d_PickAlgorithm_Aft_SW:
			return P0;
		case Box3d_PickAlgorithm_Aft_SE:
			return Pnt3d(P1.X(), P0.Y(), P0.Z());
		case Box3d_PickAlgorithm_Aft_NE:
			return Pnt3d(P1.X(), P1.Y(), P0.Z());
		case Box3d_PickAlgorithm_Aft_NW:
			return Pnt3d(P0.X(), P1.Y(), P0.Z());
		}
		return Pnt3d();
	}
}

#endif // !_Entity3d_Box_Header