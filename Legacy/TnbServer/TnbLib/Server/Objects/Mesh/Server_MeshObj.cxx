#include <Server_MeshObj.hxx>

#include <Geo3d_FVMesh.hxx>
#include <MeshPost_IdeasUNV.hxx>

#include <json.hpp>

implementTnbServerConstruction(Server_MeshObj_ExportFvToUNV)
{
	std::shared_ptr<Geo3d_FVMesh> fv;
	{
		loadNonJSONTnbServer(fv);
	}
	try
	{
		if (!fv)
		{
			throw Server_Error("the fv object is null.");
		}
		auto convertor = std::make_shared<MeshPost_IdeasUNV>();
		convertor->SetMesh(fv);
		std::stringstream stream;
		convertor->Perform(stream);
		nlohmann::json jData;
		jData[SENSE] = GetRespType(RespType::good);
		jData[VALUE] = stream.str();
		theStream_ << jData;
	}
	catchTnbServerErrors()
}