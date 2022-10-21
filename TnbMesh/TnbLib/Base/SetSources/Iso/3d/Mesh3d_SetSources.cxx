#include <Mesh3d_SetSources.hxx>

#include <Mesh3d_SetSourcesAdaptor.hxx>
#include <Mesh3d_SetSourcesNode.hxx>
#include <Mesh3d_Node.hxx>
#include <Mesh2d_Element.hxx>
#include <MeshBase_Tools.hxx>
#include <GeoMesh3d_Background.hxx>
#include <GeoMesh3d_Data.hxx>
#include <Mesh3d_Element.hxx>
#include <Geo3d_AttrbBalPrTree.hxx>
#include <Geo_BoxTools.hxx>
#include <Entity3d_Box.hxx>
#include <Global_Timer.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{

	typedef Geo3d_AttrbBalPrTree<std::shared_ptr<meshLib::setSources::Node>, Mesh3d_Element>
		SearchEngine;

	auto RetrieveTetrahedrons(const std::vector<SearchEngine::leafNode*>& theLeaves)
	{
		std::vector<std::shared_ptr<Mesh3d_Element>> elements;
		for (const auto& x : theLeaves)
		{
			Debug_Null_Pointer(x);
			auto items = x->RetrieveTets();
			for (const auto& i : items)
			{
				elements.push_back(i);
			}
		}
		return std::move(elements);
	}

	namespace meshLib
	{

		namespace setSources
		{

			class TopNode
				: public Node
			{

				/*Private Data*/

				std::set<std::shared_ptr<Mesh3d_Element>> theElements_;

			public:

				// default constructor [10/21/2022 Amir]

				TopNode()
				{}

				// constructors [10/21/2022 Amir]

				TopNode(const Pnt3d& theCoord)
					: Node(theCoord)
				{}

				TopNode(Pnt3d&& theCoord)
					: Node(std::move(theCoord))
				{}

				// public functions and operators [10/21/2022 Amir]

				Standard_Integer NbElements() const
				{
					return theElements_.size();
				}

				const auto& Elements() const
				{
					return theElements_;
				}

				void Import(const std::shared_ptr<Mesh3d_Element>& theElement)
				{
					theElements_.insert(theElement);
				}
			};
		}
	}
}

void tnbLib::Mesh3d_SetSources::Perform()
{
	if (NOT Mesh())
	{
		FatalErrorIn(FunctionSIG)
			<< "no mesh has been loaded." << endl
			<< abort(FatalError);
	}

	const auto& meshData = Mesh()->Mesh();
	Debug_Null_Pointer(meshData);

	// Register the elements in a tree [8/13/2022 Amir]
	SearchEngine engine;
	engine.SetMaxUnbalancing(2);
	engine.SetGeometryCoordFunc(&meshLib::setSources::Node::GetCoord);
	engine.SetGeometryRegion(Mesh()->BoundingBox());
	engine.BUCKET_SIZE = 1;

	const auto mergCrit = Tolerance()*Mesh()->BoundingBox().Diameter();

	// create the node map [10/21/2022 Amir]
	//std::map<Standard_Integer, std::shared_ptr<meshLib::setSources::TopNode>> nodeMap;
	//for (const auto& x : meshData->Elements())
	//{
	//	Debug_Null_Pointer(x);

	//	for (Standard_Integer i = 0; i < 4; i++)
	//	{
	//		const auto& node = x->Node(i);
	//		auto iter = nodeMap.find(node->Index());
	//		if (iter IS_EQUAL nodeMap.end())
	//		{
	//			// the node is not at the map [10/21/2022 Amir]
	//			auto inode = std::make_shared<meshLib::setSources::TopNode>(node->Coord());
	//			Debug_Null_Pointer(inode);

	//			inode->Import(x);
	//			auto paired = std::make_pair(node->Index(), std::move(inode));
	//			nodeMap.insert(std::move(paired));
	//		}
	//		else
	//		{
	//			// the node is inside the map [10/21/2022 Amir]
	//			iter->second->Import(x);
	//		}
	//	}
	//}


	//for (const auto& x : meshData->Elements())
	//{
	//	Debug_Null_Pointer(x);

	//	for (Standard_Integer i = 0; i < 4; i++)
	//	{
	//		const auto& node = x->Node(i);
	//		auto iter = nodeMap.find(node->Index());
	//		if (iter IS_EQUAL nodeMap.end())
	//		{
	//			// the node is not at the map [10/21/2022 Amir]
	//			auto inode = std::make_shared<meshLib::setSources::TopNode>(node->Coord());
	//			Debug_Null_Pointer(inode);

	//			inode->Import(x);
	//			auto paired = std::make_pair(node->Index(), std::move(inode));
	//			nodeMap.insert(std::move(paired));
	//		}
	//		else
	//		{
	//			// the node is inside the map [10/21/2022 Amir]
	//			iter->second()
	//		}
	//	}

	//	auto c = x->Centre();
	//	auto b = Geo_BoxTools::GetBox<Pnt3d>(c, mergCrit);

	//	std::vector<std::shared_ptr<meshLib::setSources::Node>> items;
	//	engine.GeometrySearch(b, items);
	//	if (items.empty())
	//	{
	//		auto node = std::make_shared<meshLib::setSources::Node>(std::move(c));
	//		Debug_Null_Pointer(node);
	//		engine.InsertToGeometry(node);
	//	}
	//	else
	//	{
	//		Standard_Real minDis = RealLast();
	//		for (const auto& i : items)
	//		{
	//			auto dis = i->Coord().Distance(c);
	//			if (dis < minDis)
	//			{
	//				minDis = dis;
	//			}
	//		}
	//		if (minDis > mergCrit)
	//		{
	//			auto node = std::make_shared<meshLib::setSources::Node>(std::move(c));
	//			Debug_Null_Pointer(node);
	//			engine.InsertToGeometry(node);
	//		}
	//	}
	//}

	// Register the elements to the leaves [8/14/2022 Amir]
	//for (const auto& x : meshData->Elements())
	//{
	//	Debug_Null_Pointer(x);

	//	auto b = MeshBase_Tools::CalcBoundingBox(x);
	//	Debug_Null_Pointer(b);

	//	b->Expand(Tolerance()*b->Diameter());

	//	// Searching into the engine [8/14/2022 Amir]
	//	auto items = engine.RetrieveLeaves(*b);
	//	for (const auto& i : items)
	//	{
	//		Debug_Null_Pointer(i);
	//		i->InsertToTets(x);
	//	}
	//}
}