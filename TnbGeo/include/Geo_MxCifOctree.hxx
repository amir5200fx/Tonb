#pragma once
#ifndef _Geo_MxCifOctree_Header
#define _Geo_MxCifOctree_Header

#include <Geo_MxCifOctree_Node.hxx>
#include <Geo_MxCifOctree_Octant.hxx>
#include <Geo_MxCifQuadtree.hxx>
#include <Geo_Tools.hxx>

#include <vector>

namespace tnbLib
{

	template<class T>
	class Geo_MxCifOctree
	{

		typedef Geo_MxCifOctree_Node<T> node;
		typedef Geo_MxCifOctree_Octant<T> octant;

		/*Private Data*/

		const Entity3d_Box& (*GetBox_)(const std::shared_ptr<T>& theItem);
		Standard_Integer(*GetIndex_)(const std::shared_ptr<T>& theItem);

		std::shared_ptr<Geo_MxCifOctree_Octant<T>> theRoot_;

		enum class TreeCompare
		{
			LEFT,
			RIGHT,
			BOTH
		};

		enum class OctantCompare
		{
			BNW,
			BNE,
			BSW,
			BSE,
			FNW,
			FNE,
			FSW,
			FSE
		};

		enum class Plane
		{
			XY,
			YZ,
			ZX
		};


		Plane(*SelectPlane_)(const TreeCompare theDxy, const TreeCompare theDyz, const TreeCompare theDzx);

		const Entity2d_Box& XY_PlaneBox() const;
		const Entity2d_Box& YZ_PlaneBox() const;
		const Entity2d_Box& ZX_PlaneBox() const;

		static Entity2d_Box GetPlaneBox(const Entity3d_Box& theBox, const Plane thePlane);

		static Standard_Boolean Intersection(const Entity3d_Box& theBox, const Pnt3d& theCx, const Pnt3d& theLx);

		static const std::shared_ptr<node>& GetPlane(const std::shared_ptr<octant>& t, const Plane pl);

		static OctantCompare SPCOCTANT(const OctantCompare oc)
		{
			switch (oc)
			{
			case OctantCompare::BSW: return OctantCompare::BNW;
			case OctantCompare::BSE: return OctantCompare::BSW;
			case OctantCompare::BNE: return OctantCompare::BSE;
			case OctantCompare::BNW: return OctantCompare::BNE;

			case OctantCompare::FSW: return OctantCompare::FNW;
			case OctantCompare::FSE: return OctantCompare::FSW;
			case OctantCompare::FNE: return OctantCompare::FSE;
			case OctantCompare::FNW: return OctantCompare::FNE;
			default:
				FatalErrorIn("OctantCompare SPCOCTANT(const OctantCompare oc)")
					<< "Invalid octant!" << endl
					<< abort(FatalError);
				return OctantCompare::BNW;
			}
		}

		static OctantCompare SPCCOCTANT(const OctantCompare oc)
		{
			switch (oc)
			{
			case OctantCompare::BSW: return OctantCompare::BSE;
			case OctantCompare::BSE: return OctantCompare::BNE;
			case OctantCompare::BNE: return OctantCompare::BNW;
			case OctantCompare::BNW: return OctantCompare::BSW;

			case OctantCompare::FSW: return OctantCompare::FSE;
			case OctantCompare::FSE: return OctantCompare::FNE;
			case OctantCompare::FNE: return OctantCompare::FNW;
			case OctantCompare::FNW: return OctantCompare::FSW;
			default:
				FatalErrorIn("OctantCompare SPCCOCTANT(const OctantCompare oc)")
					<< "Invalid octant!" << endl
					<< abort(FatalError);
				return OctantCompare::BNW;
			}
		}

