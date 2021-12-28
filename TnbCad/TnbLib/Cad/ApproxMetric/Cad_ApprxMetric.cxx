#include <Cad_ApprxMetric.hxx>

#include <Cad_ApprxMetricSubdivider.hxx>
#include <Geo2d_ApprxSpace.hxx>
#include <Geo_AdTree.hxx>
#include <Geo_BoxTools.hxx>
#include <Geo2d_DelTri.hxx>
#include <Entity2d_Triangulation.hxx>
#include <Global_Timer.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

const Standard_Integer tnbLib::Cad_ApprxMetric::DEFAULT_MIN_LEVEL(2);
const Standard_Integer tnbLib::Cad_ApprxMetric::DEFAULT_MAX_LEVEL(6);
const Standard_Integer tnbLib::Cad_ApprxMetric::DEFAULT_UNBALANCING(2);

const Standard_Real tnbLib::Cad_ApprxMetric::DEFAULT_RESOLUTION(1.0E-4);
const Standard_Real tnbLib::Cad_ApprxMetric::DEFAULT_TOLERANCE(1.0E-6);

unsigned short tnbLib::Cad_ApprxMetric::verbose(0);

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

	Cad_ApprxMetricSubdivider subdivider(Geometry());

	if (Samples())
	{
		subdivider.SetSamples(Samples());
	}

	if (Criterion())
	{
		subdivider.SetCriterion(Criterion());
	}

	std::vector<Entity2d_Box> boxes;
	{ // Timer scope [12/27/2021 Amir]
		Global_Timer timer;
		timer.SetInfo(Global_TimerInfo_ms);

		Geo2d_ApprxSpace<Cad_ApprxMetricSubdivider> alg;
		alg.SetDomain(*Domain());
		alg.SetMinLevel(MinLevel());
		alg.SetMaxLevel(MaxLevel());
		alg.SetMaxUnbalancingLevel(Unbalancing());

		alg.SetObject(&subdivider);
		alg.SetSubdivider(&Cad_ApprxMetricSubdivider::Subdivide);

		alg.Init();
		alg.Perform();

		alg.PostBalance();
		
		alg.RetrieveBoxesTo(boxes);
	}

	if (verbose)
	{
		Info << " - the space is discretized in, " << global_time_duration << ", ms." << endl;
	}

	if (verbose)
	{
		Info << endl
			<< " - Merging the points..." << endl;
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

			InsertPoint(tree, p0, Resolution(), Tolerance());
			InsertPoint(tree, p1, Resolution(), Tolerance());
			InsertPoint(tree, p2, Resolution(), Tolerance());
			InsertPoint(tree, p3, Resolution(), Tolerance());

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

	Geo2d_DelTri triAlg(points);
	triAlg.Triangulate();

	auto tri = std::make_shared<Entity2d_Triangulation>
		(
			std::move(points), 
			std::move(triAlg.Data()->Connectivity())
			);
	theTriangulation_ = std::move(tri);

	Change_IsDone() = Standard_True;
}