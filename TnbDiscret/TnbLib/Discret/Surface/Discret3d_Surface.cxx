#include <Discret3d_Surface.hxx>

#include <Discret3d_Surface_SizeFunction.hxx>
#include <Discret3d_SurfaceInfo.hxx>
#include <Discret2d_Curve.hxx>
#include <Discret_CurveInfo.hxx>
#include <Discret_Curve_UniformSamples.hxx>
#include <Discret2d_Curve_UniLengthFun.hxx>
#include <Cad_GeomSurface.hxx>
#include <GModel_Surface.hxx>
#include <GModel_Wire.hxx>
#include <GModel_Edge.hxx>
#include <GModel_ParaCurve.hxx>
#include <Geo2d_BalPrTree.hxx>
#include <Geo_AdTree.hxx>
#include <Geo_BoxTools.hxx>
#include <Entity2d_Polygon.hxx>
#include <Entity2d_Box.hxx>
#include <Global_Timer.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#ifdef Handle
#undef Handle
#endif // Handle
#include <CGAL\Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL\Polygon_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;

typedef Kernel::Point_2 Point_2;
typedef CGAL::Polygon_2<Kernel> Polygon_2;

unsigned short tnbLib::Discret3d_Surface::verbose(0);

namespace tnbLib
{

	// Merging the points [11/16/2022 Amir]
	std::vector<std::shared_ptr<Pnt2d>> RetrieveOffsets
	(
		const std::vector<std::shared_ptr<Entity2d_Polygon>>& thePoly, 
		const Entity2d_Box& theDomain, 
		const Standard_Real theTol
	)
	{
		Geo_AdTree<std::shared_ptr<Pnt2d>> engine;
		engine.SetGeometryRegion(theDomain);
		engine.SetGeometryCoordFunc([](const std::shared_ptr<Pnt2d>& pt)->const auto&{return *pt; });

		const auto d = theTol * theDomain.Diameter();
		std::vector<std::shared_ptr<Pnt2d>> pts;
		for (const auto& pl : thePoly)
		{
			for (const auto& x : pl->Points())
			{
				auto b = Geo_BoxTools::GetBox(x, d);
				std::vector<std::shared_ptr<Pnt2d>> items;
				engine.GeometrySearch(b, items);
				if (items.empty())
				{
					auto p = std::make_shared<Pnt2d>(x);
					pts.push_back(std::move(p));
				}
				else
				{
					Standard_Real dmin = RealLast();
					for (const auto& i : items)
					{
						auto idis = x.Distance(*i);
						if (idis < dmin)
						{
							dmin = idis;
						}
					}
					if (dmin <= d)
					{
						// do nothing [11/16/2022 Amir]
					}
					else
					{
						auto p = std::make_shared<Pnt2d>(x);
						pts.push_back(std::move(p));
					}
				}
				
			}
		}
		return std::move(pts);
	}

	Standard_Boolean IsInside(const Entity2d_Box& b, const Polygon_2& poly)
	{
		static auto get_cgalPoint = [](const Pnt2d& p)
		{
			Point_2 pt(p.X(), p.Y());
			return std::move(pt);
		};

		{
			const auto& pt = b.P0();
			if (poly.bounded_side(get_cgalPoint(pt)) IS_EQUAL CGAL::ON_BOUNDED_SIDE)
			{
				return Standard_True;
			}
		}
		{
			const auto& pt = b.P1();
			if (poly.bounded_side(get_cgalPoint(pt)) IS_EQUAL CGAL::ON_BOUNDED_SIDE)
			{
				return Standard_True;
			}
		}
		{
			const auto pt = b.Corner(Box2d_PickAlgorithm_SE);
			if (poly.bounded_side(get_cgalPoint(pt)) IS_EQUAL CGAL::ON_BOUNDED_SIDE)
			{
				return Standard_True;
			}
		}
		{
			const auto pt = b.Corner(Box2d_PickAlgorithm_NW);
			if (poly.bounded_side(get_cgalPoint(pt)) IS_EQUAL CGAL::ON_BOUNDED_SIDE)
			{
				return Standard_True;
			}
		}
		return Standard_False;
	}

