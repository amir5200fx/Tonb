#include <Geo2d_UniformNet.hxx>

void tnbLib::Geo2d_UniformNet::Perform()
{
	theIndices_.reserve(Ni() * Nj());
	const auto ni = Ni() + 1;
	for (Standard_Integer j = 1; j <= Nj(); j++)
	{
		for (Standard_Integer i = 1; i <= Ni(); i++)
		{
			auto v0 = (j - 1) * ni + i;
			auto v1 = v0 + 1;
			auto v3 = j * ni + i;
			auto v2 = v3 + 1;
			connectivity::quadruple q;
			q.Value(0) = v0;
			q.Value(1) = v1;
			q.Value(2) = v2;
			q.Value(3) = v3;
			theIndices_.push_back(std::move(q));
		}
	}
	Change_IsDone() = Standard_True;
}
