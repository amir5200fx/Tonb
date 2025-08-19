#include <Server_Cad2dObj_Curve_List.hxx>

#include <Pln_Edge.hxx>
#include <json.hpp>

void tnbLib::Server_Cad2dObj_Curve_List::Construct(const std::string& theValue)
{
	std::vector<std::shared_ptr<Pln_Edge>> curves;
	defineTnbServerParser(theValue);
	for (const auto& x:loader)
	{
		std::stringstream stream;
		stream << x.get<std::string>();
		TNB_iARCH_FILE_TYPE ia(stream);
		std::shared_ptr<Pln_Edge> edge;
		ia >> edge;
		curves.emplace_back(edge);
	}
	std::stringstream stream;
	TNB_oARCH_FILE_TYPE oa(stream);
	oa << curves;
	nlohmann::json jData;
	jData[SENSE] = GetRespType(RespType::good);
	jData[VALUE] = stream.str();
	theStream_ << jData;
}
