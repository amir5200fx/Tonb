#include <GeoIO_Loader_INP.hxx>

#include <GeoIO_INPElement_B31.hxx>
#include <GeoIO_INPElement_CPS3.hxx>
#include <GeoIO_INPPoint.hxx>
#include <IStringStream.hxx>

void tnbLib::GeoIO_Loader_INP::ReadNodes(std::istream& is)
{
	std::string line;
	std::streampos lineStartPos = is.tellg();
	while (std::getline(is, line))
	{
		if (line.empty() OR line.at(0) == '*')
		{
			is.seekg(lineStartPos);
			break;
		}
		lineStartPos = is.tellg();
		
		GeoIO_INPPoint point;
		std::istringstream iss(line);
		if (!(iss >> point))
		{
			FatalErrorIn(FunctionSIG) << endl
				<< "Unable to read the point." << endl
				<< abort(FatalError);
		}
		theCoords_.push_back(std::make_shared<GeoIO_INPPoint>(std::move(point)));
	}
}

std::vector<std::shared_ptr<tnbLib::GeoIO_INPElement>> 
tnbLib::GeoIO_Loader_INP::ReadElements(std::istream& is, const ElmType t)
{
	std::string line;
	std::streampos lineStartPos = is.tellg();
	std::vector<std::shared_ptr<GeoIO_INPElement>> elements;
	while (std::getline(is, line))
	{
		if (line.empty() OR line.at(0) == '*')
		{
			is.seekg(lineStartPos);
			break;
		}
		lineStartPos = is.tellg();
		switch (t)
		{
		case ElmType::B31:
		{
			auto elm = std::make_shared<GeoIO_INPElement_B31>(is);
			elements.push_back(std::move(elm));
			break;
		}
		case ElmType::CPS3:
		{
			auto elm = std::make_shared<GeoIO_INPElement_CPS3>(is);
			elements.push_back(std::move(elm));
			break;
		}
		default:
			FatalErrorIn(FunctionSIG) << endl
				<< "Unspecified type of element has been detected." << endl
				<< abort(FatalError);
			break;
		}
	}
	return std::move(elements);
}

std::vector<Standard_Integer> 
tnbLib::GeoIO_Loader_INP::ReadElementGroup(std::istream& is)
{
	std::string line;
	std::streampos lineStartPos = is.tellg();
	std::vector<Standard_Integer> elements;
	while (std::getline(is, line))
	{
		if (line.empty() OR line.at(0) == '*')
		{
			is.seekg(lineStartPos);
			break;
		}
		lineStartPos = is.tellg();

		Standard_Integer id;
		std::string comma;
		is >> id;
		if (is.fail())
		{
			FatalErrorIn(FunctionSIG)
				<< "Unable to read an integer" << endl
				<< abort(FatalError);
		}
		is >> comma;
		if (is.fail())
		{
			FatalErrorIn(FunctionSIG)
				<< "Unable to read a character" << endl
				<< abort(FatalError);
		}
		elements.push_back(id);
	}
	return std::move(elements);
}

std::vector<std::string> 
tnbLib::GeoIO_Loader_INP::ParseLine(const std::string& theLine)
{
	std::vector<std::string> entities;
	std::stringstream ss(theLine);
	std::string entity;

	while (std::getline(ss, entity, ',')) {
		entities.push_back(entity);
	}

	return entities;
}

std::string 
tnbLib::GeoIO_Loader_INP::ParseElementType(const std::string& theEntity)
{
	std::vector<std::string> entities;
	std::stringstream ss(theEntity);
	std::string entity;

	while (std::getline(ss, entity, '=')) {
		entities.push_back(entity);
	}
	if (entities.size() NOT_EQUAL 2)
	{
		FatalErrorIn(FunctionSIG)
			<< "some thing went wrong" << endl
			<< abort(FatalError);
	}
	return Trim(entities.at(1));
}

std::string 
tnbLib::GeoIO_Loader_INP::ParseElementSet(const std::string& theEntity)
{
	std::vector<std::string> entities;
	std::stringstream ss(theEntity);
	std::string entity;

	while (std::getline(ss, entity, '=')) {
		entities.push_back(entity);
	}
	if (entities.size() NOT_EQUAL 2)
	{
		FatalErrorIn(FunctionSIG)
			<< "some thing went wrong" << endl
			<< abort(FatalError);
	}
	return Trim(entities.at(1));
}

std::string 
tnbLib::GeoIO_Loader_INP::ParseGroupSet(const std::string& theEntity)
{
	std::vector<std::string> entities;
	std::stringstream ss(theEntity);
	std::string entity;

	while (std::getline(ss, entity, '=')) {
		entities.push_back(entity);
	}
	if (entities.size() NOT_EQUAL 2)
	{
		FatalErrorIn(FunctionSIG)
			<< "some thing went wrong" << endl
			<< abort(FatalError);
	}
	return Trim(entities.at(1));
}

