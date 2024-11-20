#pragma once
#include <Mesh_ReferenceValues.hxx>
#include <Global_Real.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

template<class BackGroundMesh>
inline void tnbLib::Mesh_SizeMapToolBase<BackGroundMesh>::AllocateMemory()
{
	theConditions_ = std::make_shared<Mesh_Conditions>();
	theValues_ = std::make_shared<Mesh_Values>();
}

template<class BackGroundMesh>
inline void tnbLib::Mesh_SizeMapToolBase<BackGroundMesh>::RetrieveValues
(
	Standard_Real & theElementSize,
	Standard_Real & theMinSize,
	Standard_Real & theSpanAngle
) const
{
	const auto& ref = *theReference_;

	if (theConditions_->CustomSurfaceSize())
	{
		// Specify Relative or Absolute sizes
		if (theValues_->SurfaceSize()->RelativeAbsolute() IS_EQUAL Mesh_RelativeAbsoluteInfo::absolute)
		{
			theElementSize = theValues_->SurfaceSize()->TargetSize();
			theMinSize = theValues_->SurfaceSize()->MinSize();
		}
		else
		{// is Relative to Base
			theElementSize = theValues_->SurfaceSize()->TargetSize()*ref.BaseSize() / 100.0;
			theMinSize = theValues_->SurfaceSize()->MinSize()*ref.BaseSize() / 100.0;
		}
	}
	else
	{
		if (ref.SurfaceSize()->RelativeAbsolute() IS_EQUAL Mesh_RelativeAbsoluteInfo::absolute)
		{
			theElementSize = ref.SurfaceSize()->TargetSize();
			theMinSize = ref.SurfaceSize()->MinSize();
		}
		else
		{
			theElementSize = ref.SurfaceSize()->TargetSize()*ref.BaseSize() / 100.0;
			theMinSize = ref.SurfaceSize()->MinSize()*ref.BaseSize() / 100.0;
		}
	}

	if (theElementSize <= 0.0 OR theMinSize <= 0.0)
	{
		FatalErrorIn(FunctionSIG)
			<< "NULL element size has been detected" << endl
			<< abort(FatalError);
	}

	// Specify Combination of min, target sizes
	if (theValues_->SurfaceSize()->SizeMethod() IS_EQUAL Mesh_SizeMethodInfo::minOnly)
	{
		theElementSize = theMinSize;
	}

	if (theConditions_->CustomSurfaceCurvature() IS_EQUAL Mesh_SurfaceCurvatureInfo::disable)
	{
		theSpanAngle = RealLast();
	}
	else if (theConditions_->CustomSurfaceCurvature() IS_EQUAL Mesh_SurfaceCurvatureInfo::continum)
	{
		theSpanAngle = ref.SurfaceCurvature()->SpanAngle();
	}
	else
	{// Specify Surface curvature value 
		theSpanAngle = theValues_->SurfaceCurvature()->SpanAngle();
	}

	if (theSpanAngle <= 0.0)
	{
		FatalErrorIn(FunctionSIG)
			<< "NULL span angle has been detected" << endl
			<< abort(FatalError);
	}
}

template<class BackGroundMesh>
inline Standard_Real tnbLib::Mesh_SizeMapToolBase<BackGroundMesh>::RetrieveTargetSize() const
{
	if (theValues_->SurfaceSize()->RelativeAbsolute() IS_EQUAL Mesh_RelativeAbsoluteInfo::absolute)
	{
		return theValues_->SurfaceSize()->TargetSize();
	}
	else
	{
		return theValues_->SurfaceSize()->TargetSize()*theReference_->BaseSize() / 100.0;
	}
}

template<class BackGroundMesh>
inline Standard_Real tnbLib::Mesh_SizeMapToolBase<BackGroundMesh>::GetBaseSize() const
{
	return theReference_->BaseSize();
}

template<class BackGroundMesh>
inline Standard_Real tnbLib::Mesh_SizeMapToolBase<BackGroundMesh>::GetTargetSurfaceSize() const
{
	if (theConditions_->CustomSurfaceSize())
	{
		if (theValues_->SurfaceSize()->RelativeAbsolute() IS_EQUAL Mesh_RelativeAbsoluteInfo::absolute)
		{
			return theValues_->SurfaceSize()->TargetSize();
		}
		return theValues_->SurfaceSize()->TargetSize()*theReference_->BaseSize() / 100.0;
	}
	if (theReference_->SurfaceSize()->RelativeAbsolute() IS_EQUAL Mesh_RelativeAbsoluteInfo::absolute)
	{
		return theReference_->SurfaceSize()->TargetSize();
	}
	return theReference_->SurfaceSize()->TargetSize()*theReference_->BaseSize() / 100.0;
}

template<class BackGroundMesh>
inline Standard_Real tnbLib::Mesh_SizeMapToolBase<BackGroundMesh>::GetBoundaryGrowthRate() const
{
	if (theConditions_->CustomBoundaryGrowthRate())
	{
		return Mesh_VariationRate::Rate(theValues_->BoundaryGrowthRate());
	}
	else
	{
		return Mesh_VariationRate::Rate(theReference_->DefaultGrowthRate());
	}
}