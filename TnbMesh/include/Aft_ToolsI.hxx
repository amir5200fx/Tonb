#pragma once
#include <TnbError.hxx>
#include <OSstream.hxx>

template<class EdgeType>
inline std::vector<tnbLib::connectivity::dual> 
tnbLib::Aft_Tools::RetrieveEdgeConnectivities
(
	const std::vector<std::shared_ptr<EdgeType>>& theEdges
)
{
	std::vector<connectivity::dual> indices;
	indices.reserve(theEdges.size());
	for (const auto& x : theEdges)
	{
		const auto& n0 = x->Node0();
		const auto& n1 = x->Node1();

		Debug_Null_Pointer(n0);
		Debug_Null_Pointer(n1);

		auto i0 = n0->Index();
		auto i1 = n1->Index();

		connectivity::dual v;
		v.Value(0) = i0;
		v.Value(1) = i1;

		indices.push_back(std::move(v));
	}
	return std::move(indices);
}

template<class ElmType>
inline std::vector<tnbLib::connectivity::triple> 
tnbLib::Aft_Tools::RetrieveTriangleConnectivities
(
	const std::vector<std::shared_ptr<ElmType>>& theElements
)
{
	std::vector<connectivity::triple> indices;
	indices.reserve(theElements.size());
	for (const auto& x : theElements)
	{
		const auto& n0 = x->Node0();
		const auto& n1 = x->Node1();
		const auto& n2 = x->Node2();

		Debug_Null_Pointer(n0);
		Debug_Null_Pointer(n1);
		Debug_Null_Pointer(n2);

		auto i0 = n0->Index();
		auto i1 = n1->Index();
		auto i2 = n2->Index();

		connectivity::triple v;
		v.Value(0) = i0;
		v.Value(1) = i1;
		v.Value(2) = i2;

		indices.push_back(std::move(v));
	}
	return std::move(indices);
}

template<class ElmType>
inline std::vector<tnbLib::connectivity::triple> 
tnbLib::Aft_Tools::RetrieveTriangleConnectivities
(
	const std::vector<std::shared_ptr<ElmType>>& theElements,
	const std::map<Standard_Integer, Standard_Integer>& theIndices
)
{
	std::vector<connectivity::triple> indices;
	indices.reserve(theElements.size());
	try
	{
		for (const auto& x : theElements)
		{
			const auto& n0 = x->Node0();
			const auto& n1 = x->Node1();
			const auto& n2 = x->Node2();

			Debug_Null_Pointer(n0);
			Debug_Null_Pointer(n1);
			Debug_Null_Pointer(n2);

			auto i0 = n0->Index();
			auto i1 = n1->Index();
			auto i2 = n2->Index();

			connectivity::triple v;
			v.Value(0) = theIndices.at(i0);
			v.Value(1) = theIndices.at(i1);
			v.Value(2) = theIndices.at(i2);

			indices.push_back(std::move(v));
		}
	}
	catch (const std::out_of_range&)
	{
		FatalErrorIn(FunctionSIG)
			<< "out of rage error has been detected!" << endl
			<< abort(FatalError);
	}
	catch (const std::exception&)
	{
		FatalErrorIn(FunctionSIG)
			<< "unexpected error has been detected!" << endl
			<< abort(FatalError);
	}
	return std::move(indices);
}

template<class EntityType>
inline Standard_Integer 
tnbLib::Aft_Tools::MaxIndex
(
	const std::vector<std::shared_ptr<EntityType>>& theEntities
)
{
	if (theEntities.empty())
	{
		FatalErrorIn(FunctionSIG)
			<< "the list is empty!" << endl
			<< abort(FatalError);
	}
	auto iter = theEntities.begin();
	auto maxIndex = iter->Index();
	
	iter++;
	while (iter NOT_EQUAL theEntities.end())
	{
		if (iter->Index() > maxIndex)
			maxIndex = iter->Index();
		iter++;
	}
	return maxIndex;
}

template<class EntityType>
inline std::map<Standard_Integer, Standard_Integer> 
tnbLib::Aft_Tools::CompactIndices
(
	const std::vector<std::shared_ptr<EntityType>>& theEntities
)
{
	std::map<Standard_Integer, Standard_Integer> indices;
	Standard_Integer maxIndex = 0;
	for (const auto& x : theEntities)
	{
		Debug_Null_Pointer(x);

		auto paired = std::make_pair(x->Index(), ++maxIndex);
		auto insert = indices.insert(std::move(paired));
		if (NOT insert.second)
		{
			FatalErrorIn(FunctionSIG)
				<< "duplicate data has been detected!" << endl
				<< abort(FatalError);
		}
	}
	return std::move(indices);
}

template<class ElmType, class NodeType>
inline std::vector<tnbLib::connectivity::triple> 
tnbLib::Aft_Tools::RetrieveTriangleConnectivities
(
	const std::vector<std::shared_ptr<NodeType>>& theNodes, 
	const std::vector<std::shared_ptr<ElmType>>& theElements
)
{
	auto indices = RetrieveTriangleConnectivities(theElements, CompactIndices(theNodes));
	return std::move(indices);
}

template<class EdgeType>
inline std::shared_ptr<tnbLib::Entity2d_Chain> 
tnbLib::Aft_Tools::RetrieveEdgeMesh
(
	const std::vector<std::shared_ptr<EdgeType>>& theEdges
)
{
	auto nodes = RetrieveNodes(theEdges);
	auto points = RetrieveGeometry(nodes);

	auto indices = RetrieveEdgeConnectivities(theEdges);

	auto chain = std::make_shared<Entity2d_Chain>(std::move(points), std::move(indices));
	return std::move(chain);
}

template<class ElmType>
inline std::shared_ptr<tnbLib::Entity2d_Triangulation> 
tnbLib::Aft_Tools::RetrieveTriangleMesh
(
	const std::vector<std::shared_ptr<ElmType>>& theElements
)
{
	auto nodes = RetrieveNodes(theElements);
	auto points = RetrieveGeometry(nodes);

	auto indices = RetrieveTriangleConnectivities(nodes, theElements);

	auto tri = std::make_shared<Entity2d_Triangulation>(std::move(points), std::move(indices));
	return std::move(tri);
}

template<class EdgeType>
inline void tnbLib::Aft_Tools::Connect(const std::vector<std::shared_ptr<EdgeType>>& theEdges)
{
	for (const auto& x : theEdges)
	{
		const auto& n0 = x->Node0();
		const auto& n1 = x->Node1();

		Debug_Null_Pointer(n0);
		Debug_Null_Pointer(n1);

		n0->InsertToEdges(x->Index(), x);
		n1->InsertToEdges(x->Index(), x);
	}
}