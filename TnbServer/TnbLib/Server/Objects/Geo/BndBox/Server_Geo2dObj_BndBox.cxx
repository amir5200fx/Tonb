#include <Server_Geo2dObj_BndBox.hxx>

#include <Geo_BoxTools.hxx>
#include <Entity2d_Box.hxx>
#include <json.hpp>
#include <Pln_Curve.hxx>

const std::string tnbLib::Server_Geo2dObj_BndBox_Create::Params::p0("p0");
const std::string tnbLib::Server_Geo2dObj_BndBox_Create::Params::p1("p1");

void tnbLib::Server_Geo2dObj_BndBox_Create::Construct(const std::string& theValue)
{
	Pnt2d p0, p1;
	{
		defineTnbServerParser(theValue);
		{
			loadTnbServerObject(p0);
		}
		{
			loadTnbServerObject(p1);
		}
	}
	auto value = std::make_shared<Entity2d_Box>(p0, p1);
	streamGoodTnbServerObject(value);
}

const std::string tnbLib::Server_Geo2dObj_BndBox_PntList::Params::pnt_list("pnt_list");
const std::string tnbLib::Server_Geo2dObj_BndBox_PntList::Params::offset("offset");

void tnbLib::Server_Geo2dObj_BndBox_PntList::Construct(const std::string& theValue)
{
	std::vector<Pnt2d> pnts;
	double offset;
	{
		defineTnbServerParser(theValue);
		{
			nlohmann::json json_array = nlohmann::json::parse(loader.at(Params::pnt_list).get<std::string>());
			if (json_array.is_array())
			{
				for (const auto& element: json_array)
				{
					Pnt2d pt;
					std::stringstream stream;
					stream << element.get<std::string>();
					TNB_iARCH_FILE_TYPE ia(stream);
					ia >> pt;
					pnts.emplace_back(std::move(pt));
				}
			}
			else
			{
				throw Server_Error("Couldn't load the point list.");
			}
		}
		{
			loadTnbServerObject(offset);
		}
	}
	auto b = std::make_shared<Entity2d_Box>(Geo_BoxTools::GetBox(pnts, offset));
	streamGoodTnbServerObject(b);
}

#include <Pln_Edge.hxx>

const std::string tnbLib::Server_Geo2dObj_BndBox_Curve::Params::curve("curve");
const std::string tnbLib::Server_Geo2dObj_BndBox_Curve::Params::offset("offset");

void tnbLib::Server_Geo2dObj_BndBox_Curve::Construct(const std::string& theValue)
{
	std::shared_ptr<Pln_Edge> curve;
	double offset;
	{
		defineTnbServerParser(theValue);
		{
			loadTnbServerObject(curve);
		}
		{
			loadTnbServerObject(offset);
		}
	}
	try
	{
		if (!curve)
		{
			throw Server_Error("the curve is null.");
		}
		auto b = std::make_shared<Entity2d_Box>(curve->BoundingBox(offset));
		streamGoodTnbServerObject(b);
	}
	catchTnbServerErrors()
}

const std::string tnbLib::Server_Geo2dObj_BndBox_CrvList::Params::cuvre_list("curve_list");
const std::string tnbLib::Server_Geo2dObj_BndBox_CrvList::Params::offset("offset");

void tnbLib::Server_Geo2dObj_BndBox_CrvList::Construct(const std::string& theValue)
{
	std::vector<std::shared_ptr<Pln_Curve>> curves;
	double offset;
	{
		defineTnbServerParser(theValue);
		{
			loadTnbServerObject(offset);
		}
		{
			nlohmann::json json_array = nlohmann::json::parse(loader.at(Params::cuvre_list).get<std::string>());
			if (json_array.is_array())
			{
				for (const auto& element: json_array)
				{
					std::shared_ptr<Pln_Curve> curve;
					std::stringstream stream;
					stream << element.get<std::string>();
					TNB_iARCH_FILE_TYPE ia(stream);
					ia >> curve;
					curves.emplace_back(std::move(curve));
				}
			}
		}
	}
	try
	{
		if (curves.empty())
		{
			throw Server_Error("the curve list is empty");
		}
		auto iter = curves.begin();
		auto b = (*iter)->BoundingBox(0);
		++iter;
		while(iter != curves.end())
		{
			b = Geo_BoxTools::Union(b, (*iter)->BoundingBox(0));
			++iter;
		}
		if (offset)
		{
			b.Expand(offset);
		}
		auto b_ptr = std::make_shared<Entity2d_Box>(std::move(b));
		streamGoodTnbServerObject(b_ptr);
	}
	catchTnbServerErrors()
}

#include <Cad2d_Plane.hxx>

const std::string tnbLib::Server_Geo2dObj_BndBox_Area::Params::offset("offset");
const std::string tnbLib::Server_Geo2dObj_BndBox_Area::Params::area("area");

