#pragma once
#ifndef _LegModel_DispNo1_Defaults_Header
#define _LegModel_DispNo1_Defaults_Header

#include <LegModel_ConstParameter.hxx>
#include <CadModel_Module.hxx>

namespace tnbLib
{

	class LegModel_DispNo1_Defaults
	{

		typedef LegModel_ConstParameter param;

		/*Private Data*/

	public:

		static TnbCadModel_EXPORT const param LENGTH_ON_DECK;
		static TnbCadModel_EXPORT const param BEAM_ON_DECK;
		static TnbCadModel_EXPORT const param DEPTH_AT_BOW;
		static TnbCadModel_EXPORT const param DEPTH_AT_TRANSOM;
		static TnbCadModel_EXPORT const param TRANSOM_HEIGHT;


		static TnbCadModel_EXPORT const param BOW_ROUNDING;
		static TnbCadModel_EXPORT const param FORE_FOOT_SHAPE;
		static TnbCadModel_EXPORT const param STEM_RAKE;

		static TnbCadModel_EXPORT const param FWD_TIGHTNESS;
		static TnbCadModel_EXPORT const param FWD_FLARE;
		static TnbCadModel_EXPORT const param FWD_DEADRISE;
		static TnbCadModel_EXPORT const param FWD_SIDE_SLOPE;

		static TnbCadModel_EXPORT const param MID_TIGHTNESS;
		static TnbCadModel_EXPORT const param MID_FLARE;
		static TnbCadModel_EXPORT const param MID_DEADRISE;
		static TnbCadModel_EXPORT const param MID_SIDE_SLOPE;

		static TnbCadModel_EXPORT const param AFT_TIGHTNESS;
		static TnbCadModel_EXPORT const param AFT_FLARE;
		static TnbCadModel_EXPORT const param AFT_DEADRISE;
		static TnbCadModel_EXPORT const param AFT_SIDE_SLOPE;

		static TnbCadModel_EXPORT const param TRANSOM_RAKE;
		static TnbCadModel_EXPORT const param TRANSOM_WIDTH;

		static TnbCadModel_EXPORT const param KEEL_RISE_POINT;
		static TnbCadModel_EXPORT const param KEEL_POSITION;
		static TnbCadModel_EXPORT const param KEEL_RISE_SLOPE;
		static TnbCadModel_EXPORT const param KEEL_TRANSOM_SLOPE;

		static TnbCadModel_EXPORT const param MAX_AREA_LOCATION;
		static TnbCadModel_EXPORT const param FWD_FULLNESS;
		static TnbCadModel_EXPORT const param AFT_FULLNESS;

		static TnbCadModel_EXPORT const Standard_Integer NB_OF_NET_COLUMNS;
		static TnbCadModel_EXPORT const Standard_Integer NB_OF_NET_ROWS;
	};
}

#endif // !_LegModel_DispNo1_Defaults_Header
