#pragma once
#ifndef _Geo_TableFunction_Header
#define _Geo_TableFunction_Header

#include <Standard_TypeDef.hxx>
#include <Geo_Module.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations [1/13/2022 Amir]
	class Geo_SamplingFunction;

	class Global_Table;

	class Geo_TableFunction
	{

		/*Private Data*/

		std::shared_ptr<Geo_SamplingFunction> theRow_;
		std::shared_ptr<Geo_SamplingFunction> theCol_;

	public:

		// default constructor [1/13/2022 Amir]

		Geo_TableFunction()
		{}

		// constructors [1/13/2022 Amir]

		Geo_TableFunction
		(
			const std::shared_ptr<Geo_SamplingFunction>& theRowFun, 
			const std::shared_ptr<Geo_SamplingFunction>& theColFun
		)
			: theRow_(theRowFun)
			, theCol_(theColFun)
		{}

		Geo_TableFunction
		(
			std::shared_ptr<Geo_SamplingFunction>&& theRowFun,
			std::shared_ptr<Geo_SamplingFunction>&& theColFun
		)
			: theRow_(std::move(theRowFun))
			, theCol_(std::move(theColFun))
		{}

		// public functions and operators [1/13/2022 Amir]

		const auto& RowFun() const
		{
			return theRow_;
		}

		const auto& ColFun() const
		{
			return theCol_;
		}

		TnbGeo_EXPORT Standard_Real 
			Value
			(
				const Standard_Real theRow, 
				const Standard_Real theCol, 
				const Global_Table&
			) const;

		void SetRowFun(const std::shared_ptr<Geo_SamplingFunction>& theFun)
		{
			theRow_ = theFun;
		}

		void SetRowFun(std::shared_ptr<Geo_SamplingFunction>&& theFun)
		{
			theRow_ = std::move(theFun);
		}

		void SetColFun(const std::shared_ptr<Geo_SamplingFunction>& theFun)
		{
			theCol_ = theFun;
		}

		void SetColFun(std::shared_ptr<Geo_SamplingFunction>&& theFun)
		{
			theCol_ = std::move(theFun);
		}
	};
}

#endif // !_Geo_TableFunction_Header
