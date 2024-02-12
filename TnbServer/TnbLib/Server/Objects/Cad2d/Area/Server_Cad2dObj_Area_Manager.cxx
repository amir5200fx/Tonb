#include <Server_Cad2dObj_Area_Manager.hxx>

#include <Cad2d_Plane.hxx>
#include <Pln_Edge.hxx>
#include <Cad_EntityManager.hxx>
#include <Cad_BlockEntity.hxx>

#include <json.hpp>

void tnbLib::Server_Cad2dObj_Area_Manager_Segments::Construct(const std::string& theValue)
{
	std::shared_ptr<Cad2d_Plane> shape;
	std::stringstream stream;
	stream << theValue;
	TNB_iARCH_FILE_TYPE ia(stream);
	ia >> shape;
	{
		const auto& manager = shape->Segments();
		const auto& blocks = manager->Blocks();
		std::stringstream array_stream;
		std::vector<std::string> block_list;
		{
			//nlohmann::json jData;
			
			//int i = 0;
			for (const auto& b : blocks)
			{
				block_list.emplace_back(b.second->Name());
				//jData[std::to_string(i++)] = b.second->Name();
			}
			
			//array_stream << jData;
		}
		/*std::stringstream block_stream;
		{
			nlohmann::json jData;
			jData["size"] = blocks.size();
			jData["ents"] = block_list;
			block_stream << jData;
		}*/
		{
			nlohmann::json jData;
			jData[SENSE] = GetRespType(RespType::good);
			jData[VALUE] = block_list;
			theStream_ << jData;
			//theStream_ << block_stream.str();
		}
	}
}

const std::string tnbLib::Server_Cad2dObj_Area_Manager_Segments_CombineBlocks::Params::blocks("blocks");
const std::string tnbLib::Server_Cad2dObj_Area_Manager_Segments_CombineBlocks::Params::area("area");
const std::string tnbLib::Server_Cad2dObj_Area_Manager_Segments_CombineBlocks::Params::new_name("new_name");

void tnbLib::Server_Cad2dObj_Area_Manager_Segments_CombineBlocks::Construct(const std::string& theValue)
{
	std::shared_ptr<Cad2d_Plane> area;
	std::vector<std::string> blocks;
	std::string new_name;
	{
		defineTnbServerParser(theValue);
		{
			loadTnbServerObject(area);
		}
		{
			//loadTnbServerObject(blocks);
			{
				// Parse the JSON string
				nlohmann::json json_array = nlohmann::json::parse(loader.at(Params::blocks).get<std::string>());

				// Check if the parsed JSON is an array
				if (json_array.is_array()) {
					// Access elements of the array
					for (const auto& element : json_array) {
						blocks.emplace_back(element.get<std::string>());
					}
				}
				else {
					throw Server_Error("Couldn't load the ids");
				}
			}
		}
		{
			new_name = loader.at(Params::new_name).get<std::string>();
		}
	}
	const auto& manager = area->Segments();
	try
	{
		std::vector<std::map<word, std::shared_ptr<Cad_BlockEntity<Pln_Edge>>>::const_iterator> block_iters;
		for (const auto& x: blocks)
		{
			block_iters.emplace_back(manager->SelectBlock(x));
		}
		manager->CombineBlocks(block_iters, new_name);
		streamGoodTnbServerObject(area);
	}
	catchTnbServerErrors()
}

implementTnbServerParam(Server_Cad2dObj_Area_Manager_CombineAll, area, "area");
implementTnbServerParam(Server_Cad2dObj_Area_Manager_CombineAll, name, "name");

implementTnbServerConstruction(Server_Cad2dObj_Area_Manager_CombineAll)
{
	std::shared_ptr<Cad2d_Plane> area;
	std::string name;
	{
		defineTnbServerParser(theValue);
		{
			loadTnbServerObject(area);
		}
		{
			loadTnbServerString(name);
		}
	}
	try
	{
		if (!area)
		{
			throw Server_Error("the area object is null.");
		}
		if (area->Segments()->NbBlocks() == 1)
		{
			auto manager = area->Segments();
			auto block = manager->Blocks().begin()->first;
			auto iter = manager->SelectBlock(block);
			if (iter == manager->Blocks().end())
			{
				std::string msg = "the block isn't found. block's name = " + block;
				throw Server_Error(msg);
			}
			manager->ReNameBlock(iter, name);
		}
		else
		{
			auto manager = area->Segments();
			const auto& blocks = manager->Blocks();
			std::vector<std::map<word, std::shared_ptr<Cad_BlockEntity<Pln_Edge>>>::const_iterator> iters;
			for (const auto& x: blocks)
			{
				iters.emplace_back(manager->SelectBlock(x.first));
			}
			manager->CombineBlocks(iters, name);
		}
		streamGoodTnbServerObject(area);
	}
	catchTnbServerErrors()
}

