#pragma once
template<class Point>
inline Standard_Integer tnbLib::Geo_FVMesh<Point>::NbGroups() const
{
	if (HasGroup())
	{
		return theGroups_->size();
	}
	return 0;
}