	Standard_Boolean IsCompletelyInside(const Entity2d_Box& b, const Polygon_2& poly)
	{
		static auto get_cgalPoint = [](const Pnt2d& p)
		{
			Point_2 pt(p.X(), p.Y());
			return std::move(pt);
		};

		{
			const auto& pt = b.P0();
			if (poly.bounded_side(get_cgalPoint(pt)) NOT_EQUAL CGAL::ON_BOUNDED_SIDE)
			{
				return Standard_False;
			}
		}
		{
			const auto& pt = b.P1();
			if (poly.bounded_side(get_cgalPoint(pt)) NOT_EQUAL CGAL::ON_BOUNDED_SIDE)
			{
				return Standard_False;
			}
		}
		{
			const auto pt = b.Corner(Box2d_PickAlgorithm_SE);
			if (poly.bounded_side(get_cgalPoint(pt)) NOT_EQUAL CGAL::ON_BOUNDED_SIDE)
			{
				return Standard_False;
			}
		}
		{
			const auto pt = b.Corner(Box2d_PickAlgorithm_NW);
			if (poly.bounded_side(get_cgalPoint(pt)) NOT_EQUAL CGAL::ON_BOUNDED_SIDE)
			{
				return Standard_False;
			}
		}
		return Standard_True;
	}

	Standard_Boolean IsInsideDomain(const Entity2d_Box& b, const std::pair<Polygon_2, std::vector<Polygon_2>>& pl)
	{
		const auto&[outer, inners] = pl;
		if (IsInside(b, outer))
		{
			for (const auto& x : inners)
			{
				if (IsCompletelyInside(b, x))
				{
					return Standard_False;
				}
			}
			return Standard_True;
		}
		return Standard_False;
	}


	Polygon_2 GetPolygon(const Entity2d_Polygon& thePoly)
	{
		static auto get_cgalPoint = [](const Pnt2d& p)
		{
			Point_2 pt(p.X(), p.Y());
			return std::move(pt);
		};
		Polygon_2 p;
		const auto& pts = thePoly.Points();
		for (size_t i = 0; i < pts.size() - 1; i++)
		{
			p.push_back(get_cgalPoint(pts.at(i)));
		}
		return std::move(p);
	}

	std::pair<Polygon_2, std::vector<Polygon_2>> 
		ConvertPolygon
		(
			const std::shared_ptr<Entity2d_Polygon>& theOuter,
			const std::shared_ptr<std::vector<std::shared_ptr<Entity2d_Polygon>>>& theInners
		)
	{
		auto outer = GetPolygon(*theOuter);
		std::vector<Polygon_2> polys;
		if (theInners)
		{
			polys.reserve(theInners->size());
			for (const auto& x : *theInners)
			{
				auto pl = GetPolygon(*x);
				polys.push_back(std::move(pl));
			}
		}
		auto t = std::make_pair(std::move(outer), std::move(polys));
		return std::move(t);
	}

	std::vector<Geo2d_BalPrTree<std::shared_ptr<Pnt2d>>::node*>
		RetrieveLeaves(Geo2d_BalPrTree<std::shared_ptr<Pnt2d>>::node* t)
	{
		std::vector<Geo2d_BalPrTree<std::shared_ptr<Pnt2d>>::leafNode*> leaves;
		Geo2d_BalPrTree<std::shared_ptr<Pnt2d>>::RetrieveLeavesTo(t, leaves);
		std::vector<Geo2d_BalPrTree<std::shared_ptr<Pnt2d>>::node*> nodes;
		nodes.reserve(leaves.size());
		for (auto x : leaves)
		{
			nodes.push_back(x);
		}
		return std::move(nodes);
	}

	std::vector<Geo2d_BalPrTree<std::shared_ptr<Pnt2d>>::node*>
		RetrieveLeaves(const std::vector<Geo2d_BalPrTree<std::shared_ptr<Pnt2d>>::node*>& theSpaces)
	{
		std::vector<Geo2d_BalPrTree<std::shared_ptr<Pnt2d>>::node*> nodes;
		for (auto x : theSpaces)
		{
			auto leaves = RetrieveLeaves(x);
			for (auto l : leaves)
			{
				nodes.push_back(l);
			}
		}
		return std::move(nodes);
	}

