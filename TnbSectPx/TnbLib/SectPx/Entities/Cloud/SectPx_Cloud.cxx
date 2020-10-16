#include <SectPx_Cloud.hxx>

void tnbLib::SectPx_Cloud::AllocateMemory()
{
	theProfile_ = std::make_shared<Profile>();
}

Standard_Boolean 
tnbLib::SectPx_Cloud::IsCloud() const
{
	return Standard_True;
}

tnbLib::sectPxLib::regObjType 
tnbLib::SectPx_Cloud::RegObjType() const
{
	return sectPxLib::regObjType::cloud;
}