std::string 
tnbLib::GeoIO_Loader_INP::Trim(const std::string& str)
{
	// Find the first position of a character that is not a space
	size_t first = str.find_first_not_of(' ');

	// If 'first' is 'std::string::npos', the string contains only spaces
	if (first == std::string::npos) {
		return "";
	}

	// Find the last position of a character that is not a space
	size_t last = str.find_last_not_of(' ');

	// Extract the substring without leading and trailing spaces
	return str.substr(first, last - first + 1);
}

tnbLib::GeoIO_Loader_INP::GeoIO_Loader_INP(std::istream& is)
{
	is >> *this;
}

const std::string tnbLib::GeoIO_Loader_INP::extension = "inpLoader";

std::istream& 
tnbLib::operator>>(std::istream& is, GeoIO_Loader_INP& inp)
{
	{// read the nodes [9/5/2023 aamir]
		std::string line;
		std::getline(is, line);
		auto entities = GeoIO_Loader_INP::ParseLine(line);
		if (GeoIO_Loader_INP::Trim(entities.at(0)) NOT_EQUAL "*NODE")
		{
			inp.ReadNodes(is);
		}
		else
		{
			FatalErrorIn(FunctionSIG)
				<< "Couldn't find node list in the file." << endl
				<< abort(FatalError);
		}
	}
	{// read elements [9/5/2023 aamir]	
		Standard_Boolean isElem = Standard_True;
		while (isElem)
		{
			std::streampos lineStartPos = is.tellg();
			std::string line;
			std::getline(is, line);
			auto entities = GeoIO_Loader_INP::ParseLine(line);
			if (entities.size() NOT_EQUAL 3)
			{
				FatalErrorIn(FunctionSIG)
					<< "invalid header for the element list has been detected." << endl
					<< abort(FatalError);
			}
			if (GeoIO_Loader_INP::Trim(entities.at(0)) IS_EQUAL "*ELEMENT")
			{
				auto elemType = GeoIO_Loader_INP::ParseElementType(entities.at(1));
				if (elemType IS_EQUAL GeoIO_INPElement_B31::typeName_)
				{
					auto elements = inp.ReadElements(is, GeoIO_Loader_INP::ElmType::B31);
					GeoIO_Loader_INP::ElemSet elmSet = 
					{ GeoIO_Loader_INP::ParseElementSet(entities.at(2)), std::move(elements) };
					inp.theElements_.push_back(std::make_shared<GeoIO_Loader_INP::ElemSet>(std::move(elmSet)));
				}
				else if (elemType IS_EQUAL GeoIO_INPElement_CPS3::typeName_)
				{
					auto elements = inp.ReadElements(is, GeoIO_Loader_INP::ElmType::CPS3);
					GeoIO_Loader_INP::ElemSet elmSet =
					{ GeoIO_Loader_INP::ParseElementSet(entities.at(2)), std::move(elements) };
					inp.theElements_.push_back(std::make_shared<GeoIO_Loader_INP::ElemSet>(std::move(elmSet)));
				}
				else
				{
					FatalErrorIn(FunctionSIG)
						<<"Unspecified type of element has been detected."<<endl
						<<abort(FatalError);
				}
				
			}
			else
			{
				is.seekg(lineStartPos);
				isElem = Standard_False;
			}
		}
	}
	{// read the groups [9/5/2023 aamir]
		Standard_Boolean isGroup = Standard_True;
		while (isGroup)
		{
			std::streampos lineStartPos = is.tellg();
			std::string line;
			std::getline(is, line);
			auto entities = GeoIO_Loader_INP::ParseLine(line);
			if (entities.size() NOT_EQUAL 2)
			{
				FatalErrorIn(FunctionSIG)
					<< "invalid header for the element set has been detected." << endl
					<< abort(FatalError);
			}
			if (GeoIO_Loader_INP::Trim(entities.at(0)) IS_EQUAL "*ELSET")
			{
				auto elemSet = GeoIO_Loader_INP::ParseElementSet(entities.at(1));
				auto elements = inp.ReadElementGroup(is);
				GeoIO_Loader_INP::ElemGroup group = { elemSet,std::move(elements) };
				inp.theElemSets_.insert({ elemSet, std::make_shared<GeoIO_Loader_INP::ElemGroup>(std::move(group)) });
			}
		}
	}
	inp.Change_IsDone() = Standard_True;
	return is;
}

TNB_SAVE_IMPLEMENTATION(tnbLib::GeoIO_Loader_INP::ElemSet)
{
	ar& name;
	ar& elements;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::GeoIO_Loader_INP::ElemSet)
{
	ar& name;
	ar& elements;
}

TNB_SAVE_IMPLEMENTATION(tnbLib::GeoIO_Loader_INP::ElemGroup)
{
	ar& name;
	ar& elements;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::GeoIO_Loader_INP::ElemGroup)
{
	ar& name;
	ar& elements;
}

TNB_SAVE_IMPLEMENTATION(tnbLib::GeoIO_Loader_INP)
{
	ar& boost::serialization::base_object<Global_Done>(*this);
	ar& theCoords_;
	ar& theElements_;
	ar& theElemSets_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::GeoIO_Loader_INP)
{
	ar& boost::serialization::base_object<Global_Done>(*this);
	ar& theCoords_;
	ar& theElements_;
	ar& theElemSets_;
}