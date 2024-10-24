#include <Geo2d_CompressMesh_Composite.hxx>

#include <Entity2d_CmpConnect_Polygon.hxx>
#include <Entity2d_CmpConnect_Pentagon.hxx>
#include <Entity2d_CmpConnect_Quad.hxx>
#include <Entity2d_CmpConnect_Triangle.hxx>
#include <Entity2d_CmpConnect.hxx>

template<>
std::vector<Standard_Integer> tnbLib::Geo2d_CompressMesh_Composite::get_components(
	const std::shared_ptr<Entity2d_CmpConnect>& theMat)
{
	return theMat->Components();
}

template<>
std::shared_ptr<tnbLib::Entity2d_CmpConnect> tnbLib::Geo2d_CompressMesh_Composite::update_matrix(
	const std::shared_ptr<Entity2d_CmpConnect>& theMat, const std::map<Standard_Integer, Standard_Integer>& ids)
{
	const auto cmpts = theMat->Components();
	auto get_id = [&ids, &cmpts](const Standard_Integer i)
		{
			return ids.at(cmpts.at(i));
		};
	if (theMat->IsPolygon())
	{
		std::vector<Standard_Integer> new_ids;
		for (size_t i = 0; i < cmpts.at(i); i++)
		{
			new_ids.emplace_back(get_id(i));
		}
		return std::make_shared<Entity2d_CmpConnect_Polygon>(std::move(new_ids));
	}
	if (theMat->IsPentagon())
	{
		return std::make_shared<Entity2d_CmpConnect_Pentagon>(Entity2d_CmpConnect_Pentagon::Array5{
			get_id(0), get_id(1), get_id(2), get_id(3), get_id(4)
		});
	}
	if (theMat->IsQuadrilateral())
	{
		return std::make_shared<Entity2d_CmpConnect_Quad>(Entity2d_CmpConnect_Quad::Array4{
			get_id(0), get_id(1), get_id(2), get_id(3)
		});
	}
	if (theMat->IsTriangle())
	{
		return std::make_shared<Entity2d_CmpConnect_Triangle>(Entity2d_CmpConnect_Triangle::Array3{
			get_id(0), get_id(1), get_id(2)
		});
	}
	FatalErrorIn(FunctionSIG) << "\n"  // NOLINT(clang-diagnostic-language-extension-token)
		<< "Couldn't recognize the type of the connectivity.\n"
		<< abort(FatalError);
	return nullptr;
}