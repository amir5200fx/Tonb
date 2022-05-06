#pragma once
#ifndef _SeriesProps_TabulatedWagenB_V2_Header
#define _SeriesProps_TabulatedWagenB_V2_Header

#include <SeriesProps_TabulatedWagenB.hxx>

namespace tnbLib
{

	namespace seriesProps
	{

		class TabulatedWagenB_V2
			: public SeriesProps_TabulatedWagenB
		{

			/*Private Data*/

		public:

			static TnbSeriesProps_EXPORT const Standard_Real maxTabulatedRadius;

			// default constructor [1/12/2022 Amir]

			TabulatedWagenB_V2()
			{}

			// constructors [1/12/2022 Amir]


			// override functions and operators [1/12/2022 Amir]

			Standard_Real MaxTabulatedRadius() const override
			{
				return maxTabulatedRadius;
			}

			TnbSeriesProps_EXPORT Standard_Real
				Value
				(
					const Standard_Real rPerR,
					const Standard_Real P
				) const override;

			// public functions and operators [1/12/2022 Amir]

		};

		extern TnbSeriesProps_EXPORT std::shared_ptr<TabulatedWagenB_V2> gl_wagenB_V2_values;
	}
}

#endif // !_SeriesProps_TabulatedWagenB_V2_Header
