#pragma once
template<class CurveType>
inline Standard_Real tnbLib::Mesh_CurveRemesh<CurveType>::BaseSize() const
{
	return theBaseSize_;
}

template<class CurveType>
inline Standard_Real tnbLib::Mesh_CurveRemesh<CurveType>::MinSize() const
{
	return theMinSize_;
}

template<class CurveType>
inline Standard_Real tnbLib::Mesh_CurveRemesh<CurveType>::UnderRelaxation() const
{
	return theUnderRelaxation_;
}

template<class CurveType>
inline Standard_Real tnbLib::Mesh_CurveRemesh<CurveType>::SpanAngle() const
{
	return theSpanAngle_;
}

template<class CurveType>
inline Standard_Integer tnbLib::Mesh_CurveRemesh<CurveType>::MaxNbIterations() const
{
	return theMaxNbIterations_;
}

template<class CurveType>
inline Standard_Integer tnbLib::Mesh_CurveRemesh<CurveType>::MaxNbSmoothing() const
{
	return theMaxNbSmoothing_;
}

template<class CurveType>
inline Standard_Integer tnbLib::Mesh_CurveRemesh<CurveType>::NbSamples() const
{
	return theNbSamples_;
}

template<class CurveType>
inline Standard_Integer tnbLib::Mesh_CurveRemesh<CurveType>::MinNbSubdivisions() const
{
	return theMinSubdivision_;
}

template<class CurveType>
inline Standard_Integer tnbLib::Mesh_CurveRemesh<CurveType>::MaxNbSubdivisions() const
{
	return theMaxSubdivision_;
}

template<class CurveType>
inline Standard_Integer tnbLib::Mesh_CurveRemesh<CurveType>::UnbalancingLev() const
{
	return theUnbalancing_;
}

template<class CurveType>
inline Standard_Boolean tnbLib::Mesh_CurveRemesh<CurveType>::IsUsedRandSamples() const
{
	return useRandSamples_;
}

template<class CurveType>
inline Standard_Real tnbLib::Mesh_CurveRemesh<CurveType>::IterTolerance() const
{
	return theIterTolerance_;
}

template<class CurveType>
inline Standard_Real tnbLib::Mesh_CurveRemesh<CurveType>::SmoothingFactor() const
{
	return theSmoothingFactor_;
}

template<class CurveType>
inline tnbLib::Mesh_VariationRateInfo 
tnbLib::Mesh_CurveRemesh<CurveType>::VariationRate() const
{
	return theRate_;
}

template<class CurveType>
inline const std::shared_ptr<tnbLib::Mesh_Curve_Info>& 
tnbLib::Mesh_CurveRemesh<CurveType>::MeshInfo() const
{
	return theInfo_;
}

template<class CurveType>
inline const std::shared_ptr<typename tnbLib::Mesh_CurveRemesh<CurveType>::backMesh>& 
tnbLib::Mesh_CurveRemesh<CurveType>::BackgroundMesh() const
{
	return theBackmesh_;
}

template<class CurveType>
inline const std::shared_ptr<typename tnbLib::Mesh_CurveRemesh<CurveType>::chainData>&
tnbLib::Mesh_CurveRemesh<CurveType>::Chain() const
{
	return theChain_;
}

template<class CurveType>
inline const std::shared_ptr<typename tnbLib::Mesh_CurveRemesh<CurveType>::box>&
tnbLib::Mesh_CurveRemesh<CurveType>::BoundingBox() const
{
	return theBoundaingBox_;
}

template<class CurveType>
inline const std::vector<std::shared_ptr<CurveType>>& 
tnbLib::Mesh_CurveRemesh<CurveType>::Curves() const
{
	return theCurves_;
}

template<class CurveType>
inline void tnbLib::Mesh_CurveRemesh<CurveType>::SetBaseSize(const Standard_Real x)
{
	theBaseSize_ = x;
}

template<class CurveType>
inline void tnbLib::Mesh_CurveRemesh<CurveType>::SetMinSize(const Standard_Real x)
{
	theMinSize_ = x;
}

template<class CurveType>
inline void tnbLib::Mesh_CurveRemesh<CurveType>::SetUnderRelaxation(const Standard_Real x)
{
	theUnderRelaxation_ = x;
}

template<class CurveType>
inline void tnbLib::Mesh_CurveRemesh<CurveType>::SetSpanAngle(const Standard_Real x)
{
	theSpanAngle_ = x;
}

template<class CurveType>
inline void tnbLib::Mesh_CurveRemesh<CurveType>::SetMaxNbIterations(const Standard_Integer n)
{
	theMaxNbIterations_ = n;
}

template<class CurveType>
inline void tnbLib::Mesh_CurveRemesh<CurveType>::SetMaxNbSmoothing(const Standard_Integer n)
{
	theMaxNbSmoothing_ = n;
}

template<class CurveType>
inline void tnbLib::Mesh_CurveRemesh<CurveType>::SetIterTolerance(const Standard_Real x)
{
	theIterTolerance_ = x;
}

template<class CurveType>
inline void tnbLib::Mesh_CurveRemesh<CurveType>::SetSmoothingFactor(const Standard_Real x)
{
	theSmoothingFactor_ = x;
}

template<class CurveType>
inline void tnbLib::Mesh_CurveRemesh<CurveType>::SetVariationRate(const Mesh_VariationRateInfo x)
{
	theRate_ = x;
}

template<class CurveType>
inline void tnbLib::Mesh_CurveRemesh<CurveType>::LoadCurves
(
	const std::vector<std::shared_ptr<CurveType>>& theCurves
)
{
	theCurves_ = theCurves;
}

template<class CurveType>
inline void tnbLib::Mesh_CurveRemesh<CurveType>::LoadCurves
(
	std::vector<std::shared_ptr<CurveType>>&& theCurves
)
{
	theCurves_ = std::move(theCurves);
}