#include "InitCamberLoc.hxx"

void tnbLib::createMaxCamberLocForm()
{
	auto form = std::make_shared<ptdModel::BladeFormNo1_CamberLoc>();
	ImportToForm(form, myBladeMaxCamber);
	myMakers->push_back(std::move(form));
}