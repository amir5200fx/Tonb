#pragma once
#ifndef _SeriesProps_WagenB_TableThreeBladed_Header
#define _SeriesProps_WagenB_TableThreeBladed_Header

#include <SeriesProps_Module.hxx>

#include <Standard_TypeDef.hxx>

#include <vector>
#include <memory>

namespace tnbLib
{

	// Forward Declarations [4/29/2022 Amir]
	class NumAlg_InterplFunc;

	namespace wagenB
	{

		class TableThreeBladed
		{

			/*Private Data*/


		public:

			static TnbSeriesProps_EXPORT const std::vector<Standard_Real> rPerR;

			static TnbSeriesProps_EXPORT const std::vector<Standard_Real> cPerD;
			static TnbSeriesProps_EXPORT const std::vector<Standard_Real> aPerc;
			static TnbSeriesProps_EXPORT const std::vector<Standard_Real> bPerc;

			static TnbSeriesProps_EXPORT const std::vector<Standard_Real> Ar;
			static TnbSeriesProps_EXPORT const std::vector<Standard_Real> Br;

			static TnbSeriesProps_EXPORT const std::shared_ptr<NumAlg_InterplFunc> Interpl_rPerR;
			
			static TnbSeriesProps_EXPORT const std::shared_ptr<NumAlg_InterplFunc> Interpl_cPerD;
			static TnbSeriesProps_EXPORT const std::shared_ptr<NumAlg_InterplFunc> Interpl_aPerc;
			static TnbSeriesProps_EXPORT const std::shared_ptr<NumAlg_InterplFunc> Interpl_bPerc;

			static TnbSeriesProps_EXPORT const std::shared_ptr<NumAlg_InterplFunc> Interpl_Ar;
			static TnbSeriesProps_EXPORT const std::shared_ptr<NumAlg_InterplFunc> Interpl_Br;


			static TnbSeriesProps_EXPORT Standard_Real CalcChord(const Standard_Real rPerR, const Standard_Real Dia, const Standard_Real AePerAo, const Standard_Integer Z);
			static TnbSeriesProps_EXPORT Standard_Real CalcA(const Standard_Real rPerR, const Standard_Real c);
			static TnbSeriesProps_EXPORT Standard_Real CalcB(const Standard_Real rPerR, const Standard_Real c);
			static TnbSeriesProps_EXPORT Standard_Real CalcThickness(const Standard_Real rPerR, const Standard_Real Dia, const Standard_Integer Z);
		};
	}
}

#endif // !_SeriesProps_WagenB_TableThreeBladed_Header
