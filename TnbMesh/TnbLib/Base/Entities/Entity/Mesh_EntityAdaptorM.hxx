#pragma once
#ifndef _Mesh_EntityAdaptorM_Header
#define _Mesh_EntityAdaptorM_Header

#include <Global_Serialization.hxx>
#include <Global_TypeDef.hxx>

#include <map>
#include <memory>

#define Mesh_EntityToEntityAdaptor(EntityName, toEntityName, EntityType)																	\
	template<class EntityType>																												\
	class Mesh_##EntityName##To##toEntityName##Adaptor																						\
	{																																		\
																																			\
		/*Private Data*/																													\
																																			\
		std::map<Standard_Integer, std::weak_ptr<EntityType>> the##toEntityName##s_;														\
																																			\
																																			\
		TNB_SERIALIZATION(MESH_MODULE)																										\
																																			\
																																			\
																																			\
	public:																																	\
																																			\
		Mesh_##EntityName##To##toEntityName##Adaptor()																						\
		{}																																	\
																																			\
		Standard_Integer Nb##toEntityName##s() const																						\
		{																																	\
			return (Standard_Integer)the##toEntityName##s_.size();																			\
		}																																	\
																																			\
																																			\
		/*Standard_Boolean InsertTo##toEntityName##s(const Standard_Integer theIndex, const std::weak_ptr<EntityType>& theEntity)			\
		{																																	\
			auto insert = the##toEntityName##s_.insert(std::make_pair(theIndex, theEntity));												\
			return (Standard_Boolean)!insert.second;																						\																															\
		}*/																																	\
																																			\
																																			\
		Standard_Boolean RemoveFrom##toEntityName##s(const Standard_Integer theIndex)														\
		{																																	\
			auto iter = the##toEntityName##s_.find(theIndex);																				\
			if (iter == the##toEntityName##s_.end())																						\
			{																																\
				return Standard_True;																										\
			}																																\
			the##toEntityName##s_.erase(iter);																								\
			return Standard_False;																											\
		}																																	\
																																			\
		Standard_Boolean IsOn##toEntityName##s(const Standard_Integer theIndex) const														\
		{																																	\
			auto iter = the##toEntityName##s_.find(theIndex);																				\
			if (iter == the##toEntityName##s_.end())																						\
			{																																\
				return Standard_False;																										\
			}																																\
			return Standard_True;																											\
		}																																	\
																																			\
		const std::map<Standard_Integer, std::weak_ptr<EntityType>>& Retrieve##toEntityName##s() const										\
		{																																	\
			return the##toEntityName##s_;																									\
		}																																	\
																																			\
		void Clear##toEntityName##s()																										\
		{																																	\
			the##toEntityName##s_.clear();																									\
		}																																	\
																																			\
Standard_Boolean InsertTo##toEntityName##s(const Standard_Integer theIndex, const std::weak_ptr<EntityType>& theEntity) \
{auto insert = the##toEntityName##s_.insert(std::make_pair(theIndex, theEntity)); return (Standard_Boolean)!insert.second;}\
	}

#endif // !_Mesh_EntityAdaptorM_Header