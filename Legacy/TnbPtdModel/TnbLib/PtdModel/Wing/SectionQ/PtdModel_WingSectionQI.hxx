#pragma once
inline tnbLib::PtdModel_WingSectionQ::PtdModel_WingSectionQ
(
	const UpperFace & theUpper,
	const LowerFace & theLower
)
	: theUpper_(theUpper)
	, theLower_(theLower)
{
	//- empty body
}

inline tnbLib::PtdModel_WingSectionQ::PtdModel_WingSectionQ
(
	UpperFace && theUpper,
	LowerFace && theLower
)
	: theUpper_(std::move(theUpper))
	, theLower_(std::move(theLower))
{
	//- empty body
}

inline void tnbLib::PtdModel_WingSectionQ::SetUpper(const UpperFace & theFace)
{
	theUpper_ = theFace;
}

inline void tnbLib::PtdModel_WingSectionQ::SetLower(const LowerFace & theFace)
{
	theLower_ = theFace;
}

inline void tnbLib::PtdModel_WingSectionQ::SetUpper(UpperFace && theFace)
{
	theUpper_ = std::move(theFace);
}

inline void tnbLib::PtdModel_WingSectionQ::SetLower(LowerFace && theFace)
{
	theLower_ = std::move(theFace);
}