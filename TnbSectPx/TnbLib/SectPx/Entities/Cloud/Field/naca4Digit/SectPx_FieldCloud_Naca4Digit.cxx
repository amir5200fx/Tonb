#include <SectPx_FieldCloud_Naca4Digit.hxx>

#include <Geo_Naca4Digit.hxx>
#include <SectPx_Macros.hxx>
#include <SectPx_Coord.hxx>
#include <SectPx_ParTools.hxx>
#include <SectPx_Par.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>


void tnbLib::sectPxLib::FieldCloud_Naca4DigitBase::SetChord
(
	const std::shared_ptr<SectPx_Par>& thePar
)
{
	AddParameterToParent
	(
		theChord_, 
		thePar, 
		"void SetChord(const std::shared_ptr<SectPx_Par>& )"
	);
}

void tnbLib::sectPxLib::FieldCloud_Naca4DigitBase::SetMaxCamber
(
	const std::shared_ptr<SectPx_Par>& thePar
)
{
	AddParameterToParent
	(
		theMaxCamber_,
		thePar,
		"void SetMaxCamber(const std::shared_ptr<SectPx_Par>& )"
	);
}

void tnbLib::sectPxLib::FieldCloud_Naca4DigitBase::SetMaxCamberLoc
(
	const std::shared_ptr<SectPx_Par>& thePar
)
{
	AddParameterToParent
	(
		theMaxCamberLoc_,
		thePar,
		"void SetMaxCamberLoc(const std::shared_ptr<SectPx_Par>& )"
	);
}

void tnbLib::sectPxLib::FieldCloud_Naca4DigitBase::SetMaxThickness
(
	const std::shared_ptr<SectPx_Par>& thePar
)
{
	AddParameterToParent
	(
		theMaxThickness_,
		thePar,
		"void SetMaxThickness(const std::shared_ptr<SectPx_Par>& )"
	);
}

namespace tnbLib
{
	void SetParameter(const std::weak_ptr<SectPx_Par>& p, Standard_Real& x)
	{
		Debug_Null_Pointer(p.lock());
		x = p.lock()->Value();
	}
}

Standard_Integer 
tnbLib::sectPxLib::FieldCloud_Naca4DigitBase::NbChildren() const
{
	return 4;
}

Standard_Boolean 
tnbLib::sectPxLib::FieldCloud_Naca4DigitBase::IsComplete() const
{
	ReturnFalseIfNull(Chord());
	ReturnFalseIfNull(MaxCamber());
	ReturnFalseIfNull(MaxCamberLoc());
	ReturnFalseIfNull(MaxThickness());
	return Standard_True;
}

Standard_Boolean 
tnbLib::sectPxLib::FieldCloud_Naca4DigitBase::HasChildren() const
{
	return Standard_True;
}

Standard_Boolean 
tnbLib::sectPxLib::FieldCloud_Naca4DigitBase::HasChild
(
	const std::shared_ptr<SectPx_Child>& thePar
) const
{
	ReturnTrueIfParBelongsToThisParent(Chord(), thePar);
	ReturnTrueIfParBelongsToThisParent(MaxCamber(), thePar);
	ReturnTrueIfParBelongsToThisParent(MaxCamberLoc(), thePar);
	ReturnTrueIfParBelongsToThisParent(MaxThickness(), thePar);
	return Standard_False;
}

std::vector<std::shared_ptr<tnbLib::SectPx_Child>>
tnbLib::sectPxLib::FieldCloud_Naca4DigitBase::RetrieveChildren() const
{
	DefineChildList(childs);
	AddParToChildList(Chord(), childs);
	AddParToChildList(MaxCamber(), childs);
	AddParToChildList(MaxCamberLoc(), childs);
	AddParToChildList(MaxThickness(), childs);
	return std::move(childs);
}

void tnbLib::sectPxLib::FieldCloud_Naca4DigitBase::RemoveThisFromChildren() const
{
	auto chord = Chord().lock();
	if (chord)
	{
		RemoveThisFromChild(chord);
	}

	auto maxCamb = MaxCamber().lock();
	if (maxCamb)
	{
		RemoveThisFromChild(maxCamb);
	}

	auto maxCambLoc = MaxCamberLoc().lock();
	if (maxCambLoc)
	{
		RemoveThisFromChild(maxCambLoc);
	}

	auto maxThickness = MaxThickness().lock();
	if (maxThickness)
	{
		RemoveThisFromChild(maxThickness);
	}
}

void tnbLib::sectPxLib::FieldCloud_Naca4DigitBase::AddThisToChildren() const
{
	AddThisParentToChildren(Chord());
	AddThisParentToChildren(MaxCamber());
	AddThisParentToChildren(MaxCamberLoc());
	AddThisParentToChildren(MaxThickness());
}

void tnbLib::sectPxLib::FieldCloud_Naca4DigitBase::AddThisToChild
(
	const std::shared_ptr<SectPx_Child>& thePar
) const
{
	AddThisParentToChild(thePar);
}

void tnbLib::sectPxLib::FieldCloud_Naca4DigitBase::RemoveThisFromChild
(
	const std::shared_ptr<SectPx_Child>& thePar
) const
{
	RemoveThisParentFromChild(thePar);
}

const char* tnbLib::sectPxLib::naca::UpperEdge::typeName_ = "naca 4-digit upper edge field cloud";

void tnbLib::sectPxLib::naca::UpperEdge::Update() const
{
	if (NOT IsComplete())
	{
		FatalErrorIn(FunctionSIG)
			<< "the field is not completed!" << endl
			<< abort(FatalError);
	}
	Geo_Naca4Digit::Parameter params;

	SetParameter(Chord(), params.chord);
	SetParameter(MaxCamber(), params.maxCamber);
	SetParameter(MaxCamberLoc(), params.maxCamberLoc);
	SetParameter(MaxThickness(), params.maxThick);

	params.nbSections = NbSegments();

	Geo_Naca4Digit naca(std::move(params));

	naca.SetCloseTail(CloseTail_);
	naca.Perform();

	Debug_If_Condition_Message
	(
		NOT naca.IsDone(),
		"the naca 4 digit algorithm is not performed!"
	);

	const auto& upper = naca.Upper();

	Debug_Null_Pointer(theProfile_)
	theProfile_->Coords = std::move(upper);
}

tnbLib::word 
tnbLib::sectPxLib::naca::UpperEdge::RegObjTypeName() const
{
	return typeName_;
}

const char* tnbLib::sectPxLib::naca::LowerEdge::typeName_ = "naca 4-digit lower edge field cloud";

void tnbLib::sectPxLib::naca::LowerEdge::Update() const
{
	if (NOT IsComplete())
	{
		FatalErrorIn(FunctionSIG)
			<< "the field is not completed!" << endl
			<< abort(FatalError);
	}
	Geo_Naca4Digit::Parameter params;

	SetParameter(Chord(), params.chord);
	SetParameter(MaxCamber(), params.maxCamber);
	SetParameter(MaxCamberLoc(), params.maxCamberLoc);
	SetParameter(MaxThickness(), params.maxThick);

	params.nbSections = NbSegments();

	Geo_Naca4Digit naca(std::move(params));

	naca.SetCloseTail(CloseTail_);
	naca.Perform();

	Debug_If_Condition_Message
	(
		NOT naca.IsDone(),
		"the naca 4 digit algorithm is not performed!"
	);

	const auto& lower = naca.Lower();

	Debug_Null_Pointer(theProfile_)
		theProfile_->Coords = std::move(lower);
}

tnbLib::word 
tnbLib::sectPxLib::naca::LowerEdge::RegObjTypeName() const
{
	return typeName_;
}