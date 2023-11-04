#pragma once
#ifndef _Server_Macros_Header
#define _Server_Macros_Header

#define defineTnbServeObject(ObjectName)							\
class ObjectName													\
	: public Server_Object											\
{																	\
public:																\
																	\
	static const std::string command_name;							\
																	\
	ObjectName() = default;											\
																	\
	TnbServer_EXPORT void Construct(const std::string&) override;	\
}


#endif