		static OctantCompare SPOPOCTANT(const OctantCompare oc)
		{
			switch (oc)
			{
			case OctantCompare::BSW: return OctantCompare::BNE;
			case OctantCompare::BSE: return OctantCompare::BNW;
			case OctantCompare::BNE: return OctantCompare::BSW;
			case OctantCompare::BNW: return OctantCompare::BSE;

			case OctantCompare::FSW: return OctantCompare::FNE;
			case OctantCompare::FSE: return OctantCompare::FNW;
			case OctantCompare::FNE: return OctantCompare::FSW;
			case OctantCompare::FNW: return OctantCompare::FSE;
			default:
				FatalErrorIn("OctantCompare SPOPOCTANT(const OctantCompare oc)")
					<< "Invalid octant!" << endl
					<< abort(FatalError);
				return OctantCompare::BNW;
			}
		}

		static OctantCompare OPCOCTANT(const OctantCompare oc)
		{
			switch (oc)
			{
			case OctantCompare::BSW: return OctantCompare::FNW;
			case OctantCompare::BSE: return OctantCompare::FSW;
			case OctantCompare::BNE: return OctantCompare::FSE;
			case OctantCompare::BNW: return OctantCompare::FNE;

			case OctantCompare::FSW: return OctantCompare::BNW;
			case OctantCompare::FSE: return OctantCompare::BSW;
			case OctantCompare::FNE: return OctantCompare::BSE;
			case OctantCompare::FNW: return OctantCompare::BNE;
			default:
				FatalErrorIn("OctantCompare OPCOCTANT(const OctantCompare oc)")
					<< "Invalid octant!" << endl
					<< abort(FatalError);
				return OctantCompare::BNW;
			}
		}

		static OctantCompare OPCCOCTANT(const OctantCompare oc)
		{
			switch (oc)
			{
			case OctantCompare::BSW: return OctantCompare::FSE;
			case OctantCompare::BSE: return OctantCompare::FNE;
			case OctantCompare::BNE: return OctantCompare::FNW;
			case OctantCompare::BNW: return OctantCompare::FSW;

			case OctantCompare::FSW: return OctantCompare::BSE;
			case OctantCompare::FSE: return OctantCompare::BNE;
			case OctantCompare::FNE: return OctantCompare::BNW;
			case OctantCompare::FNW: return OctantCompare::BSW;
			default:
				FatalErrorIn("OctantCompare OPCCOCTANT(const OctantCompare oc)")
					<< "Invalid octant!" << endl
					<< abort(FatalError);
				return OctantCompare::BNW;
			}
		}

		static OctantCompare OPOPOCTANT(const OctantCompare oc)
		{
			switch (oc)
			{
			case OctantCompare::BSW: return OctantCompare::FNE;
			case OctantCompare::BSE: return OctantCompare::FNW;
			case OctantCompare::BNE: return OctantCompare::FSW;
			case OctantCompare::BNW: return OctantCompare::FSE;

			case OctantCompare::FSW: return OctantCompare::BNE;
			case OctantCompare::FSE: return OctantCompare::BNW;
			case OctantCompare::FNE: return OctantCompare::BSW;
			case OctantCompare::FNW: return OctantCompare::BSE;
			default:
				FatalErrorIn("OctantCompare OPOPOCTANT(const OctantCompare oc)")
					<< "Invalid octant!" << endl
					<< abort(FatalError);
				return OctantCompare::BNW;
			}
		}

		static OctantCompare OPOCTANT(const OctantCompare oc)
		{
			switch (oc)
			{
			case OctantCompare::BSW: return OctantCompare::FSW;
			case OctantCompare::BSE: return OctantCompare::FSE;
			case OctantCompare::BNE: return OctantCompare::FNE;
			case OctantCompare::BNW: return OctantCompare::FNW;

			case OctantCompare::FSW: return OctantCompare::BSW;
			case OctantCompare::FSE: return OctantCompare::BSE;
			case OctantCompare::FNE: return OctantCompare::BNE;
			case OctantCompare::FNW: return OctantCompare::BNW;
			default:
				FatalErrorIn("OctantCompare OPOCTANT(const OctantCompare oc)")
					<< "Invalid octant!" << endl
					<< abort(FatalError);
				return OctantCompare::BNW;
			}
		}

