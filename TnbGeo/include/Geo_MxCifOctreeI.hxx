#pragma once
namespace tnbLib
{
	template<class T>
	void Geo_MxCifOctree<T>::Search
	(
		const Entity3d_Box & theArea,
		const std::shared_ptr<octant>& theRoot,
		const Pnt3d & theCx,
		const Pnt3d & theLx, 
		std::vector<std::shared_ptr<T>>& theList
	) const
	{
		if (NOT theRoot)
		{
			return;
		}

		if (NOT Intersection(theArea, theCx, theLx))
		{
			return;
		}

		std::vector<std::shared_ptr<T>> Q;
		theRoot->XYPlane()->Quad()->Search(XY_PlaneBox(), Q);
		theRoot->YZPlane()->Quad()->Search(YZ_PlaneBox(), Q);
		theRoot->ZXPlane()->Quad()->Search(ZX_PlaneBox(), Q);

		const auto lx = 0.5*theLx.X();
		const auto ly = 0.5*theLx.Y();
		const auto lz = 0.5*theLx.Z();

		Search
		(
			theArea, 
			SON(theRoot, OctantCompare::BNE), 
			theCx + Pnt3d(XF(OctantCompare::BNE)*lx, YF(OctantCompare::BNE)*ly, ZF(OctantCompare::BNE)*lz),
			Pnt3d(lx, ly, lz), theList
		);

		Search
		(
			theArea,
			SON(theRoot, OctantCompare::BNW),
			theCx + Pnt3d(XF(OctantCompare::BNW)*lx, YF(OctantCompare::BNW)*ly, ZF(OctantCompare::BNW)*lz),
			Pnt3d(lx, ly, lz), theList
		);

		Search
		(
			theArea,
			SON(theRoot, OctantCompare::BSW),
			theCx + Pnt3d(XF(OctantCompare::BSW)*lx, YF(OctantCompare::BSW)*ly, ZF(OctantCompare::BSW)*lz),
			Pnt3d(lx, ly, lz), theList
		);

		Search
		(
			theArea,
			SON(theRoot, OctantCompare::BSE),
			theCx + Pnt3d(XF(OctantCompare::BSE)*lx, YF(OctantCompare::BSE)*ly, ZF(OctantCompare::BSE)*lz),
			Pnt3d(lx, ly, lz), theList
		);


		Search
		(
			theArea,
			SON(theRoot, OctantCompare::FNE),
			theCx + Pnt3d(XF(OctantCompare::FNE)*lx, YF(OctantCompare::FNE)*ly, ZF(OctantCompare::FNE)*lz),
			Pnt3d(lx, ly, lz), theList
		);

		Search
		(
			theArea,
			SON(theRoot, OctantCompare::FNW),
			theCx + Pnt3d(XF(OctantCompare::FNW)*lx, YF(OctantCompare::FNW)*ly, ZF(OctantCompare::FNW)*lz),
			Pnt3d(lx, ly, lz), theList
		);

		Search
		(
			theArea,
			SON(theRoot, OctantCompare::FSW),
			theCx + Pnt3d(XF(OctantCompare::FSW)*lx, YF(OctantCompare::FSW)*ly, ZF(OctantCompare::FSW)*lz),
			Pnt3d(lx, ly, lz), theList
		);

		Search
		(
			theArea,
			SON(theRoot, OctantCompare::FSE),
			theCx + Pnt3d(XF(OctantCompare::FSE)*lx, YF(OctantCompare::FSE)*ly, ZF(OctantCompare::FSE)*lz),
			Pnt3d(lx, ly, lz), theList
		);
	}
}