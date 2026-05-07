#include <SectPx_Cloud.hxx>

#include <TnbError.hxx>
#include <OSstream.hxx>

void tnbLib::SectPx_Cloud::AllocateMemory()
{
	theProfile_ = std::make_shared<Profile>();
}

Standard_Boolean 
tnbLib::SectPx_Cloud::IsCloud() const
{
	return Standard_True;
}

Standard_Boolean 
tnbLib::SectPx_Cloud::IsFrameRegObj() const
{
	return Standard_True;
}

tnbLib::sectPxLib::regObjType 
tnbLib::SectPx_Cloud::RegObjType() const
{
	return sectPxLib::regObjType::cloud;
}

typename tnbLib::SectPx_Cloud::Profile & 
tnbLib::SectPx_Cloud::ProfileRef()
{
	if (NOT theProfile_)
	{
		FatalErrorIn(FunctionSIG)
			<< " found no profile fro the cloud!" << endl
			<< abort(FatalError);
	}
	return *theProfile_;
}