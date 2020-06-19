#pragma once
namespace tnbLib
{
	template<class Point, class ConnectType, bool NeighbData>
	void Entity_StaticData<Point, ConnectType, NeighbData>::Add
	(
		const Entity_StaticData & theChain
	)
	{
		pointList points;
		points.reserve(thePoints_.size() + theChain.NbPoints());

		for (const auto& x : thePoints_)
		{
			points.push_back(std::move(x));
		}

		for (const auto& x : theChain.Points())
		{
			points.push_back(x);
		}

		auto connectivities = CombineConnectivities(Connectivity(), theChain.Connectivity());

		thePoints_.clear();
		theConnectivity_.clear();

		thePoints_ = std::move(points);
		theConnectivity_ = std::move(connectivities);

		if (theBoundingBox_)
			theBoundingBox_ = nullptr;
	}

	template<class Point, class ConnectType, bool NeighbData>
	std::shared_ptr<Entity_StaticData<Point, ConnectType, NeighbData>>
		Entity_StaticData<Point, ConnectType, NeighbData>::Added
		(
			const Entity_StaticData & theChain
		) const
	{
		auto copy = *this;
		copy.Add(theChain);

		auto p = std::make_shared<Entity_StaticData>(std::move(copy));
		return std::move(p);
	}
}