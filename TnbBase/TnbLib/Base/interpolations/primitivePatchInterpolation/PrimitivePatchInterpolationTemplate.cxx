#include <PrimitivePatchInterpolationTemplate.hxx>

#include <faceList.hxx>
#include <demandDrivenData.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

	template<class Patch>
	const scalarListList&
		PrimitivePatchInterpolation<Patch>::faceToPointWeights() const
	{
		if (!faceToPointWeightsPtr_)
		{
			makeFaceToPointWeights();
		}

		return *faceToPointWeightsPtr_;
	}


	template<class Patch>
	void PrimitivePatchInterpolation<Patch>::makeFaceToPointWeights() const
	{
		if (faceToPointWeightsPtr_)
		{
			FatalErrorIn
			(
				"PrimitivePatchInterpolation<Patch>::makeFaceToPointWeights() const"
			) << "Face-to-edge weights already calculated"
				<< abort(FatalError);
		}

		const pointField& points = patch_.localPoints();
		const faceList& faces = patch_.localFaces();

		faceToPointWeightsPtr_ = new scalarListList(points.size());
		scalarListList& weights = *faceToPointWeightsPtr_;

		// get reference to addressing
		const labelListList& pointFaces = patch_.pointFaces();

		forAll(pointFaces, pointi)
		{
			const labelList& curFaces = pointFaces[pointi];

			scalarList& pw = weights[pointi];
			pw.setSize(curFaces.size());

			scalar sumw = 0.0;

			forAll(curFaces, facei)
			{
				pw[facei] =
					1.0 / mag(faces[curFaces[facei]].centre(points) - points[pointi]);
				sumw += pw[facei];
			}

			forAll(curFaces, facei)
			{
				pw[facei] /= sumw;
			}
		}
	}


	template<class Patch>
	const scalarList&
		PrimitivePatchInterpolation<Patch>::faceToEdgeWeights() const
	{
		if (!faceToEdgeWeightsPtr_)
		{
			makeFaceToEdgeWeights();
		}

		return *faceToEdgeWeightsPtr_;
	}


	template<class Patch>
	void PrimitivePatchInterpolation<Patch>::makeFaceToEdgeWeights() const
	{
		if (faceToEdgeWeightsPtr_)
		{
			FatalErrorIn
			(
				"PrimitivePatchInterpolation<Patch>::makeFaceToEdgeWeights() const"
			) << "Face-to-edge weights already calculated"
				<< abort(FatalError);
		}

		const pointField& points = patch_.localPoints();
		const faceList& faces = patch_.localFaces();
		const edgeList& edges = patch_.edges();
		const labelListList& edgeFaces = patch_.edgeFaces();

		faceToEdgeWeightsPtr_ = new scalarList(patch_.nInternalEdges());
		scalarList& weights = *faceToEdgeWeightsPtr_;

		for (label edgei = 0; edgei < weights.size(); edgei++)
		{
			vector P = faces[edgeFaces[edgei][0]].centre(points);
			vector N = faces[edgeFaces[edgei][1]].centre(points);
			vector S = points[edges[edgei].start()];
			vector e = edges[edgei].vec(points);

			scalar alpha =
				-(((N - P) ^ (S - P))&((N - P) ^ e)) / (((N - P) ^ e)&((N - P) ^ e));

			vector E = S + alpha * e;

			weights[edgei] = mag(N - E) / (mag(N - E) + mag(E - P));
		}
	}


	template<class Patch>
	void PrimitivePatchInterpolation<Patch>::clearWeights()
	{
		deleteDemandDrivenData(faceToPointWeightsPtr_);
		deleteDemandDrivenData(faceToEdgeWeightsPtr_);
	}


	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	template<class Patch>
	PrimitivePatchInterpolation<Patch>::PrimitivePatchInterpolation(const Patch& p)
		:
		patch_(p),
		faceToPointWeightsPtr_(NULL),
		faceToEdgeWeightsPtr_(NULL)
	{}


	// * * * * * * * * * * * * * * * * Destructor * * * * * * * * * * * * * * * //

	template<class Patch>
	PrimitivePatchInterpolation<Patch>::~PrimitivePatchInterpolation()
	{
		clearWeights();
	}


	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	template<class Patch>
	template<class Type>
	tmp<Field<Type> > PrimitivePatchInterpolation<Patch>::faceToPointInterpolate
	(
		const Field<Type>& ff
	) const
	{
		// Check size of the given field
		if (ff.size() != patch_.size())
		{
			FatalErrorIn
			(
				"tmp<Field<Type> > PrimitivePatchInterpolation::"
				"faceToPointInterpolate(const Field<Type> ff)"
			) << "given field does not correspond to patch. Patch size: "
				<< patch_.size() << " field size: " << ff.size()
				<< abort(FatalError);
		}

		tmp<Field<Type> > tresult
		(
			new Field<Type>
			(
				patch_.nPoints(), pTraits<Type>::zero
				)
		);

		Field<Type>& result = tresult();

		const labelListList& pointFaces = patch_.pointFaces();
		const scalarListList& weights = faceToPointWeights();

		forAll(pointFaces, pointi)
		{
			const labelList& curFaces = pointFaces[pointi];
			const scalarList& w = weights[pointi];

			forAll(curFaces, facei)
			{
				result[pointi] += w[facei] * ff[curFaces[facei]];
			}
		}

		return tresult;
	}


	template<class Patch>
	template<class Type>
	tmp<Field<Type> > PrimitivePatchInterpolation<Patch>::faceToPointInterpolate
	(
		const tmp<Field<Type> >& tff
	) const
	{
		tmp<Field<Type> > tint = faceToPointInterpolate(tff());
		tff.clear();
		return tint;
	}


	template<class Patch>
	template<class Type>
	tmp<Field<Type> > PrimitivePatchInterpolation<Patch>::pointToFaceInterpolate
	(
		const Field<Type>& pf
	) const
	{
		if (pf.size() != patch_.nPoints())
		{
			FatalErrorIn
			(
				"tmp<Field<Type> > PrimitivePatchInterpolation::"
				"pointToFaceInterpolate(const Field<Type> pf)"
			) << "given field does not correspond to patch. Patch size: "
				<< patch_.nPoints() << " field size: " << pf.size()
				<< abort(FatalError);
		}

		tmp<Field<Type> > tresult
		(
			new Field<Type>
			(
				patch_.size(),
				pTraits<Type>::zero
				)
		);

		Field<Type>& result = tresult();

		const faceList& localFaces = patch_.localFaces();

		forAll(result, facei)
		{
			const labelList& curPoints = localFaces[facei];

			forAll(curPoints, pointi)
			{
				result[facei] += pf[curPoints[pointi]];
			}

			result[facei] /= curPoints.size();
		}

		return tresult;
	}


	template<class Patch>
	template<class Type>
	tmp<Field<Type> > PrimitivePatchInterpolation<Patch>::pointToFaceInterpolate
	(
		const tmp<Field<Type> >& tpf
	) const
	{
		tmp<Field<Type> > tint = pointToFaceInterpolate(tpf());
		tpf.clear();
		return tint;
	}


	template<class Patch>
	template<class Type>
	tmp<Field<Type> > PrimitivePatchInterpolation<Patch>::faceToEdgeInterpolate
	(
		const Field<Type>& pf
	) const
	{
		// Check size of the given field
		if (pf.size() != patch_.size())
		{
			FatalErrorIn
			(
				"tmp<Field<Type> > PrimitivePatchInterpolation::"
				"faceToEdgeInterpolate(const Field<Type> ff)"
			) << "given field does not correspond to patch. Patch size: "
				<< patch_.size() << " field size: " << pf.size()
				<< abort(FatalError);
		}

		tmp<Field<Type> > tresult
		(
			new Field<Type>(patch_.nEdges(), pTraits<Type>::zero)
		);

		Field<Type>& result = tresult();

		const edgeList& edges = patch_.edges();
		const labelListList& edgeFaces = patch_.edgeFaces();

		const scalarList& weights = faceToEdgeWeights();

		for (label edgei = 0; edgei < patch_.nInternalEdges(); edgei++)
		{
			result[edgei] =
				weights[edgei] * pf[edgeFaces[edgei][0]]
				+ (1.0 - weights[edgei])*pf[edgeFaces[edgei][1]];
		}

		for (label edgei = patch_.nInternalEdges(); edgei < edges.size(); edgei++)
		{
			result[edgei] = pf[edgeFaces[edgei][0]];
		}

		return tresult;
	}


	template<class Patch>
	template<class Type>
	tmp<Field<Type> > PrimitivePatchInterpolation<Patch>::faceToEdgeInterpolate
	(
		const tmp<Field<Type> >& tpf
	) const
	{
		tmp<Field<Type> > tint = faceToEdgeInterpolate(tpf());
		tpf.clear();
		return tint;
	}


	template<class Patch>
	bool PrimitivePatchInterpolation<Patch>::movePoints()
	{
		clearWeights();

		return true;
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //