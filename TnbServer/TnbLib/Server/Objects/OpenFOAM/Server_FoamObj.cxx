#include <Server_FoamObj.hxx>

#include <TnbError.hxx>
#include <OSstream.hxx>
#include <IOobject.hxx>
#include <dictionaryListEntry.hxx>
#include <dictionary.hxx>
#include <IStringStream.hxx>
#include <Global_Serialization.hxx>

#include <json.hpp>

namespace tnbLib
{
	static const std::string HEADER = "header";
	static const std::string BODY = "body";

	static const std::string FOAM_FILE = "FoamFile";

	static const std::string DIMENSIONS = "dimensions";
	static const std::string INTERNAL_FIELD = "internalField";
	static const std::string BOUNDARY_FILED = "boundaryField";
}

implementTnbServerConstruction(Server_FoamObj_LoadInitCs)
{
	try
	{
		IStringStream iss(theValue);
		dictionary dict;
		dict.read(iss, true);

		nlohmann::json jData;
		OStringStream fstream;
		{
			//IOobject::writeBanner(fstream);
			auto sub = dict.subDict(FOAM_FILE);
			//fstream << FOAM_FILE;
			sub.write(fstream);
			dict.remove(FOAM_FILE);
			//IOobject::writeDivider(fstream);
		}
		{
			auto& dimens = dict.lookup(DIMENSIONS);
			std::string l;
			l.append("[");
			for(const auto& i: dimens)
			{
				if (i.isLabel())
				{
					l.append(std::to_string(i.labelToken()));
					l.append(" ");
				}
			}
			l.at(l.size() - 1) = ']';
			jData[DIMENSIONS] = l;
		}
		{
			auto& field = dict.lookup(INTERNAL_FIELD);
			std::string l;
			for(const auto& i: field)
			{
				if (i.isString())
				{
					l.append(i.stringToken());
					l.append(" ");
				}
				if (i.isWord())
				{
					l.append(i.wordToken());
					l.append(" ");
				}
				if (i.isLabel())
				{
					l.append(std::to_string(i.labelToken()));
					l.append(" ");
				}
				if (i.isFloatScalar())
				{
					l.append(std::to_string(i.isFloatScalar()));
					l.append(" ");
				}
				if (i.isDoubleScalar())
				{
					l.append(std::to_string(i.doubleScalarToken()));
					l.append(" ");
				}
				if (i.isLongDoubleScalar())
				{
					l.append(std::to_string(i.longDoubleScalarToken()));
					l.append(" ");
				}
			}
			l.erase(l.size() - 1);
			jData[INTERNAL_FIELD] = l;
		}
		{
			auto bnds = dict.subDict(BOUNDARY_FILED);
			auto& j0 = jData[BOUNDARY_FILED];
			for (const auto& b: bnds)
			{
				auto sub = bnds.subDict(b.keyword());
				auto& j1 = j0[b.keyword()];
				for (const auto& e: sub)
				{
					auto it = sub.lookup(e.keyword());
					//auto& j2 = j1[e.keyword()];
					std::vector<std::string> l;
					for (auto t: it)
					{
						switch (t.type())
						{
						case token::UNDEFINED:
						case token::PUNCTUATION:
						case token::COMPOUND:
							FatalErrorIn(FunctionSIG) << endl
								<< "Undefined token." << endl
								<< abort(FatalError);
							break;
						case token::WORD:
							l.emplace_back(t.wordToken());
							break;
						case token::STRING:
						case token::VERBATIMSTRING:
							l.emplace_back(t.stringToken());
							break;
						case token::VARIABLE:
							break;

						case token::LABEL:
							l.emplace_back(std::to_string(t.labelToken()));
							break;
						case token::FLOAT_SCALAR:
							l.emplace_back(std::to_string(t.floatScalarToken()));
							break;
						case token::DOUBLE_SCALAR:
							l.emplace_back(std::to_string(t.doubleScalarToken()));
							break;
						case token::LONG_DOUBLE_SCALAR:
							l.emplace_back(std::to_string(t.longDoubleScalarToken()));
							break;
					
						case token::ERROR:
							FatalErrorIn(FunctionSIG) << endl
								<< "Undefined token." << endl
								<< abort(FatalError);
							break;

						
						}
					}
					{
						std::stringstream ss;
						for (size_t i = 0; i < l.size() - 1; i++)
						{
							ss << l.at(i) << " ";
						}
						ss << l.at(l.size() - 1);
						j1[e.keyword()] = ss.str();
					}
				}
			}
		}
		//std::cout << jData << std::endl;
		nlohmann::json tot_j;
		tot_j[HEADER] = fstream.str();
		{
			std::stringstream ss;
			ss << jData;
			tot_j[BODY] = ss.str();
		}
		std::stringstream stream_j;
		stream_j << tot_j;
		nlohmann::json jData1;
		jData1[SENSE] = GetRespType(RespType::good);
		jData1[VALUE] = stream_j.str();
		theStream_ << jData1;
	}
	catchTnbServerErrors()
	
}

implementTnbServerConstruction(Server_FoamObj_LoadBcs)
{
	try
	{
		IStringStream iss(theValue);
		dictionary dict;
		dict.read(iss, true);

		nlohmann::json jData;
		OStringStream fstream;
		{
			//IOobject::writeBanner(fstream);
			auto sub = dict.subDict("FoamFile");
			//fstream << "FoamFile";
			sub.write(fstream);
			dict.remove("FoamFile");
			//IOobject::writeDivider(fstream);
		}
		nlohmann::json tot_j;
		tot_j["header"] = fstream.str();
		const auto& entry = dict.lookupEntry("entry0", false, true);
		{
			if (!entry.isDict())
			{
				FatalErrorIn(FunctionSIG) << endl
					<< "Something went wrong. It's not an entry object!" << endl
					<< abort(FatalError);
			}
			auto bnds = entry.dict();
			for (const auto& b: bnds)
			{
				auto sub = bnds.subDict(b.keyword());
				auto& j0 = jData[b.keyword()];
				for (const auto& e : sub)
				{
					auto it = sub.lookup(e.keyword());
					if (it.size() != 1)
					{
						FatalErrorIn(FunctionSIG) << endl
							<< "Error in reading the boundary condition file." << endl
							<< abort(FatalError);
					}
					auto t = it[0];
					if (t.isWord())
					{
						j0[e.keyword()] = t.wordToken();
					}
					if (t.isString())
					{
						j0[e.keyword()] = t.isString();
					}
					if (t.isLabel())
					{
						j0[e.keyword()] = t.labelToken();
					}
				}
			}
		}
		{
			std::stringstream ss;
			ss << jData;
			tot_j["body"] = ss.str();
		}
		std::stringstream stream_j;
		stream_j << tot_j;
		nlohmann::json jData1;
		jData1[SENSE] = GetRespType(RespType::good);
		jData1[VALUE] = stream_j.str();
		theStream_ << jData1;
	}
	catchTnbServerErrors()
}

implementTnbServerConstruction(Server_FoamObj_WriteInitCs)
{
	try
	{
		std::stringstream os;
		{ // writing the baner
			OStringStream fstream;
			//IOobject::writeBanner(fstream);
			//os << fstream.str();
		}
		nlohmann::json jData = nlohmann::json::parse(theValue);
		auto header = jData[HEADER].get<std::string>();
		//std::cout << header << std::endl;
		
		//os << FOAM_FILE;
		os << header;
		{// writing the divider
			OStringStream fstream;
			//IOobject::writeDivider(fstream);
			os << fstream.str();
		}
		
		{// get the body part
			nlohmann::json body_j = jData[BODY];
			//dictionary dict;
			//dict.add(word(DIMENSIONS), word(body_j[DIMENSIONS].get<std::string>()));
			//dict.add(word(INTERNAL_FIELD), word(body_j[INTERNAL_FIELD].get<std::string>()));
			dictionary boundaries;
			{// boundaries
				
				for (const auto& b: body_j[BOUNDARY_FILED].items())
				{
					dictionary items;
					for(const auto& i: b.value().items())
					{
						items.add(word(i.key().c_str()), word(i.value().get<std::string>()));
					}
					boundaries.add(word(b.key().c_str()), items);
				}
				//dict.add(word(BOUNDARY_FILED), boundaries);
			}
			os << BOUNDARY_FILED;
			//Info << dict << endl;
			OStringStream fstream;
			fstream << boundaries;
			/*for(const auto& ent: dict)
			{
				fstream << ent << endl;
				fstream << endl;
			}*/
			{ // writing the divider
				IOobject::writeEndDivider(fstream);
			}
			//std::cout << fstream.str() << std::endl;
			os << fstream.str();
			nlohmann::json jData1;
			jData1[SENSE] = GetRespType(RespType::good);
			jData1[VALUE] = os.str();
			theStream_ << jData1;
		}
	}
	catchTnbServerErrors()
}

implementTnbServerConstruction(Server_FoamObj_WriteBcs)
{
	try
	{
		std::stringstream os;
		{ // writing the baner
			OStringStream fstream;
			IOobject::writeBanner(fstream);
			os << fstream.str();
		}
		nlohmann::json jData = nlohmann::json::parse(theValue);
		auto header = jData[HEADER].get<std::string>();
		os << FOAM_FILE;
		os << header;
		{// writing the divider
			OStringStream fstream;
			IOobject::writeDivider(fstream);
			os << fstream.str();
		}
		//std::cout << os.str() << std::endl;
		List<word> dicts;
		{// get the body part
			nlohmann::json body_j = jData[BODY];
			{// boundaries
				dictionary boundaries;
				for(const auto& b: body_j.items())
				{
					
					dictionary items;
					for (const auto& i : b.value().items())
					{
						if (i.value().is_number_integer())
						{
							items.add(word(i.key().c_str()), label(i.value().get<int>()));
						}
						if (i.value().is_string())
						{
							items.add(word(i.key().c_str()), word(i.value().get<std::string>()));
						}
					}
					boundaries.add(word(b.key().c_str()), items);
					
				}
				
				for(const auto& x: boundaries)
				{
					OStringStream fstream;
					fstream << x.keyword();
					fstream << x.dict();
					auto s = std::string(fstream.str());
					s.erase(s.size() - 1);
					dicts.append(word(s));
				}
				//Info << dicts << endl;
			}
		}
		{
			OStringStream fstream;
			fstream << dicts;
			{ // writing the divider
				IOobject::writeEndDivider(fstream);
			}
			os << fstream.str();
		}
		nlohmann::json jData1;
		jData1[SENSE] = GetRespType(RespType::good);
		jData1[VALUE] = os.str();
		theStream_ << jData1;
	}
	catchTnbServerErrors()
}