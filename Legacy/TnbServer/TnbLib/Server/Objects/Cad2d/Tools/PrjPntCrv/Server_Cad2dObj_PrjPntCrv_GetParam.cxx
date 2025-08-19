#include <Server_Cad2dObj_PrjPntCrv_GetParam.hxx>

#include <json.hpp>

void tnbLib::Server_Cad2dObj_PrjPntCrv_GetParam::Construct(const std::string& theValue)
{
	double value;
	{
		std::stringstream stream;
		stream << theValue;
		TNB_iARCH_FILE_TYPE ia(stream);
		std::shared_ptr<Server_Cad2dObj_PrjPntCrv::Values> values;
		ia >> values;
		value = values->u;
	}
	streamGoodTnbServerObject(value);
}
