#pragma once
#ifndef _Server_Macros_Header
#define _Server_Macros_Header

#include <Server_Error.hxx>
#include <sstream>

#include <StdFail_NotDone.hxx>

#define defineTnbServerObject(ObjectName)									\
class ObjectName															\
	: public Server_Object													\
{																			\
public:																		\
																			\
	static const std::string command_name;									\
																			\
	ObjectName() = default;													\
																			\
	TnbServer_EXPORT void Construct(const std::string&) override;			\
}

#define loadTnbServerObject(ObjectName)										\
	std::stringstream stream;												\
	stream << loader.at(Params::ObjectName).get<std::string>();				\
	TNB_iARCH_FILE_TYPE ia(stream);											\
	ia >> ObjectName

#define loadTnbServerString(ObjectName)										\
	ObjectName = loader.at(Params::ObjectName).get<std::string>()

#define loadNonJSONTnbServer(ObjectName)									\
	std::stringstream stream;												\
	stream << theValue;														\
	TNB_iARCH_FILE_TYPE ia(stream);											\
	ia >> ObjectName;
	

#define defineTnbServerParser(String)										\
	nlohmann::json loader = nlohmann::json::parse(String)

#define streamGoodTnbServerObject(Object)									\
	std::stringstream stream;												\
	TNB_oARCH_FILE_TYPE oa(stream);											\
	oa << (Object);															\
	nlohmann::json jData;													\
	jData[SENSE] = GetRespType(RespType::good);								\
	jData[VALUE] = stream.str();											\
	theStream_ << jData

#define streamRealValueTnbServerObject(value)								\
	std::stringstream stream;												\
	nlohmann::json jData;													\
	jData[SENSE] = GetRespType(RespType::good);								\
	jData[VALUE] = value;													\
	theStream_ << jData

#define streamWarningTnbServerObject(Object, MSG)							\
	std::stringstream stream;												\
	TNB_oARCH_FILE_TYPE oa(stream);											\
	oa << (Object);															\
	nlohmann::json jData;													\
	jData[SENSE] = GetRespType(RespType::warning);							\
	jData[SERVER_MSG] = MSG;												\
	jData[VALUE] = stream.str();											\
	theStream_ << jData

#define serializedTnbObject(STR, Obj)										\
	std::stringstream stream_s;												\
	TNB_oARCH_FILE_TYPE oa(stream_s);										\
	oa << (Obj);															\
	STR = stream_s.str()

#define serializedTnbObjectAtJSON(Obj, ObjName, JSON)						\
{																			\
	std::string str;														\
	serializedTnbObject(str, Obj);											\
	(JSON)[ObjName] = str;													\
}

#define initTnbCommands(Object, Command)									\
	const std::string tnbLib::Object::command_name = Command

#define defineRuntimeSelectTnbServerObject(Object, Server_ObjType)			\
class Object##_RunTime_Selection											\
{																			\
	static void Run();														\
																			\
public:																		\
																			\
	Object##_RunTime_Selection()											\
	{																		\
		Run();																\
	}																		\
};																			\
																			\
void Object##_RunTime_Selection::Run()										\
{																			\
	Server::Commands.insert({Object::command_name, Server_ObjType});		\
}

#define registerRuntimeSelectTnbServerObject(Object)						\
	static const Object##_RunTime_Selection Object##_run_time_selection_Obj

#define defineAndRegisterTnbServerObject(Object, Server_ObjType, Command)	\
	initTnbCommands(Object, Command);										\
	defineRuntimeSelectTnbServerObject(Object, Server_ObjType);				\
	registerRuntimeSelectTnbServerObject(Object)

#define createTnbServerObject(FuncName, Object)								\
	void Server::FuncName(const std::string& theValue, const std::string& theSense)		\
	{																					\
		if (theSense == "no")															\
		{																				\
			theObj_ = std::make_shared<Object>();										\
			theObj_->Construct(theValue);												\
		}																				\
		else																			\
		{																				\
			theObj_ = std::make_shared<Object>();										\
			theObj_->MakeEmpty();														\
		}																				\
																						\
	}

#define streamBadTnbServerObject(MSG)										\
	nlohmann::json jData;													\
	jData[SENSE] = GetRespType(RespType::bad);								\
	jData[VALUE] = MSG;														\
	theStream_ << jData

#define switchToMakeTnbServerObject(ObjType, FuncName, String, Sense)		\
	case ObjType:															\
	{																		\
		FuncName(String, Sense);													\
		break;																\
	}

#define streamUnknownBadTnbServerObject()									\
	catch(...) {streamBadTnbServerObject("Unknown Error has been occured");}

#define catchTnbServerErrors()												\
catch (error& x)															\
{																			\
	streamBadTnbServerObject(x.message());									\
}																			\
catch (Standard_Failure& x)													\
{																			\
	streamBadTnbServerObject(x.GetMessageString());							\
}																			\
catch (Server_Error& x)														\
{																			\
	streamBadTnbServerObject(x.what());										\
}																			\
catch (StdFail_NotDone& x)													\
{																			\
	streamBadTnbServerObject(x.GetMessageString());							\
}																			\
streamUnknownBadTnbServerObject()

#define declareTnbServerFunction(NAME)										\
void NAME(const std::string&, const std::string&)

#endif
