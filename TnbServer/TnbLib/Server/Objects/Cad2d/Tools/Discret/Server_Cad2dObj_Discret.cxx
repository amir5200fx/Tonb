#include <Server_Cad2dObj_Discret.hxx>

#include <Geo_ApprxCurve_Info.hxx>
#include <Pln_Edge.hxx>
#include <Pln_Curve.hxx>
#include <Cad2d_Plane.hxx>
#include <Geo2d_ApprxCurve.hxx>
#include <Global_Timer.hxx>
#include <Entity2d_Box.hxx>
#include <json.hpp>

#include <Server_Error.hxx>

const std::string tnbLib::Server_Cad2dObj_Discret::Params::object_type = "object_type";
const std::string tnbLib::Server_Cad2dObj_Discret::Params::info = "info";
const std::string tnbLib::Server_Cad2dObj_Discret::Params::object = "object";

namespace tnbLib
{

	auto mesh_curve(const std::shared_ptr<Pln_Curve>& curve, const std::shared_ptr<Geo_ApprxCurve_Info>& info)
	{
		Global_Timer timer;
		timer.SetInfo(Global_TimerInfo_ms);
		const auto d = curve->BoundingBox(0).Diameter();
		info->SetApprox(info->Approx() * d);
		info->SetMinSize(info->MinSize() * d);
		auto alg =
			std::make_shared<Geo2d_ApprxCurve>
			(curve->Geometry(), curve->FirstParameter(), curve->LastParameter(), info);
		alg->Perform();
		return alg->Chain();
	}
}

void tnbLib::Server_Cad2dObj_Discret::Construct(const std::string& theValue)
{
	std::string object_type;
	std::shared_ptr<Geo_ApprxCurve_Info> info;
	std::shared_ptr<Pln_Edge> edge;
	std::shared_ptr<Cad2d_Plane> plane;
	int flag = 0;
	{
		defineTnbServerParser(theValue);
		{
			loadTnbServerObject(info);
		}
		{
			object_type = loader.at(Params::object_type).get<std::string>();
		}
		if (object_type == "curve")
		{
			std::stringstream stream;												
			stream << loader.at(Params::object).get<std::string>();
			TNB_iARCH_FILE_TYPE ia(stream);
			ia >> edge;
			flag = 1;
		}
		else if (object_type == "area")
		{
			std::stringstream stream;
			stream << loader.at(Params::object).get<std::string>();
			TNB_iARCH_FILE_TYPE ia(stream);
			ia >> plane;
			flag = 2;
		}
	}
	try
	{
		if (!flag)
		{
			throw Server_Error("the type of the object is not supported!");
		}
		if (flag == 1)
		{
			const auto& curve = edge->Curve();
			edge->Mesh() = mesh_curve(curve, info);
			streamGoodTnbServerObject(edge);
		}
		else
		{
			Global_Timer timer;
			timer.SetInfo(Global_TimerInfo_ms);

			std::vector<std::shared_ptr<Pln_Entity>> entities;
			plane->RetrieveSegmentsTo(entities);

			for (const auto& x: entities)
			{
				if (auto e = std::dynamic_pointer_cast<Pln_Edge>(x))
				{
					e->Mesh() = mesh_curve(e->Curve(), info);
				}
			}
			streamGoodTnbServerObject(plane);
		}
	}
	catch (error& x)
	{
		streamBadTnbServerObject(x.message());
	}
	catch (Standard_Failure& x)
	{
		streamBadTnbServerObject(x.GetMessageString());
	}
	catch (Server_Error& x)
	{
		streamBadTnbServerObject(x.what());
	}
	streamUnknownBadTnbServerObject();
}
