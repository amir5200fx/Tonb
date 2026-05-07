#pragma once
inline Standard_Real 
tnbLib::HydStatic_DisContinuBonjean::Clip::Z0() const
{
	return FirstValue().Y();
}

inline Standard_Real 
tnbLib::HydStatic_DisContinuBonjean::Clip::Z1() const
{
	return LastValue().Y();
}

inline Standard_Real 
tnbLib::HydStatic_DisContinuBonjean::Clip::Value0() const
{
	return FirstValue().X();
}

inline Standard_Real 
tnbLib::HydStatic_DisContinuBonjean::Clip::Value1() const
{
	return LastValue().X();
}

inline std::shared_ptr<tnbLib::HydStatic_DisContinuBonjean::Clip>
tnbLib::HydStatic_DisContinuBonjean::Clip::Scaled(const Standard_Real coeff) const
{
	auto c = Copy();
	c->Scale(coeff);
	return std::move(c);
}

inline void tnbLib::HydStatic_DisContinuBonjean::Clip::SetCurve
(
	std::shared_ptr<HydStatic_BnjCurve> && theCurve
)
{
	theCurve_ = std::move(theCurve);
}

inline void tnbLib::HydStatic_DisContinuBonjean::Clip::SetSpan(const span & s)
{
	theSpan_ = s;
}

inline void tnbLib::HydStatic_DisContinuBonjean::Clip::SetSpan(span && s)
{
	theSpan_ = std::move(s);
}

inline Standard_Integer 
tnbLib::HydStatic_DisContinuBonjean::SectionClips::NbClips() const
{
	return (Standard_Integer)theClips_.size();
}

std::shared_ptr<tnbLib::HydStatic_DisContinuBonjean::Clip>
tnbLib::HydStatic_DisContinuBonjean::SectionClips::First() const
{
	if (theClips_.empty())
	{
		FatalErrorIn(FunctionSIG)
			<< "the list is empty" << endl
			<< abort(FatalError);
	}
	return theClips_[0];
}

inline std::shared_ptr<tnbLib::HydStatic_DisContinuBonjean::Clip>
tnbLib::HydStatic_DisContinuBonjean::SectionClips::Last() const
{
	if (theClips_.empty())
	{
		FatalErrorIn(FunctionSIG)
			<< "the list is empty" << endl
			<< abort(FatalError);
	}
	return theClips_[theClips_.size() - 1];
}

inline Standard_Real 
tnbLib::HydStatic_DisContinuBonjean::SectionClips::MaxValue() const
{
	return Value1();
}

inline Standard_Real 
tnbLib::HydStatic_DisContinuBonjean::SectionClips::Dz() const
{
	return Z1() - Z0();
}

inline Standard_Real 
tnbLib::HydStatic_DisContinuBonjean::SectionClips::CalcAngle() const
{
	return std::atan(MaxValue() / Dz());
}

inline Standard_Real 
tnbLib::HydStatic_DisContinuBonjean::SectionClips::Z0() const
{
	return First()->Z0();
}

inline Standard_Real
tnbLib::HydStatic_DisContinuBonjean::SectionClips::Z1() const
{
	return Last()->Z1();
}

inline Standard_Real 
tnbLib::HydStatic_DisContinuBonjean::SectionClips::Value0() const
{
	return First()->Value0();
}

inline Standard_Real 
tnbLib::HydStatic_DisContinuBonjean::SectionClips::Value1() const
{
	return Last()->Value1();
}

inline void tnbLib::HydStatic_DisContinuBonjean::LoadDomain
(
	const std::shared_ptr<Marine_Domain>& theDomain
)
{
	theDomain_ = theDomain;
}

inline void tnbLib::HydStatic_DisContinuBonjean::LoadBody
(
	const std::shared_ptr<Marine_Body>& theBody
)
{
	theBody_ = theBody;
}

inline void tnbLib::HydStatic_DisContinuBonjean::SetNbLevels
(
	const Standard_Integer n
)
{
	theNbLevels_ = n;
}

inline void tnbLib::HydStatic_DisContinuBonjean::SetInterplScheme
(
	const interplScheme s
)
{
	theInterplScheme_ = s;
}