const std::string tnbLib::Server_Cad2dObj_Area_Manager_Segments_BlockCurves::Params::block_name("block_name");
const std::string tnbLib::Server_Cad2dObj_Area_Manager_Segments_BlockCurves::Params::area("area");

void tnbLib::Server_Cad2dObj_Area_Manager_Segments_BlockCurves::Construct(const std::string& theValue)
{
	std::shared_ptr<Cad2d_Plane> area;
	std::string block_name;
	{
		defineTnbServerParser(theValue);
		{
			loadTnbServerObject(area);
		}
		{
			block_name = loader.at(Params::block_name).get<std::string>();
		}
	}
	const auto& manager = area->Segments();
	try
	{
		auto iter = manager->SelectBlock(block_name);
		if (iter == manager->Blocks().end())
		{
			std::string msg = "the block isn't found. block's name = " + block_name;
			throw Server_Error(msg);
		}
		auto block = iter->second;
		auto keys = block->RetrieveKeys();
		{
			nlohmann::json jData;
			jData[SENSE] = GetRespType(RespType::good);
			jData[VALUE] = keys;
			theStream_ << jData;
		}
	}
	catchTnbServerErrors()
}

const std::string tnbLib::Server_Cad2dObj_Area_Manager_Segments_SplitBlock::Params::curve_ids("curve_ids");
const std::string tnbLib::Server_Cad2dObj_Area_Manager_Segments_SplitBlock::Params::new_name("new_name");
const std::string tnbLib::Server_Cad2dObj_Area_Manager_Segments_SplitBlock::Params::block_name("block_name");
const std::string tnbLib::Server_Cad2dObj_Area_Manager_Segments_SplitBlock::Params::area("area");

void tnbLib::Server_Cad2dObj_Area_Manager_Segments_SplitBlock::Construct(const std::string& theValue)
{
	std::vector<int> curve_ids;
	std::string new_name;
	std::string block_name;
	std::shared_ptr<Cad2d_Plane> area;
	{
		defineTnbServerParser(theValue);
		{
			loadTnbServerObject(area);
		}
		{
			{
				// Parse the JSON string
				nlohmann::json json_array = nlohmann::json::parse(loader.at(Params::curve_ids).get<std::string>());

				// Check if the parsed JSON is an array
				if (json_array.is_array()) {
					// Access elements of the array
					for (const auto& element : json_array) {
						curve_ids.emplace_back(element.get<int>());
					}
				}
				else {
					throw Server_Error("Couldn't load the ids");
				}
			}
			/*if (loader.at(Params::curve_ids).is_array())
			{
				for (const auto& x: loader.at(Params::curve_ids))
				{
					curve_ids.emplace_back(x.get<int>());
				}
			}*/
		}
		{
			block_name = loader.at(Params::block_name).get<std::string>();
		}
		{
			new_name = loader.at(Params::new_name).get<std::string>();
		}
	}
	//std::exit(1);
	const auto& manager = area->Segments();
	try
	{
		auto iter = manager->SelectBlock(block_name);
		if (iter == manager->Blocks().end())
		{
			std::string msg = "the block isn't found. block's name = " + block_name;
			throw Server_Error(msg);
		}
		auto block = iter->second;
		/*std::vector<int> ids;
		for (const auto& x: curve_ids)
		{
			ids.emplace_back(std::stoi(x));
		}*/
		//std::cout << "new name: " << new_name << std::endl;
		auto new_block = block->Split(new_name, curve_ids);
		manager->Import(new_name, new_block);
		streamGoodTnbServerObject(area);
	}
	catchTnbServerErrors()
}

const std::string tnbLib::Server_Cad2dObj_Area_Manager_Segments_RenameBlock::Params::area("area");
const std::string tnbLib::Server_Cad2dObj_Area_Manager_Segments_RenameBlock::Params::block_name("block_name");
const std::string tnbLib::Server_Cad2dObj_Area_Manager_Segments_RenameBlock::Params::new_name("new_name");

void tnbLib::Server_Cad2dObj_Area_Manager_Segments_RenameBlock::Construct(const std::string& theValue)
{
	std::string new_name;
	std::string block_name;
	std::shared_ptr<Cad2d_Plane> area;
	{
		defineTnbServerParser(theValue);
		{
			loadTnbServerObject(area);
		}
		{
			block_name = loader.at(Params::block_name).get<std::string>();
		}
		{
			new_name = loader.at(Params::new_name).get<std::string>();
		}
	}
	const auto& manager = area->Segments();
	try
	{
		auto iter = manager->SelectBlock(block_name);
		if (iter == manager->Blocks().end())
		{
			std::string msg = "the block isn't found. block's name = " + block_name;
			throw Server_Error(msg);
		}
		manager->ReNameBlock(iter, new_name);
		streamGoodTnbServerObject(area);
	}
	catchTnbServerErrors()
}
