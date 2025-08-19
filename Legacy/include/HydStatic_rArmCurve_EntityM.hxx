#pragma once
#ifndef _HydStatic_rArmCurve_EntityM_Header
#define _HydStatic_rArmCurve_EntityM_Header

#include <HydStatic_rArmCurve.hxx>

#define R_ARMCURVE_ENTITYM(CLASS_NAME, PRIM_TYPE)																												\
	class CLASS_NAME																																			\
		: public HydStatic_rArmCurve																															\
	{																																							\
		typedef rArmCurve_Cmpt<PRIM_TYPE> cmptCurve;																											\
		/*Private Data*/																																		\
																																								\
		std::shared_ptr<cmptCurve> theCmpt_;																													\
																																								\
																																								\
																																								\
		/*private functions and operators*/																														\
																																								\
		TNB_SERIALIZATION(TnbHydStatic_EXPORT);																													\
																																								\
																																								\
		/*default constructor*/																																	\
		CLASS_NAME() {}																																			\
																																								\
	public:																																						\
																																								\
																																								\
		CLASS_NAME(const Handle(Geom2d_Curve)& theCurve, std::shared_ptr<cmptCurve>&& theCmpt)																	\
			: HydStatic_rArmCurve(theCurve)																														\
			, theCmpt_(std::move(theCmpt))																														\
		{}																																						\
																																								\
																																								\
		CLASS_NAME(const Standard_Integer theIndex, const word& theName, const Handle(Geom2d_Curve)& theCurve, std::shared_ptr<cmptCurve>&& theCmpt)			\
			: HydStatic_rArmCurve(theIndex, theName, theCurve)																									\
			, theCmpt_(std::move(theCmpt))																														\
		{}																																						\
																																								\
		const auto& Cmpt() const																																\
		{																																						\
			return theCmpt_;																																	\
		}																																						\
																																								\
		auto& ChangeCmpt()																																		\
		{																																						\
			return theCmpt_;																																	\
		}																																						\
																																								\
		void SetCmpt(const std::shared_ptr<cmptCurve>&& theCmpt)																								\
		{																																						\
			theCmpt_ = std::move(theCmpt);																														\
		}																																						\
																																								\
		std::shared_ptr<HydStatic_rArmCurve> ExpandToPort() const override;																						\
																																								\
	};

#endif // !_HydStatic_rArmCurve_EntityM_Header
