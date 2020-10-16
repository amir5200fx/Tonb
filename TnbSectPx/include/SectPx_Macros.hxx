#pragma once
#ifndef _SectPx_Macros_Header
#define _SectPx_Macros_Header

#define AddParameterToParent(PAR, INPPAR, FuncName)							\
{																			\
	auto par = PAR.lock();													\
	if(par)																	\
	{																		\
		RemoveThisFromChild(par);											\
	}																		\
																			\
	PAR=INPPAR;																\
																			\
	if(INPPAR AND INPPAR->InCycle())										\
	{																		\
		FatalErrorIn(FuncName)												\
			<< "the parameter is just taken into a cycle!" << endl			\
			<< abort(FatalError);											\
	}																		\
	AddThisToChild(INPPAR);													\
}

#define AddThisParentToChild(PAR)									\
{																	\
	auto parent = std::dynamic_pointer_cast<SectPx_Parent>(This());	\
	Debug_Null_Pointer(parent);										\
																	\
	if (PAR)														\
	{																\
		SectPx_ParTools::AddParentToChild(parent, PAR);				\
	}																\
}

#define RemoveThisParentFromChild(PAR)								\
{																	\
	auto parent = std::dynamic_pointer_cast<SectPx_Parent>(This());	\
	Debug_Null_Pointer(parent);										\
																	\
	if (PAR)														\
	{																\
		SectPx_ParTools::RemoveParentFromChild(parent, PAR);		\
	}																\
}

#define AddThisParentToChildren(PAR)									\
{																		\
	auto par = PAR.lock();												\
	if(par)																\
	{																	\
		auto parent = std::dynamic_pointer_cast<SectPx_Parent>(This());	\
		Debug_Null_Pointer(parent);										\
																		\
		SectPx_ParTools::AddParentToChild(parent, par);					\
	}																	\
}

#define ReturnFalseIfNull(PAR)			\
{										\
	const auto par = PAR.lock();		\
	if(NOT par) return Standard_False;	\
}

#define ReturnTrueIfParBelongsToThisParent(PAR,INPPAR)		\
{															\
	const auto par = PAR.lock();							\
	return (Standard_Boolean)(par IS_EQUAL INPPAR);			\
}

#define DefineChildList(LIST) \
	std::vector<std::shared_ptr<SectPx_Child>> LIST

#define AddParToChildList(PAR, LIST)						\
	{														\
		auto par = PAR.lock();								\
		if(par) LIST.push_back(std::move(par));				\
	}


#endif // !_SectPx_Macros_Header
