#pragma once
template<class Point>
inline tnbLib::PtdModel_AirfoilSectionQ<Point>::PtdModel_AirfoilSectionQ(const faceQ & face, const backQ & back)
	: theFace_(face)
	, theBack_(back)
{
	// empty body [6/9/2021 Amir]
}

template<class Point>
inline tnbLib::PtdModel_AirfoilSectionQ<Point>::PtdModel_AirfoilSectionQ(faceQ && face, backQ && back)
	: theFace_(std::move(face))
	, theBack_(std::move(back))
{
	// empty body [6/9/2021 Amir]
}

template<class Point>
inline void tnbLib::PtdModel_AirfoilSectionQ<Point>::SetQ(const faceQ & f)
{
	theFace_ = f;
}

template<class Point>
inline void tnbLib::PtdModel_AirfoilSectionQ<Point>::SetQ(const backQ & f)
{
	theBack_ = f;
}

template<class Point>
inline void tnbLib::PtdModel_AirfoilSectionQ<Point>::SetQ(faceQ && f)
{
	theFace_ = std::move(f);
}

template<class Point>
inline void tnbLib::PtdModel_AirfoilSectionQ<Point>::SetQ(backQ && f)
{
	theBack_ = std::move(f);
}