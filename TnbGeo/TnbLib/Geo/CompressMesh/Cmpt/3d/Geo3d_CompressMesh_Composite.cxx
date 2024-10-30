#include <Geo3d_CompressMesh_Composite.hxx>

#include <Entity3d_CmpConnect_Brick.hxx>
#include <Entity3d_CmpConnect_ExtrudedPolygon.hxx>
#include <Entity3d_CmpConnect_Prism.hxx>
#include <Entity3d_CmpConnect_Pyramid.hxx>
#include <Entity3d_CmpConnect_Tetrahedron.hxx>
#include <Entity3d_CmpConnect.hxx>

template<>
std::vector<Standard_Integer> tnbLib::Geo3d_CompressMesh_Composite::get_components(const std::shared_ptr<Entity3d_CmpConnect>& theMat)
{
	return theMat->Components();
}

template<>
std::shared_ptr<tnbLib::Entity3d_CmpConnect> tnbLib::Geo3d_CompressMesh_Composite::update_matrix(
	const std::shared_ptr<Entity3d_CmpConnect>& theMat, const std::map<Standard_Integer, Standard_Integer>& ids)
{
	const auto cmpts = theMat->Components();
	auto get_id = [&ids, &cmpts](const Standard_Integer i)
		{
			return ids.at(cmpts.at(i));
		};
	if (theMat->IsBrick())
	{
		return std::make_shared<Entity3d_CmpConnect_Brick>(Entity3d_CmpConnect_Brick::Array8{
			get_id(0), get_id(1), get_id(2), get_id(3), get_id(4), get_id(5), get_id(6), get_id(7)
		});
	}
	if (theMat->IsExtrudedPolygon())
	{
		std::vector<Standard_Integer> new_ids;
		for (size_t i = 0; i < cmpts.at(i); i++)
		{
			new_ids.emplace_back(get_id(i));
		}
		return std::make_shared<Entity3d_CmpConnect_ExtrudedPolygon>(std::move(new_ids));
	}
	if (theMat->IsPyramid())
	{
		return std::make_shared<Entity3d_CmpConnect_Pyramid>(Entity3d_CmpConnect_Pyramid::Array5{
			get_id(0), get_id(1), get_id(2), get_id(3), get_id(4)
		});
	}
	if (theMat->IsPrism())
	{
		return std::make_shared<Entity3d_CmpConnect_Prism>(Entity3d_CmpConnect_Prism::Array6{
			get_id(0), get_id(1), get_id(2), get_id(3), get_id(4), get_id(5)
			});
	}
	if (theMat->IsTetrahedron())
	{
		return std::make_shared<Entity3d_CmpConnect_Tetrahedron>(Entity3d_CmpConnect_Tetrahedron::Array4{
			get_id(0), get_id(1), get_id(2), get_id(3)
		});
	}
	FatalErrorIn(FunctionSIG) << "\n"  // NOLINT(clang-diagnostic-language-extension-token)
		<< "Couldn't recognize the type of the connectivity.\n"
		<< abort(FatalError);
	return nullptr;
}