	void RetrieveInners(Geo2d_BalPrTree<std::shared_ptr<Pnt2d>>::node* t, const std::pair<Polygon_2, std::vector<Polygon_2>>& pl, std::vector<Geo2d_BalPrTree<std::shared_ptr<Pnt2d>>::node*>& items)
	{
		auto leaf = dynamic_cast<Geo2d_BalPrTree<std::shared_ptr<Pnt2d>>::leafNode*>(t);
		if (leaf)
		{
			if (IsInsideDomain(*leaf->Box(), pl) OR leaf->Size())
			{
				items.push_back(t);
			}		
		}
		else
		{
			if (IsInsideDomain(*t->Box(), pl))
			{
				auto leaves = RetrieveLeaves(t);
				for (auto l : leaves)
				{
					items.push_back(l);
				}
			}
			else
			{
				auto inner = dynamic_cast<Geo2d_BalPrTree<std::shared_ptr<Pnt2d>>::internalNode*>(t);
				Debug_Null_Pointer(inner);

				RetrieveInners(inner->Sw(), pl, items);
				RetrieveInners(inner->Se(), pl, items);
				RetrieveInners(inner->Ne(), pl, items);
				RetrieveInners(inner->Nw(), pl, items);
			}
		}
	}

	// Discard the potion of the space that are outside of the domain [11/16/2022 Amir]
	std::vector<Geo2d_BalPrTree<std::shared_ptr<Pnt2d>>::node*> 
		DiscardOuterSpace
		(
			const Geo2d_BalPrTree<std::shared_ptr<Pnt2d>>& theEngine, 
			const std::pair<Polygon_2, std::vector<Polygon_2>>& pl
		)
	{
		/*std::vector<Geo2d_BalPrTree<std::shared_ptr<Pnt2d>>::leafNode*> spaces;
		theEngine.RetrieveLeavesTo(spaces);*/
		std::vector<Geo2d_BalPrTree<std::shared_ptr<Pnt2d>>::node*> inners;
		RetrieveInners(theEngine.Root(), pl, inners);
		/*for (auto x : spaces)
		{
			if (x->Size()) inners.push_back(x);
			else
			{
				if (IsInsideDomain(*x->Box(), pl))
				{
					inners.push_back(x);
				}
			}
		}*/
		return std::move(inners);
	}

	struct SubdivideObject
	{

		std::shared_ptr<Cad_GeomSurface> surface;
		std::shared_ptr<Discret3d_Surface_Function> func;

		static Standard_Boolean doSubdivide(const Entity2d_Box& b, const SubdivideObject* obj)
		{
			const auto[u0, v0] = b.P0().Components();
			const auto[u1, v1] = b.P1().Components();

			return obj->func->Subdivide(obj->surface, u0, u1, v0, v1);
		}
	};

	void Subdivide
	(
		std::vector<Geo2d_BalPrTree<std::shared_ptr<Pnt2d>>::node*>& theNodes, 
		Geo2d_BalPrTree<std::shared_ptr<Pnt2d>>& theEngine, 
		const std::shared_ptr<Cad_GeomSurface>& theSurface,
		const std::shared_ptr<Discret3d_Surface_Function>& theFun, 
		const Standard_Integer theMaxLev
	)
	{
		SubdivideObject obj = { theSurface,theFun };
		for (auto& x : theNodes)
		{
			theEngine.PostSubdivide<SubdivideObject>(x, &SubdivideObject::doSubdivide, &obj, theMaxLev);
		}
	}

	std::vector<Pnt2d> 
		RetrieveSamples
		(
			const std::vector<Geo2d_BalPrTree<std::shared_ptr<Pnt2d>>::node*>& leaves, 
			const std::vector<std::shared_ptr<Pnt2d>>& theOffsets
		)
	{
		std::vector<Pnt2d> samples;
		samples.reserve(leaves.size() + theOffsets.size());
		for (auto x : leaves)
		{
			auto leaf = dynamic_cast<Geo2d_BalPrTree<std::shared_ptr<Pnt2d>>::leafNode*>(x);
			Debug_Null_Pointer(leaf);
			if (NOT leaf->Size())
			{
				Debug_Null_Pointer(leaf->Box());
				auto pt = leaf->Box()->CalcCentre();
				samples.push_back(std::move(pt));
			}
		}
		for (const auto& x : theOffsets)
		{
			samples.push_back(*x);
		}
		return std::move(samples);
	}

