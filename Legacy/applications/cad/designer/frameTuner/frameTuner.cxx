#include "frameTuner.hxx"

#include <SectPx_FrameTuner.hxx>

std::tuple<std::pair<int, int>, int> 
tnbLib::appl::createSlider(const tuner_t & t, int seg, const par_t & p)
{
	auto segmt = t->SelectSegment(seg);
	auto tt = t->CreateSlider(segmt, p);
	return std::move(tt);
}

std::tuple<std::pair<int, int>, int> 
tnbLib::appl::createSlider(const tuner_t & t, int seg, const coord_t & p)
{
	auto segmt = t->SelectSegment(seg);
	auto tt = t->CreateSlider(segmt, p);
	return std::move(tt);
}

int tnbLib::appl::createWeight(const tuner_t & t, int i, const par_t & p)
{
	auto pole = t->SelectPole(i);
	return t->CreateWeight(pole, p);
}

int tnbLib::appl::createSymmTightness(const tuner_t & t, int i, const par_t & p)
{
	auto pole = t->SelectPole(i);
	return t->CreateSymmTightnessDeg2(pole, p);
}

void tnbLib::appl::importFrame(const tuner_t & t, const frame_t & f)
{
	t->ImportFrame(f);
}