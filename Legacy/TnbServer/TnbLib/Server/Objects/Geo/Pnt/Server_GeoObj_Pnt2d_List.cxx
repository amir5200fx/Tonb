#include <Server_GeoObj_Pnt2d_List.hxx>

#include <Pnt2d.hxx>
#include <json.hpp>

void tnbLib::Server_GeoObj_Pnt2d_List::Construct(const std::string& theValue)
{
	std::vector<Pnt2d> pnt_list;
	defineTnbServerParser(theValue);
	for (const auto& x: loader)
	{
		std::stringstream stream;
		stream << x.get<std::string>();
		TNB_iARCH_FILE_TYPE ia(stream);
		Pnt2d pt;
		ia >> pt;
		pnt_list.emplace_back(pt);
	}
	std::stringstream stream;
	TNB_oARCH_FILE_TYPE oa(stream);
	oa << pnt_list;
	nlohmann::json jData;
	jData[SENSE] = GetRespType(RespType::good);
	jData[VALUE] = stream.str();
	theStream_ << jData;
}
