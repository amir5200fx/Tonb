#include <Geo2d_UniformNet.hxx>
#include <Entity2d_QuadMesh.hxx>

using namespace tnbLib;

int main()
{

	constexpr int nx = 5;
	constexpr int ny = 6;

	const auto alg = std::make_shared<Geo2d_UniformNet>();
	alg->SetNi(nx);
	alg->SetNj(ny);

	alg->Perform();

	const auto& indices = alg->Indices();
	std::vector<Pnt2d> coords;
	constexpr auto lx = 1.0;
	constexpr auto ly = 1.0;
	constexpr auto dx = lx / (double)nx;
	constexpr auto dy = ly / (double)ny;
	for (size_t j = 0; j <= ny; j++)
	{
		auto y = j * dy;
		for (size_t i = 0; i <= nx; i++)
		{
			auto x = i * dx;
			coords.emplace_back(x, y);
		}
	}
	const auto mesh = std::make_shared<Entity2d_QuadMesh>(coords, indices);
	OFstream myFile("mesh.plt");
	mesh->ExportToPlt(myFile);
	return 1;
}