void tnbLib::Server_Geo2dObj_BndBox_Area::Construct(const std::string& theValue)
{
	std::shared_ptr<Cad2d_Plane> area;
	double offset;
	{
		defineTnbServerParser(theValue);
		{
			loadTnbServerObject(area);
		}
		{
			loadTnbServerObject(offset);
		}
	}
	try
	{
		if (!area)
		{
			throw Server_Error("the area is null.");
		}
		auto b = std::make_shared<Entity2d_Box>(area->BoundingBox(offset));
		streamGoodTnbServerObject(b);
	}
	catchTnbServerErrors()
}

const std::string tnbLib::Server_Geo2dObj_BndBox_AreaList::Params::offset("offset");
const std::string tnbLib::Server_Geo2dObj_BndBox_AreaList::Params::area_list("area_list");

void tnbLib::Server_Geo2dObj_BndBox_AreaList::Construct(const std::string& theValue)
{
	std::vector<std::shared_ptr<Cad2d_Plane>> areas;
	double offset;
	{
		defineTnbServerParser(theValue);
		{
			loadTnbServerObject(offset);
		}
		{
			nlohmann::json json_array = nlohmann::json::parse(loader.at(Params::area_list).get<std::string>());
			if (json_array.is_array())
			{
				for (const auto& element: json_array)
				{
					std::shared_ptr<Cad2d_Plane> area;
					std::stringstream stream;
					stream << element.get<std::string>();
					TNB_iARCH_FILE_TYPE ia(stream);
					ia >> area;
					areas.emplace_back(std::move(area));
				}
				
			}
			else
			{
				throw Server_Error("Couldn't load the area list.");
			}
		}
	}
	try
	{
		if (areas.empty())
		{
			throw Server_Error("the area list is empty");
		}
		auto iter = areas.begin();
		auto b = (*iter)->BoundingBox(0);
		++iter;
		while (iter != areas.end())
		{
			b = Geo_BoxTools::Union(b, (*iter)->BoundingBox(0));
			++iter;
		}
		if (offset)
		{
			b.Expand(offset);
		}
		auto b_ptr = std::make_shared<Entity2d_Box>(std::move(b));
		streamGoodTnbServerObject(b_ptr);
	}
	catchTnbServerErrors()
}

void tnbLib::Server_Geo2dObj_BndBox_GetDia::Construct(const std::string& theValue)
{
	std::shared_ptr<Entity2d_Box> b;
	loadNonJSONTnbServer(b);
	try
	{
		if (!b)
		{
			throw Server_Error("the bounding box object is null.");
		}
		nlohmann::json j;
		j[SENSE] = GetRespType(RespType::good);
		j[VALUE] = b->Diameter();
		theStream_ << j;
	}
	catchTnbServerErrors()
}

void tnbLib::Server_Geo2dObj_BndBox_GetCorners::Construct(const std::string& theValue)
{
	std::shared_ptr<Entity2d_Box> b;
	loadNonJSONTnbServer(b);
	try
	{
		if (!b)
		{
			throw Server_Error("the bounding box object is null.");
		}
		std::stringstream stream;
		{
			nlohmann::json j;
			serializedTnbObjectAtJSON(b->P0(), "p0", j)
				serializedTnbObjectAtJSON(b->P1(), "p1", j)
				stream << j;
		}
		nlohmann::json j;
		j[SENSE] = GetRespType(RespType::good);
		j[VALUE] = stream.str();
		theStream_ << j;
	}
	catchTnbServerErrors()
}

void tnbLib::Server_Geo2dObj_BndBox_GetLengths::Construct(const std::string& theValue)
{
	std::shared_ptr<Entity2d_Box> b;
	loadNonJSONTnbServer(b);
	try
	{
		if (!b)
		{
			throw Server_Error("the bounding box object is null.");
		}
		std::stringstream stream;
		{
			auto [lx, ly] = b->Length();
			nlohmann::json j;
			{
				j["lx"] = lx;
			}
			{
				j["ly"] = ly;
			}
			stream << j;
		}
		nlohmann::json j;
		j[SENSE] = GetRespType(RespType::good);
		j[VALUE] = stream.str();
		theStream_ << j;
	}
	catchTnbServerErrors()
}

const std::string tnbLib::Server_Geo2dObj_BndBox_Expand::Params::offset("offset");
const std::string tnbLib::Server_Geo2dObj_BndBox_Expand::Params::bnd_box("bnd_box");

void tnbLib::Server_Geo2dObj_BndBox_Expand::Construct(const std::string& theValue)
{
	std::shared_ptr<Entity2d_Box> bnd_box;
	double offset;
	{
		defineTnbServerParser(theValue);
		{
			loadTnbServerObject(bnd_box);
		}
		{
			loadTnbServerObject(offset);
		}
	}
	try
	{
		if (!bnd_box)
		{
			throw Server_Error("the bounding box object is null.");
		}
		if (offset < 0)
		{
			throw Server_Error("invalid value to offset the bounding box");
		}
		bnd_box->Expand(offset);
		streamGoodTnbServerObject(bnd_box);
	}
	catchTnbServerErrors()
}