		static Standard_Integer GetAxis(const Plane pl)
		{
			switch (pl)
			{
			case Plane::XY: return 2;
			case Plane::YZ: return 0;
			case Plane::ZX: return 1;
			default:
				return -1;
			}
		}

		static TreeCompare
			BinCompare
			(
				const Entity3d_Box& theBox,
				const Standard_Real theX,
				const Plane pl
			)
		{
			Standard_Real x0, x1;
			theBox.GetBound(GetAxis(pl), x0, x1);

			const auto cx = MEAN(x0, x1);
			const auto lx = x1 - x0;

			if (cx - lx <= theX AND theX < cx + lx)
			{
				return TreeCompare::BOTH;
			}
			else if (theX < cx)
			{
				return TreeCompare::RIGHT;
			}
			else
			{
				return TreeCompare::LEFT;
			}
		}

		static TreeCompare OPDIRECTION(const TreeCompare d)
		{
			switch (d)
			{
			case TreeCompare::LEFT: return TreeCompare::RIGHT;
			case TreeCompare::RIGHT: return TreeCompare::LEFT;
			default:
				FatalErrorIn("TreeCompare OPDIRECTION(const TreeCompare d)")
					<< "Invalid data!" << endl
					<< abort(FatalError);
				return TreeCompare::BOTH;
			}
		}

		static OctantCompare 
			CIFCompare
			(
				const Entity3d_Box& theBox, 
				const Pnt3d& theCx
			)
		{
			const auto c = theBox.CalcCentre();
			if (c.Z() < theCx.Z())
			{
				if (c.X() < theCx.X())
				{
					if (c.Y() < theCx.Y()) return OctantCompare::BSW;
					else return OctantCompare::BNW;
				}
				else if (c.Y() < theCx.Y()) return OctantCompare::BSE;
				else return OctantCompare::BNE;
			}
			else
			{
				if (c.X() < theCx.X())
				{
					if (c.Y() < theCx.Y()) return OctantCompare::FSW;
					else return OctantCompare::FNW;
				}
				else if (c.Y() < theCx.Y()) return OctantCompare::FSE;
				else return OctantCompare::FNE;
			}
		}

		static Standard_Real VF(const TreeCompare t)
		{
			switch (t)
			{
			case TreeCompare::LEFT: return -1.0;
			case TreeCompare::RIGHT: return +1.0;
			default:
				return 0;
			}
		}

		static Standard_Real XF(const OctantCompare q);

		static Standard_Real YF(const OctantCompare q);

		static Standard_Real ZF(const OctantCompare q);

		static const std::shared_ptr<node>& BIN(const std::shared_ptr<octant>& t, const Plane pl)
		{
			switch (pl)
			{
			case Plane::XY: return t->XYPlane();
			case Plane::YZ: return t->YZPlane();
			case Plane::ZX: return t->ZXPlane();
			default:
				return octant::null_plane;
			}
		}

		static const std::shared_ptr<node>& CreateBIN(const std::shared_ptr<octant>& t, const Plane pl)
		{
			switch (pl)
			{
			case Plane::XY:
				auto& p = t->XYPlane();
				p = std::make_shared<node>();
				return p;
			case Plane::YZ:
				auto& p = t->YZPlane();
				p = std::make_shared<node>();
				return p;
			case Plane::ZX: 
				auto& p = t->ZXPlane();
				p = std::make_shared<node>();
				return p;
			default:
				return octant::null_plane;
			}
		}

