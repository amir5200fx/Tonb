#pragma once
#ifndef _Global_Tools_Header
#define _Global_Tools_Header

#include <Global_Module.hxx>

#include <Standard_TypeDef.hxx>

#include <memory>
#include <vector>
#include <map>

namespace tnbLib
{

	// Forward Declarations [1/11/2022 Amir]
	class Global_Table;

	class Global_Tools
	{

	public:

		template<class T>
		static std::shared_ptr<T> 
			Find
			(
				const std::map<Standard_Integer, std::shared_ptr<T>>&,
				const Standard_Integer theIndex
			);

		template<class T>
		static void Insert
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<T>& theItem, 
			std::map<Standard_Integer, std::shared_ptr<T>>&
		);

		template<class T>
		static void Insert
		(
			const Standard_Integer theIndex,
			std::shared_ptr<T>&& theItem,
			std::map<Standard_Integer, std::shared_ptr<T>>&
		);

		template<class T>
		static void InsertIgnoreDup
		(
			const Standard_Integer theIndex,
			std::shared_ptr<T>&& theItem, 
			std::map<Standard_Integer, std::shared_ptr<T>>&
		);

		template<class T>
		static void InsertIgnoreDup
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<T>& theItem,
			std::map<Standard_Integer, std::shared_ptr<T>>&
		);

		template<class Type>
		static size_t
			FindSpan
			(
				const Standard_Real x,
				const std::vector<Type>& theSorted,
				Standard_Real(*xValue)(const Type&)
			);

		static TnbGlobal_EXPORT size_t
			FindSpan
			(
				const Standard_Real x,
				const std::vector<Standard_Real>& theSorted
			);

		static inline Standard_Real 
			LinearInterpolate
			(
				const Standard_Real theX0,
				const Standard_Real theX1,
				const Standard_Real theY0,
				const Standard_Real theY1,
				const Standard_Real x
			);

		static inline Standard_Real 
			LinearInterpolate
			(
				const std::pair<Standard_Real, Standard_Real>& theXY0,
				const std::pair<Standard_Real, Standard_Real>& theXY1,
				const Standard_Real x
			);

		static TnbGlobal_EXPORT Standard_Real 
			Interpolate
			(
				const Standard_Real theRow, 
				const Standard_Real theCol,
				const Global_Table&
			);

		static TnbGlobal_EXPORT void 
			Check
			(
				const Standard_Real theRow,
				const Standard_Real theCol,
				const Global_Table&
			);

		static TnbGlobal_EXPORT void
			CheckSorted
			(
				const std::vector<Standard_Real>& theSorted,
				const char* theName
			);

		template<class Type, class UpType>
		static std::vector<std::shared_ptr<UpType>> 
			UpCast(const std::vector<std::shared_ptr<Type>>&);

		template<class T1, class T2>
		static std::vector<std::pair<T1, T2>>
			ConvertToPairedList
			(
				const std::vector<T1>&, const std::vector<T2>&
			);

		template<class Type1, class Type2, int nbVaries>
		static std::vector<std::array<Type2, nbVaries>> ConvertToArrayField(const std::vector<Type1>&);

		template<>
		static TnbGlobal_EXPORT std::vector<std::array<Standard_Real, 1>> 
			ConvertToArrayField<Standard_Real, Standard_Real, 1>
			(const std::vector<Standard_Real>&);

		template<class Key, class T>
		static std::vector<T> RetrieveValuesToList(const std::map<Key, T>&);

		static TnbGlobal_EXPORT bool IsNumber(const std::string& s);
		static TnbGlobal_EXPORT std::string ConvertToUpperCase(const std::string& s);
		static TnbGlobal_EXPORT std::string ConvertToLowerCase(const std::string& s);

	};
}

#include <Global_ToolsI.hxx>

#endif // !_Global_Tools_Header
