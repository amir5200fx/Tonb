#include "InitPitch.hxx"

void tnbLib::createPitchForm()
{
	auto form = std::make_shared<ptdModel::BladeFormNo1_Pitch>();
	ImportToForm(form, myRootPitch);
	ImportToForm(form, myTipPitch);
	ImportToForm(form, myTipSteepPitch);
	ImportToForm(form, myRootSteepPitch);
	myMakers->push_back(std::move(form));
}