		static const std::shared_ptr<octant>& SON(const std::shared_ptr<octant>& t, const OctantCompare q)
		{
			switch (q)
			{
			case OctantCompare::BNW: return t->BNW();
			case OctantCompare::BNE: return t->BNE();
			case OctantCompare::BSW: return t->BSW();
			case OctantCompare::BSE: return t->BSE();
			case OctantCompare::FNW: return t->FNW();
			case OctantCompare::FNE: return t->FNE();
			case OctantCompare::FSW: return t->FSW();
			case OctantCompare::FSE: return t->FSE();
			default:
				return octant::null_octant;
			}
		}

		static std::shared_ptr<octant>& ChangeSON(const std::shared_ptr<octant>& t, const OctantCompare q)
		{
			switch (q)
			{
			case OctantCompare::BNW: return t->BNW();
			case OctantCompare::BNE: return t->BNE();
			case OctantCompare::BSW: return t->BSW();
			case OctantCompare::BSE: return t->BSE();
			case OctantCompare::FNW: return t->FNW();
			case OctantCompare::FNE: return t->FNE();
			case OctantCompare::FSW: return t->FSW();
			case OctantCompare::FSE: return t->FSE();
			default:
				return octant::null_octant;
			}
		}

		static const std::shared_ptr<octant>& CreateSON(const std::shared_ptr<octant>& t, const OctantCompare q)
		{
			switch (q)
			{
			case OctantCompare::BNW:
				auto& p = t->BNW();
				p = std::make_shared<octant>();
				return p;
			case OctantCompare::BNE: 
				auto& p = t->BNE();
				p = std::make_shared<octant>();
				return p;
			case OctantCompare::BSW: 
				auto& p = t->BSW();
				p = std::make_shared<octant>();
				return p;
			case OctantCompare::BSE: 
				auto& p = t->BSE();
				p = std::make_shared<octant>();
				return p;
			case OctantCompare::FNW: 
				auto& p = t->FNW();
				p = std::make_shared<octant>();
				return p;
			case OctantCompare::FNE: 
				auto& p = t->FNE();
				p = std::make_shared<octant>();
				return p;
			case OctantCompare::FSW: 
				auto& p = t->FSW();
				p = std::make_shared<octant>();
				return p;
			case OctantCompare::FSE: 
				auto& p = t->FSE();
				p = std::make_shared<octant>();
				return p;
			default:
				return octant::null_octant;
			}
		}


		void Insert(const std::shared_ptr<T>& theItem, const std::shared_ptr<octant>& theRoot, const Pnt3d& theCx, const Pnt3d& theLx)
		{
			auto t = theRoot;
			const auto& b = GetBox_(theItem);

			if (NOT t)
			{
				t = std::make_shared<octant>();
			}

			auto dxy = BinCompare(b, theCx.Coord(GetAxis(Plane::XY) + 1), Plane::XY);
			auto dyz = BinCompare(b, theCx.Coord(GetAxis(Plane::YZ) + 1), Plane::YZ);
			auto dzx = BinCompare(b, theCx.Coord(GetAxis(Plane::ZX) + 1), Plane::ZX);

			auto lx = theLx.X();
			auto ly = theLx.Y();
			auto lz = theLx.Z();

			auto cx = theCx.X();
			auto cy = theCx.Y();
			auto cz = theCx.Z();

			while 
				(
					dxy NOT_EQUAL TreeCompare::BOTH AND 
					dyz NOT_EQUAL TreeCompare::BOTH AND 
					dzx NOT_EQUAL TreeCompare::BOTH
					)
			{
				auto q = CIFCompare(b, theCx);

				auto father = t;
				t = SON(t, q);

				if (NOT t)
				{
					t = CreateSON(father, q);
				}

				lx *= 0.5;
				ly *= 0.5;
				lz *= 0.5;

				cx += XF(q)*lx;
				cy += YF(q)*ly;
				cz += ZF(q)*lz;

				auto Cx = Pnt3d(cx, cy, cz);

				dxy = BinCompare(b, Cx.Coord(GetAxis(Plane::XY) + 1), Plane::XY);
				dyz = BinCompare(b, Cx.Coord(GetAxis(Plane::YZ) + 1), Plane::YZ);
				dzx = BinCompare(b, Cx.Coord(GetAxis(Plane::ZX) + 1), Plane::ZX);
			}

			auto Lx = Pnt3d(lx, ly, lz);
			auto Cx = Pnt3d(cx, cy, cz);
			auto selected = SelectPlane_(dxy, dyz, dzx);

			auto& p = GetPlane(t, selected);
			p->Quad()->Insert(theItem);
		}

		

