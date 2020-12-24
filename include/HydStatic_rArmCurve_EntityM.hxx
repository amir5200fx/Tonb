#pragma once
#ifndef _HydStatic_rArmCurve_EntityM_Header
#define _HydStatic_rArmCurve_EntityM_Header

#define R_ARMCURVE_ENTITYM(CLASS_NAME, PRIM_TYPE)								\
	class CLASS_NAME															\
		: public HydStatic_Entity												\
	{																			\
		typedef rArmCurve_Cmpt<PRIM_TYPE> cmptCurve;							\
		/*Private Data*/														\
																				\
		std::shared_ptr<cmptCurve> theCmpt_;									\
																				\
	public:																		\
																				\
		CLASS_NAME() {}															\
																				\
		CLASS_NAME(const std::shared_ptr<cmptCurve>&& theCmpt)					\
			: theCmpt_(std::move(theCmpt))										\
		{}																		\
																				\
		CLASS_NAME(const Standard_Integer theIndex)								\
			: HydStatic_Entity(theIndex)										\
		{}																		\
																				\
		CLASS_NAME(const Standard_Integer theIndex, const word& theName)		\
			: HydStatic_Entity(theIndex, theName)								\
		{}																		\
																				\
		const auto& Cmpt() const												\
		{																		\
			return theCmpt_;													\
		}																		\
																				\
		auto& ChangeCmpt()														\
		{																		\
			return theCmpt_;													\
		}																		\
																				\
		void SetCmpt(const std::shared_ptr<cmptCurve>&& theCmpt)				\
		{																		\
			theCmpt_ = std::move(theCmpt);										\
		}																		\
	};

#endif // !_HydStatic_rArmCurve_EntityM_Header
