#include <BoundarySizeMap3d_UniformFaceTool.hxx>

#include <Mesh3d_Element.hxx>
#include <MeshBase_Tools.hxx>
#include <TModel_Tools.hxx>
#include <TModel_Surface.hxx>
#include <GeoMesh_Background_Info.hxx>
#include <GeoMesh3d_Background.hxx>
#include <GeoMesh3d_Data.hxx>
#include <Geo3d_BalPrTree.hxx>
#include <Geo_ItemMerge.hxx>
#include <Geo_BoxTools.hxx>
#include <Entity3d_Box.hxx>
#include <Entity3d_Tetrahedralization.hxx>
#include <Global_Timer.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <Poly_Triangulation.hxx>


namespace tnbLib
{

	namespace meshLib
	{

		namespace faceTool
		{

			class Node
			{

				/*Private Data*/

				Pnt3d theCoord_;

				Standard_Real theValue_;

			public:

				typedef Pnt3d ptType;

				// default constructor [7/9/2022 Amir]

				Node()
					: theCoord_(Pnt3d::null)
					, theValue_(0)
				{}


				// constructors [7/9/2022 Amir]

				Node(const Pnt3d& theCoord, const Standard_Real h)
					: theCoord_(theCoord)
					, theValue_(h)
				{}

				Node(Pnt3d&& theCoord, const Standard_Real h)
					: theCoord_(std::move(theCoord))
					, theValue_(h)
				{}

				// public functions and operators [7/9/2022 Amir]

				const auto& Coord() const
				{
					return theCoord_;
				}

				auto H() const
				{
					return theValue_;
				}

				static const auto& GetCoord(const std::shared_ptr<Node>& node)
				{
					return node->Coord();
				}
			};
		}
	}
}

