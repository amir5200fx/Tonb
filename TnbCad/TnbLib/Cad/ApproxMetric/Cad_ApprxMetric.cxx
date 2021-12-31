#include <Cad_ApprxMetric.hxx>

#include <Cad_ApprxMetricSubdivider.hxx>
#include <Cad_ApprxMetricInfo.hxx>
#include <Geo2d_ApprxSpace.hxx>
#include <Geo_AdTree.hxx>
#include <Geo_BoxTools.hxx>
#include <Geo2d_DelTri.hxx>
#include <Entity2d_Triangulation.hxx>
#include <Global_Timer.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

unsigned short tnbLib::Cad_ApprxMetric::verbose(0);

const std::shared_ptr<tnbLib::Cad_ApprxMetricInfo> tnbLib::Cad_ApprxMetric::DEFAULT_INFO =
std::make_shared<tnbLib::Cad_ApprxMetricInfo>();

namespace tnbLib
{
	class ApprxMetricNode
	{

		/*Private Data*/

		Pnt2d theCoord_;

	public:

		typedef Pnt2d ptType;

		// default constructor [12/27/2021 Amir]


		// constructors [12/27/2021 Amir]

		ApprxMetricNode(const Pnt2d& theCoord)
			: theCoord_(theCoord)
		{}

		ApprxMetricNode(Pnt2d&& theCoord)
			: theCoord_(std::move(theCoord))
		{}

		// public functions and operators [12/27/2021 Amir]

		const auto& Coord() const
		{
			return theCoord_;
		}

		auto& CoordRef()
		{
			return theCoord_;
		}

		static inline const Pnt2d& GetCoord(const std::shared_ptr<ApprxMetricNode>& node)
		{
			Debug_Null_Pointer(node);
			return node->Coord();
		}
	};

	Standard_Boolean InsertPoint
	(
		Geo_AdTree<std::shared_ptr<ApprxMetricNode>>& tree, 
		const Pnt2d& coord,
		const Standard_Real res,
		const Standard_Real tol
	)
	{
		auto b = Geo_BoxTools::GetBox(coord, res);
		std::vector<std::shared_ptr<ApprxMetricNode>> items;
		tree.GeometrySearch(b, items);
		if (items.empty())
		{
			auto node = std::make_shared<ApprxMetricNode>(coord);
			tree.InsertToGeometry(node);
			return Standard_True;
		}
		else
		{
			Standard_Real minDis = RealLast();
			for (const auto& x : items)
			{
				auto dis = coord.SquareDistance(x->Coord());
				if (dis < minDis)
				{
					minDis = dis;
				}
			}
			if (minDis < tol)
			{
				return Standard_False;
			}
			else
			{
				auto node = std::make_shared<ApprxMetricNode>(coord);
				tree.InsertToGeometry(node);
				return Standard_True;
			}
		}
	}
}

void tnbLib::Cad_ApprxMetric::Perform()
{
	if (verbose)
	{
		tnbLib::Info << endl
			<< "******* Approximating the Surface Metric ********" << endl
			<< endl;
	}

	if (NOT Geometry())
	{
		FatalErrorIn(FunctionSIG)
			<< " no surface is found!" << endl
			<< abort(FatalError);
	}

	if (NOT Domain())
	{
		FatalErrorIn(FunctionSIG)
			<< " no domain is loaded!" << endl
			<< abort(FatalError);
	}

	if (NOT Info())
	{
		FatalErrorIn(FunctionSIG)
			<< "no info is loaded!" << endl
			<< abort(FatalError);
	}

	Cad_ApprxMetricSubdivider subdivider(Geometry());

	if (Info()->Samples())
	{
		subdivider.SetSamples(Info()->Samples());
	}

	if (Info()->Criterion())
	{
		subdivider.SetCriterion(Info()->Criterion());
	}

	if (verbose)
	{
		tnbLib::Info << endl
			<< " Discretizing the space..." << endl;
	}

	std::vector<Entity2d_Box> boxes;
	{ // Timer scope [12/27/2021 Amir]
		Global_Timer timer;
		timer.SetInfo(Global_TimerInfo_ms);

		Geo2d_ApprxSpace<Cad_ApprxMetricSubdivider> alg;
		alg.SetDomain(*Domain());
		alg.SetMinLevel(Info()->MinLevel());
		alg.SetMaxLevel(Info()->MaxLevel());
		alg.SetMaxUnbalancingLevel(Info()->Unbalancing());

		alg.SetObject(&subdivider);
		alg.SetSubdivider(&Cad_ApprxMetricSubdivider::Subdivide);

		alg.Init();
		alg.Perform();

		alg.PostBalance();
		
		alg.RetrieveBoxesTo(boxes);
	}

	if (verbose)
	{
		tnbLib::Info << " - the space is discretized in, " << global_time_duration << ", ms." << endl;
	}

	if (verbose)
	{
		tnbLib::Info << endl
			<< " - Merging the points..." << endl;
	}

	const auto res = Info()->MergeInfo().Resolution();
	const auto tol = Info()->MergeInfo().Radius();

	if (verbose)
	{
		tnbLib::Info << " - resolution: " << res << ", Tolerance: " << tol << "." << endl;
	}

	std::vector<Pnt2d> points;
	{
		auto d = *Domain();
		d.Expand(d.Diameter()*1.05);

		Geo_AdTree<std::shared_ptr<ApprxMetricNode>> tree;	
		tree.SetGeometryRegion(d);
		tree.SetGeometryCoordFunc(&ApprxMetricNode::GetCoord);
		
		while (NOT boxes.empty())
		{
			const auto& b = boxes.back();

			const auto& p0 = b.P0();
			auto p1 = b.Corner(Box2d_PickAlgorithm_SE);
			const auto& p2 = b.P1();
			auto p3 = b.Corner(Box2d_PickAlgorithm_NW);

			InsertPoint(tree, p0, res, tol);
			InsertPoint(tree, p1, res, tol);
			InsertPoint(tree, p2, res, tol);
			InsertPoint(tree, p3, res, tol);

			boxes.pop_back();
		}

		std::vector<std::shared_ptr<ApprxMetricNode>> nodes;
		tree.RetrieveFromGeometryTo(nodes);

		tree.Clear();

		points.reserve(nodes.size());
		for (const auto& x : nodes)
		{
			auto p = std::move(x->CoordRef());
			points.push_back(std::move(p));
		}
	}

	if (verbose)
	{
		tnbLib::Info << endl
			<< " - Triangulation the points..." << endl;
	}

	{// timer scope [12/31/2021 Amir]
		Global_Timer timer;
		timer.SetInfo(Global_TimerInfo_ms);

		Geo2d_DelTri triAlg(points);
		triAlg.Triangulate();

		auto tri = std::make_shared<Entity2d_Triangulation>
			(
				std::move(points),
				std::move(triAlg.Data()->Connectivity())
				);
		theTriangulation_ = std::move(tri);
	}

	if (verbose)
	{
		tnbLib::Info << endl
			<< " - the space is triangulated in, " << global_time_duration << ", ms." << endl;
	}

	Change_IsDone() = Standard_True;

	if (verbose)
	{
		tnbLib::Info << endl
			<< "******* Surface Metric is approximated, successfully! ********" << endl
			<< endl;
	}
}