	std::vector<std::shared_ptr<Entity2d_Polygon>> 
		RetrieveAllPolygons
		(
			const std::shared_ptr<Entity2d_Polygon>& theOuter, 
			const std::shared_ptr<std::vector<std::shared_ptr<Entity2d_Polygon>>>& theInners
		)
	{
		std::vector<std::shared_ptr<Entity2d_Polygon>> polys;
		polys.push_back(theOuter);
		if (theInners)
		{
			for (const auto& x : *theInners)
			{
				polys.push_back(x);
			}
		}
		return std::move(polys);
	}
}

void tnbLib::Discret3d_Surface::Perform()
{
	if (NOT Surface())
	{
		FatalErrorIn(FunctionSIG)
			<< "no surface has been loaded." << endl
			<< abort(FatalError);
	}

	if (NOT AlgInfo())
	{
		FatalErrorIn(FunctionSIG)
			<< "no info has been loaded." << endl
			<< abort(FatalError);
	}

	if (NOT Domain())
	{
		FatalErrorIn(FunctionSIG)
			<< "no boundary domain has been loaded." << endl
			<< abort(FatalError);
	}

	const auto& surface = Surface();
	auto domain = *Domain();
	//domain.Expand(domain.Diameter()*1.0E-5);

	auto mEdges = RetrieveAllPolygons(Outer(), Inners());
	auto offsetPoints = RetrieveOffsets(mEdges, domain, domain.Diameter()*1.0E-5);

	Geo2d_BalPrTree<std::shared_ptr<Pnt2d>> engine;
	engine.SetMaxUnbalancing(2);
	engine.SetGeometryCoordFunc([](const std::shared_ptr<Pnt2d>& coord)-> const auto&{return *coord; });
	engine.SetGeometryRegion(domain);
	engine.BUCKET_SIZE = 1;

	{// approximation scope [11/15/2022 Amir]
		Global_Timer timer;
		timer.SetInfo(Global_TimerInfo_ms);

		for (const auto& x : offsetPoints)
		{
			Debug_Null_Pointer(x);
			engine.InsertToGeometry(x);
		}
	}

	if (verbose)
	{
		Info << endl
			<< " - the space is approximated in: " << global_time_duration << " ms." << endl;
	}
	std::cout << "post balancing..." << std::endl;
	if (AlgInfo()->PostBalance())
	{
		{
			Global_Timer timer;
			timer.SetInfo(Global_TimerInfo_ms);

			engine.SetMaxUnbalancing(2);
			engine.PostBalance();
		}

		if (verbose)
		{
			Info << endl
				<< " - the tree is balanced in: " << global_time_duration << " ms." << endl;
		}
	}
	std::cout << "convert" << std::endl;
	auto polys = ConvertPolygon(Outer(), Inners());
	std::cout << "discard" << std::endl;
	std::vector<Geo2d_BalPrTree<std::shared_ptr<Pnt2d>>::node*> spaces;
	{
		Global_Timer timer;
		timer.SetInfo(Global_TimerInfo_ms);

		spaces = DiscardOuterSpace(engine, polys);
	}

	if (verbose)
	{
		Info << endl
			<< " - the space has been detected in: " << global_time_duration << " ms." << endl;
	}
	std::cout << "retrieve nodes" << std::endl;
	// retrieve all leaves [11/15/2022 Amir]
	auto nodes = RetrieveLeaves(spaces);
	std::cout << "subdivide" << std::endl;
	{
		Global_Timer timer;
		timer.SetInfo(Global_TimerInfo_ms);

		Subdivide(nodes, engine, surface, this->SizeFun(), AlgInfo()->MaxNbSubs());
	}

	if (verbose)
	{
		Info << endl
			<< " - the space has been approximated in: " << global_time_duration << " ms." << endl;
	}
	std::cout << "retrieve leaves" << std::endl;
	auto leaves = RetrieveLeaves(nodes);
	auto samples2d = RetrieveSamples(leaves, offsetPoints);
	theCoords_ = std::make_shared<std::vector<Pnt2d>>(std::move(samples2d));
	PAUSE;
	Change_IsDone() = Standard_True;
}