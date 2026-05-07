#include <Cad_tModelMaker_SamplePtsDistPairCrvCriterion.hxx>

#include <Cad_CurveLength_Info.hxx>
#include <Cad_CurveSplitter_Info.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::Cad_tModelMaker_SamplePtsDistPairCrvCriterion)
{
	ar & boost::serialization::base_object<Cad_tModelMaker_PairCrvCriterion>(*this);

	ar & theLengthInfo_;
	ar & theSplitterInfo_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Cad_tModelMaker_SamplePtsDistPairCrvCriterion)
{
	ar & boost::serialization::base_object<Cad_tModelMaker_PairCrvCriterion>(*this);

	ar & theLengthInfo_;
	ar & theSplitterInfo_;
}