#pragma once
#ifndef _SeriesProps_TabulatedWagenB_Header
#define _SeriesProps_TabulatedWagenB_Header

#include <Standard_TypeDef.hxx>
#include <SeriesProps_Module.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations [1/12/2022 Amir]
	class Geo_InterplFunction;
	class Geo_SamplingFunction;

	class SeriesProps_TabulatedWagenB
	{

		/*Private Data*/

		std::shared_ptr<Geo_SamplingFunction> theRadiusFun_;
		std::shared_ptr<Geo_SamplingFunction> thePFun_;

	protected:

		// default constructor [1/12/2022 Amir]

		SeriesProps_TabulatedWagenB()
		{}

		// constructors [1/12/2022 Amir]

		SeriesProps_TabulatedWagenB
		(
			const std::shared_ptr<Geo_SamplingFunction>& theRaFun, 
			const std::shared_ptr<Geo_SamplingFunction>& thePFun
		)
			: theRadiusFun_(theRaFun)
			, thePFun_(thePFun)
		{}

		SeriesProps_TabulatedWagenB
		(
			std::shared_ptr<Geo_SamplingFunction>&& theRaFun,
			std::shared_ptr<Geo_SamplingFunction>&& thePFun
		)
			: theRadiusFun_(std::move(theRaFun))
			, thePFun_(std::move(thePFun))
		{}


		// protected functions and operators [1/12/2022 Amir]

	public:

		static TnbSeriesProps_EXPORT const Standard_Real maxRadius;
		static TnbSeriesProps_EXPORT const Standard_Real minRadius;

		static TnbSeriesProps_EXPORT const Standard_Real minP;
		static TnbSeriesProps_EXPORT const Standard_Real maxP;

		virtual ~SeriesProps_TabulatedWagenB()
		{}

		// public functions and operators [1/12/2022 Amir]

		const auto& RadiusFun() const
		{
			return theRadiusFun_;
		}

		const auto& PFun() const
		{
			return thePFun_;
		}

		virtual Standard_Real MaxTabulatedRadius() const = 0;
		virtual Standard_Real Value(const Standard_Real rPerR, const Standard_Real P) const = 0;

		void SetRadiusFun(const std::shared_ptr<Geo_SamplingFunction>& theFun)
		{
			theRadiusFun_ = theFun;
		}

		void SetPFun(const std::shared_ptr<Geo_SamplingFunction>& theFun)
		{
			thePFun_ = theFun;
		}

		void SetRadiusFun(std::shared_ptr<Geo_SamplingFunction>&& theFun)
		{
			theRadiusFun_ = std::move(theFun);
		}

		void SetPFun(std::shared_ptr<Geo_SamplingFunction>&& theFun)
		{
			thePFun_ = std::move(theFun);
		}
	};
}

#endif // !_SeriesProps_TabulatedWagenB_Header
