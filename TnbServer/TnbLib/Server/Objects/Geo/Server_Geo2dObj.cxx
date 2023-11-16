#include <Server_Geo2dObj.hxx>

#include <GeoSizeFun2d_Uniform.hxx>
#include <Entity2d_Box.hxx>

#include <json.hpp>

const std::string tnbLib::Server_Geo2dObj_SizeMap_Uniform::Params::size("size");
const std::string tnbLib::Server_Geo2dObj_SizeMap_Uniform::Params::bnd_box("domain");

void tnbLib::Server_Geo2dObj_SizeMap_Uniform::Construct(const std::string& theValue)
{
	std::shared_ptr<Entity2d_Box> bnd_box;
	double size;
	{
		defineTnbServerParser(theValue);
		{
			loadTnbServerObject(bnd_box);
		}
		{
			loadTnbServerObject(size);
		}
	}
	try
	{
		if (!bnd_box)
		{
			throw Server_Error("the bounding box object is null");
		}
		if (size <= gp::Resolution())
		{
			throw Server_Error("invalid value for a size function: " + std::to_string(size));
		}
		std::shared_ptr<Geo2d_SizeFunction> value = 
			std::make_shared<GeoSizeFun2d_Uniform>(size, *bnd_box);
		streamGoodTnbServerObject(value);
	}
	catchTnbServerErrors()
}