		void Remove(const std::shared_ptr<T>& theItem, const std::shared_ptr<octant>& theRoot, const Pnt3d& theCx, const Pnt3d& theLx)
		{
			if (NOT theRoot)
			{
				return; // the tree is empty
			}

			auto t = theRoot;
			std::shared_ptr<octant> ft;
			OctantCompare qf;

			auto lx = theLx.X();
			auto ly = theLx.Y();
			auto lz = theLx.Z();

			auto cx = theCx.X();
			auto cy = theCx.Y();
			auto cz = theCx.Z();

			const auto& box = GetBox_(theItem);
			while 
				(
					BinCompare(box, theCx.Coord(GetAxis(Plane::XY) + 1), Plane::XY) NOT_EQUAL TreeCompare::BOTH AND 
					BinCompare(box, theCx.Coord(GetAxis(Plane::YZ) + 1), Plane::YZ) NOT_EQUAL TreeCompare::BOTH AND 
					BinCompare(box, theCx.Coord(GetAxis(Plane::ZX) + 1), Plane::ZX) NOT_EQUAL TreeCompare::BOTH
					)
			{
				//- Locate the quadrant in which P belongs
				auto q = CIFCompare(box, theCx);
				if (NOT SON(t, q))
				{
					FatalErrorIn("void Remove(Args..)")
						<< "the item is not in the tree!" << endl
						<< abort(FatalError);
				}

				if (
					SON(t, SPCOCTANT(q)) OR 
					SON(t, SPCCOCTANT(q)) OR 
					SON(t, SPOPOCTANT(q)) OR 
					SON(t, OPOCTANT(q)) OR 
					SON(t, OPCOCTANT(q)) OR 
					SON(t, OPCCOCTANT(q)) OR 
					SON(t, OPOPOCTANT(q)) OR 
					BIN(t, Plane::XY) OR 
					BIN(t, Plane::YZ) OR 
					BIN(t, Plane::ZX)
					)
				{
					ft = t;
					qf = q;
				}

				t = SON(t, q);

				lx *= 0.5;
				ly *= 0.5;
				lz *= 0.5;

				cx += XF(q)*lx;
				cy += YF(q)*ly;
				cz += ZF(q)*lz;
			}

			auto v = SelectPlane_
			(
				BinCompare(box, theCx.Coord(GetAxis(Plane::XY) + 1), Plane::XY), 
				BinCompare(box, theCx.Coord(GetAxis(Plane::YZ) + 1), Plane::YZ), 
				BinCompare(box, theCx.Coord(GetAxis(Plane::ZX) + 1), Plane::ZX)
			);

			auto& p = GetPlane(t, v);
			p->Quad()->Remove(theItem);
		}

		void Search(const Entity3d_Box& theArea, const std::shared_ptr<octant>& theRoot, const Pnt3d& theCx, const Pnt3d& theLx, std::vector<std::shared_ptr<T>>& theList) const;

	public:

		void Insert(const std::shared_ptr<T>& theItem);

		void Remove(const std::shared_ptr<T>& theItem);

		void Search(const Entity3d_Box& theDomain, std::vector<std::shared_ptr<T>>& theQ) const;

		std::vector<std::shared_ptr<T>> Search(const Entity3d_Box& theDomain) const;
	};
}

#include <Geo_MxCifOctreeI.hxx>

#endif // !_Geo_MxCifOctree_Header
