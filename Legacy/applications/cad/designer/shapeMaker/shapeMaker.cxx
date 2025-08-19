#include "shapeMaker.hxx"

#include <SectPx_Registry.hxx>
#include <SectPx_Frame.hxx>
#include <SectPx_ExtrProfiles.hxx>
#include <ShapePx_ExtrudedPatch.hxx>
#include <ShapePx_ExtrudeOp.hxx>
#include <ShapePx_Section.hxx>
#include <ShapePx_ContinProfile_OffsetCustom.hxx>
#include <ShapePx_ExtrudeSpacing.hxx>
#include <ShapePx_CustomSpacing.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#define TypeName_APPL typename tnbLib::appl::


void tnbLib::appl::createSection()
{
	if (NOT myPatch)
	{
		FatalErrorIn(FunctionSIG)
			<< "no patch has been created!" << endl
			<< abort(FatalError);
	}
	if (myPatch->Section())
	{
		FatalErrorIn(FunctionSIG)
			<< "there is already a section in the patch" << endl
			<< abort(FatalError);
	}
	const auto& reg = getRegistry();
	const auto id = reg->CreateFrame();
	const auto frame = reg->SelectFrame(id);
	auto section = std::make_shared<ShapePx_Section>(0, "section", frame);
	myPatch->SetSection(section);
}

const TypeName_APPL section_t & 
tnbLib::appl::getSection()
{
	return myPatch->Section();
}

TypeName_APPL frame_t 
tnbLib::appl::createSectionFrame()
{
	auto frame = 
		std::make_shared<SectPx_Frame>(getParRegistry(), getSection()->Registry());
	return std::move(frame);
}

TypeName_APPL profileBnd
tnbLib::appl::createProfileBounds
(
	const par_t & minLow, 
	const par_t & maxLow, 
	const par_t & x0, 
	const par_t & x1
)
{
	auto t = std::make_tuple(minLow, maxLow, x0, x1);
	return std::move(t);
}

TypeName_APPL extrProfile_t 
tnbLib::appl::createUniformExtrudeProfile(const profileBnd & b, const par_t & v)
{
	auto[minLow, maxUpper, x0, x1] = b;
	auto prf = std::make_shared<sectPxLib::ExtrProfile_Uniform>();
	prf->SetStart(minLow);
	prf->SetEnd(maxUpper);
	prf->SetX0(x0);
	prf->SetX1(x1);
	prf->SetValue(v);
	
	auto t = std::make_shared<shapePxLib::ContinProfile_OffsetCustom>(std::move(prf));
	return std::move(t);
}

TypeName_APPL extrProfile_t 
tnbLib::appl::createLinearExtrudeProfile(const profileBnd & b, const par_t & v0, const par_t & v1)
{
	auto[minLow, maxUpper, x0, x1] = b;
	auto prf = std::make_shared<sectPxLib::ExtrProfile_Linear>();
	prf->SetStart(minLow);
	prf->SetEnd(maxUpper);
	prf->SetX0(x0);
	prf->SetX1(x1);
	prf->SetValue0(v0);
	prf->SetValue1(v1);

	auto t = std::make_shared<shapePxLib::ContinProfile_OffsetCustom>(std::move(prf));
	return std::move(t);
}

void tnbLib::appl::setExtrudeProfile(int par, const extrProfile_t & t)
{
	myPatch->ImportProfileForParameter(par, t);
}

void tnbLib::appl::execute()
{
	if (NOT mySpacing)
	{
		calcSpacing();
	}
	myOp->SetPatch(myPatch);
	myOp->SetSpacing(mySpacing);
	myOp->Perform();
}

void tnbLib::appl::calcSpacing()
{
	ShapePx_ExtrudeSpacing spacing;
	if (NOT myPatch)
	{
		FatalErrorIn(FunctionSIG)
			<< "no patch is found!" << endl
			<< abort(FatalError);
	}

	const auto& profiles = myPatch->SectionParameterToProfileMap();
	for (const auto& x : profiles)
	{
		const auto& prf = x.second;
		ShapePx_ExtrudeSpacing::Span s = { prf->MinLower(),prf->MaxUpper() };
		spacing.ImportSpan(std::move(s));
	}
	spacing.Perform();
	mySpacing = spacing.Spacing();
}