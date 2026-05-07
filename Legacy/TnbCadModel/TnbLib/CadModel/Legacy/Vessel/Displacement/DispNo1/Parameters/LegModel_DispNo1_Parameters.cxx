#include <LegModel_DispNo1_Parameters.hxx>

#include <LegModel_DispNo1_Defaults.hxx>
#include <LegModel_ConstParameter.hxx>
#include <LegModel_BoundedParameter.hxx>

typedef tnbLib::LegModel_DispNo1_Defaults DP;

tnbLib::LegModel_DispNo1_Dimensions::LegModel_DispNo1_Dimensions()
{
	theBeamOnDeck_ = std::make_shared<LegModel_ConstParameter>(DP::BEAM_ON_DECK.Index(), DP::BEAM_ON_DECK.Name(), DP::BEAM_ON_DECK.Value());
	theDepthAtBow_ = std::make_shared<LegModel_ConstParameter>(DP::DEPTH_AT_BOW.Index(), DP::DEPTH_AT_BOW.Name(), DP::DEPTH_AT_BOW.Value());
	theDepthAtTransom_ = std::make_shared<LegModel_ConstParameter>(DP::DEPTH_AT_TRANSOM.Index(), DP::DEPTH_AT_TRANSOM.Name(), DP::DEPTH_AT_TRANSOM.Value());
	theLengthOnDeck_ = std::make_shared<LegModel_ConstParameter>(DP::LENGTH_ON_DECK.Index(), DP::LENGTH_ON_DECK.Name(), DP::LENGTH_ON_DECK.Value());
	theTransomHeight_ = std::make_shared<LegModel_ConstParameter>(DP::TRANSOM_HEIGHT.Index(), DP::TRANSOM_HEIGHT.Name(), DP::TRANSOM_HEIGHT.Value());

	theNbNetColumns_ = DP::NB_OF_NET_COLUMNS;
	theNbNetRows_ = DP::NB_OF_NET_ROWS;
}

tnbLib::LegModel_DispNo1_AftSectionParams::LegModel_DispNo1_AftSectionParams()
{
	Tightness() = std::make_shared<LegModel_BoundedParameter>(DP::AFT_TIGHTNESS.Index(), DP::AFT_TIGHTNESS.Name(), DP::AFT_TIGHTNESS.Value(), 0, 1);
	Flare() = std::make_shared<LegModel_BoundedParameter>(DP::AFT_FLARE.Index(), DP::AFT_FLARE.Name(), DP::AFT_FLARE.Value(), 0, 1);
	Deadrise() = std::make_shared<LegModel_BoundedParameter>(DP::AFT_DEADRISE.Index(), DP::AFT_DEADRISE.Name(), DP::AFT_DEADRISE.Value(), 0, 1);
	SideSlope() = std::make_shared<LegModel_BoundedParameter>(DP::AFT_SIDE_SLOPE.Index(), DP::AFT_SIDE_SLOPE.Name(), DP::AFT_SIDE_SLOPE.Value(), 0, 1);
}

tnbLib::LegModel_DispNo1_FwdSectionParams::LegModel_DispNo1_FwdSectionParams()
{
	Tightness() = std::make_shared<LegModel_BoundedParameter>(DP::FWD_TIGHTNESS.Index(), DP::FWD_TIGHTNESS.Name(), DP::FWD_TIGHTNESS.Value(), 0, 1);
	Flare() = std::make_shared<LegModel_BoundedParameter>(DP::FWD_FLARE.Index(), DP::FWD_FLARE.Name(), DP::FWD_FLARE.Value(), 0, 1);
	Deadrise() = std::make_shared<LegModel_BoundedParameter>(DP::FWD_DEADRISE.Index(), DP::FWD_DEADRISE.Name(), DP::FWD_DEADRISE.Value(), 0, 1);
	SideSlope() = std::make_shared<LegModel_BoundedParameter>(DP::FWD_SIDE_SLOPE.Index(), DP::FWD_SIDE_SLOPE.Name(), DP::FWD_SIDE_SLOPE.Value(), 0, 1);
}

