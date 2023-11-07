#pragma once
#ifndef _Server_Macros_Header
#define _Server_Macros_Header

#include <sstream>

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
	void Server::FuncName(const std::string& theValue)						\
	{																		\
		theObj_ = std::make_shared<Object>();								\
		theObj_->Construct(theValue);										\
	}

#define streamBadTnbServerObject(MSG)										\
	nlohmann::json jData;													\
	jData[SENSE] = GetRespType(RespType::bad);								\
	jData[VALUE] = MSG;								\
	theStream_ << jData

#define switchToMakeTnbServerObject(ObjType, FuncName, String)				\
	case ObjType:															\
	{																		\
		FuncName(String);													\
		break;																\
	}

#define streamUnknownBadTnbServerObject()									\
	catch(...) {streamBadTnbServerObject("Unknown Error has been occured");}

#endif
