#include "InitRake.hxx"

void tnbLib::createRakeForm()
{
	auto form = std::make_shared<ptdModel::BladeFormNo1_Rake>();
	ImportToForm(form, myRake);
	myMakers->push_back(std::move(form));
}