tnbLib::LegModel_DispNo1_MidSectionParams::LegModel_DispNo1_MidSectionParams()
{
	Tightness() = std::make_shared<LegModel_BoundedParameter>(DP::MID_TIGHTNESS.Index(), DP::MID_TIGHTNESS.Name(), DP::MID_TIGHTNESS.Value(), 0, 1);
	Flare() = std::make_shared<LegModel_BoundedParameter>(DP::MID_FLARE.Index(), DP::MID_FLARE.Name(), DP::MID_FLARE.Value(), 0, 1);
	Deadrise() = std::make_shared<LegModel_BoundedParameter>(DP::MID_DEADRISE.Index(), DP::MID_DEADRISE.Name(), DP::MID_DEADRISE.Value(), 0, 1);
	SideSlope() = std::make_shared<LegModel_BoundedParameter>(DP::MID_SIDE_SLOPE.Index(), DP::MID_SIDE_SLOPE.Name(), DP::MID_SIDE_SLOPE.Value(), 0, 1);
}

tnbLib::LegModel_DispNo1_KeelParams::LegModel_DispNo1_KeelParams()
{
	thePosition_ = std::make_shared<LegModel_BoundedParameter>(DP::KEEL_POSITION.Index(), DP::KEEL_POSITION.Name(), DP::KEEL_POSITION.Value(), 0, 1);
	theRisePoint_ = std::make_shared<LegModel_BoundedParameter>(DP::KEEL_RISE_POINT.Index(), DP::KEEL_RISE_POINT.Name(), DP::KEEL_RISE_POINT.Value(), 0, 1);
	theRiseSlope_ = std::make_shared<LegModel_BoundedParameter>(DP::KEEL_RISE_SLOPE.Index(), DP::KEEL_RISE_SLOPE.Name(), DP::KEEL_RISE_SLOPE.Value(), 0, 1);
	theTransomSlope_ = std::make_shared<LegModel_BoundedParameter>(DP::KEEL_TRANSOM_SLOPE.Index(), DP::KEEL_TRANSOM_SLOPE.Name(), DP::KEEL_TRANSOM_SLOPE.Value(), 0, 1);
}

tnbLib::LegModel_DispNo1_StemParams::LegModel_DispNo1_StemParams()
{
	theBowRounding_ = std::make_shared<LegModel_BoundedParameter>(DP::BOW_ROUNDING.Index(), DP::BOW_ROUNDING.Name(), DP::BOW_ROUNDING.Value(), 0, 1);
	theForeFootShape_ = std::make_shared<LegModel_BoundedParameter>(DP::FORE_FOOT_SHAPE.Index(), DP::FORE_FOOT_SHAPE.Name(), DP::FORE_FOOT_SHAPE.Value(), 0, 1);
	theStemRake_ = std::make_shared<LegModel_BoundedParameter>(DP::STEM_RAKE.Index(), DP::STEM_RAKE.Name(), DP::STEM_RAKE.Value(), 0, 1);
}

tnbLib::LegModel_DispNo1_TransomParams::LegModel_DispNo1_TransomParams()
{
	theRake_ = std::make_shared<LegModel_BoundedParameter>(DP::TRANSOM_RAKE.Index(), DP::TRANSOM_RAKE.Name(), DP::TRANSOM_RAKE.Value(), 0, 1);
	theWidth_ = std::make_shared<LegModel_BoundedParameter>(DP::TRANSOM_WIDTH.Index(), DP::TRANSOM_WIDTH.Name(), DP::TRANSOM_WIDTH.Value(), 0, 1);
}

tnbLib::LegModel_DispNo1_HullParams::LegModel_DispNo1_HullParams()
{
	theMaxAreaLocation_ = std::make_shared<LegModel_BoundedParameter>(DP::MAX_AREA_LOCATION.Index(), DP::MAX_AREA_LOCATION.Name(), DP::MAX_AREA_LOCATION.Value(), 0, 1);
	theAftFullness_ = std::make_shared<LegModel_BoundedParameter>(DP::AFT_FULLNESS.Index(), DP::AFT_FULLNESS.Name(), DP::AFT_FULLNESS.Value(), 0, 1);
	theFwdFullness_ = std::make_shared<LegModel_BoundedParameter>(DP::FWD_FULLNESS.Index(), DP::FWD_FULLNESS.Name(), DP::FWD_FULLNESS.Value(), 0, 1);
}
