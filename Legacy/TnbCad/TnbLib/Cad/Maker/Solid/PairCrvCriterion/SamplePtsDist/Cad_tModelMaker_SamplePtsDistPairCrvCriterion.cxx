#include <Cad_tModelMaker_SamplePtsDistPairCrvCriterion.hxx>

#include <Cad_CurveLength.hxx>
#include <Cad_CurveSplitter.hxx>

tnbLib::Cad_tModelMaker_SamplePtsDistPairCrvCriterion::Cad_tModelMaker_SamplePtsDistPairCrvCriterion()
	: theLengthInfo_(Cad_CurveLength::DEFAULT_INFO)
	, theSplitterInfo_(Cad_CurveSplitter::DEFAULT_INFO)
{
	// empty body [1/16/2022 Amir]
}