void tnbLib::BoundarySizeMap3d_UniformFaceTool::Perform()
{
	if (NOT Model())
	{
		FatalErrorIn(FunctionSIG)
			<< "no model has been found." << endl
			<< abort(FatalError);
	}
	if (NOT Domain())
	{
		FatalErrorIn(FunctionSIG)
			<< "no domain has been set!" << endl
			<< abort(FatalError);
	}

	auto faces = RetrieveFaces();
	if (verbose)
	{
		Info << " - nb. of faces: " << faces.size() << endl
			<< endl;
	}
	if (faces.empty()) return;

	//! Retrieve sizes
	Standard_Real elemSize, minElemSize, spanAngle;
	RetrieveValues(elemSize, minElemSize, spanAngle);

	if (verbose)
	{
		Info << " - Target element size: " << elemSize << endl;
		Info << " - Min. element size: " << minElemSize << endl;
		Info << " - Span size angle: " << spanAngle << endl;
		Info << endl;
	}

	Standard_Real radius = 0;
	if (MeshConditions().CustomBoundaryGrowthRate())
		radius =
		MeshBase_Tools::CalcRadius
		(
			Mesh_VariationRate::Rate(MeshValues().BoundaryGrowthRate()),
			elemSize,
			ReferenceValues()->BaseSize()
		);
	else
		radius =
		MeshBase_Tools::CalcRadius
		(
			Mesh_VariationRate::Rate(ReferenceValues()->DefaultGrowthRate()),
			elemSize,
			ReferenceValues()->BaseSize()
		);
	if (radius IS_EQUAL 0)
	{
		FatalErrorIn(FunctionSIG)
			<< "invalid radius value has been detected!" << endl
			<< abort(FatalError);
	}

	if (verbose > 1)
	{
		Info << " - Radius: " << radius << endl;
		Info << endl;
	}
	//const auto b = *Domain();
	const auto expB = *Domain();

	const auto mergCrit = 1.0E-5*expB.Diameter();

	if (verbose)
	{
		Info << " Approximating the whole domain..." << endl;
		Info << endl;
	}

	std::vector<std::shared_ptr<meshLib::faceTool::Node>> sources;
	std::vector<std::shared_ptr<Entity3d_Box>> boxes;
	{
		Geo3d_BalPrTree<std::shared_ptr<meshLib::faceTool::Node>> approxSpace;
		approxSpace.SetMaxUnbalancing(2);
		approxSpace.SetGeometryCoordFunc(&meshLib::faceTool::Node::GetCoord);
		approxSpace.SetGeometryRegion(expB);

		{ // Approximating space scope [7/10/2022 Amir]
			Global_Timer timer;
			timer.SetInfo(Global_TimerInfo_ms);

			for (const auto& x : faces)
			{
				auto poly = x->RetrieveTriangulation();
				if (NOT poly)
				{
					FatalErrorIn(FunctionSIG)
						<< "the edge has no triangulation with itself!" << endl
						<< abort(FatalError);
				}
				for (Standard_Integer i = 1; i < poly->NbNodes(); i++)
				{
					const auto& pt = poly->Node(i);
					auto b = Geo_BoxTools::GetBox<Pnt3d>(pt, mergCrit);

					std::vector<std::shared_ptr<meshLib::faceTool::Node>> items;
					approxSpace.GeometrySearch(b, items);
					if (items.empty())
					{
						auto node = std::make_shared<meshLib::faceTool::Node>(pt, elemSize);
						Debug_Null_Pointer(node);
						approxSpace.InsertToGeometry(node);
						sources.push_back(std::move(node));
					}
					else
					{
						Standard_Real minDis = RealLast();
						for (const auto& i : items)
						{
							auto dis = i->Coord().Distance(pt);
							if (dis < minDis)
							{
								minDis = dis;
							}
						}
						if (minDis > mergCrit)
						{
							auto node = std::make_shared<meshLib::faceTool::Node>(pt, elemSize);
							Debug_Null_Pointer(node);
							approxSpace.InsertToGeometry(node);
							sources.push_back(std::move(node));
						}
					}
				}
			}
		}

		if (verbose)
		{
			Info << endl
				<< " - the space is approximated in: " << global_time_duration << " ms." << endl;
		}

		// Post Balancing [7/10/2022 Amir]
		{
			Global_Timer timer;
			timer.SetInfo(Global_TimerInfo_ms);

			approxSpace.PostBalance();
		}

		if (verbose)
		{

			Info << endl
				<< " - the tree is balanced in: " << global_time_duration << " ms." << endl;
		}

		std::vector<Geo3d_BalPrTree<std::shared_ptr<meshLib::faceTool::Node>>::leafNode*> leaves;
		approxSpace.RetrieveLeavesTo(leaves);

		for (const auto& x : leaves)
		{
			const auto& b = x->Box();
			boxes.push_back(b);
		}
	}

	auto myTet = std::make_shared<Entity3d_Tetrahedralization>();
	Debug_Null_Pointer(myTet);
	// Triangulation [7/10/2022 Amir]
	{
		Global_Timer timer;
		timer.SetInfo(Global_TimerInfo_ms);

		Geo_BoxTools::GetTriangulation(boxes, *myTet);
	}

	if (verbose)
	{
		Info << endl
			<< " - the domain is triangulated in: " << global_time_duration << " ms." << endl;
	}

	if (verbose)
	{
		Info << " Constructing the background mesh..." << endl;
		Info << endl;
	}

	const auto bMesh = std::make_shared<GeoMesh3d_Background>();
	Debug_Null_Pointer(bMesh);

	bMesh->Mesh()->Construct(*myTet);
	bMesh->InitiateCurrentElement();
	bMesh->SetBoundingBox(std::move(expB));

	if (verbose)
	{
		Info << " Setting the sources into the background mesh..." << endl;
		Info << endl;
	}
	MeshBase_Tools::SetSourcesToMesh3d(sources, ReferenceValues()->BaseSize(), *bMesh);
	sources.clear();

	auto hvInfo = std::make_shared<GeoMesh_Background_SmoothingHvCorrection_Info>();
	Debug_Null_Pointer(hvInfo);
	hvInfo->SetMaxNbIters(MaxNbCorrIters());

	if (MeshConditions().CustomBoundaryGrowthRate())
		hvInfo->SetFactor(Mesh_VariationRate::Rate(ReferenceValues()->BoundaryGrowthRate()));
	else
		hvInfo->SetFactor(Mesh_VariationRate::Rate(ReferenceValues()->DefaultGrowthRate()));

	if (verbose)
	{
		Info << " Applying Hv-correction..." << endl;
		Info << " - Max. nb. of iterations: " << hvInfo->MaxNbIters() << endl;
		Info << endl;
	}
	bMesh->HvCorrection(hvInfo);

	ChangeBackMesh() = std::move(bMesh);
	Change_IsDone() = Standard_True;
}