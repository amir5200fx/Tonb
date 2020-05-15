#include <meshUntangler.hxx>

#include <demandDrivenData.hxx>
#include <plane.hxx>
#include <primitiveMesh.hxx>
#include <polyMeshGenModifier.hxx>
#include <helperFunctions.hxx>

//#define DEBUGSmooth

#ifdef DEBUGSmooth
#include <foamTime.hxx>
#include <objectRegistry.hxx>
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	bool meshUntangler::cutRegion::findNewVertices
	(
		const plane& plane
	)
	{
#ifdef DEBUGSmooth
		Info << "Finding new vertices" << endl;
#endif

		const DynList<point, 64>& points = *pointsPtr_;

		newVertexLabel_.setSize(points.size());
		newVertexLabel_ = -1;

		vertexDistance_.setSize(points.size());

		vertexTypes_.setSize(points.size());
		vertexTypes_ = direction(NONE);

		origNumVertices_ = 0;

		cPtsPtr_ = new DynList<point, 64>();

		const point& rp = plane.refPoint();
		const vector& n = plane.normal();
		forAll(points, pI)
		{
			const point& p = points[pI];
			vertexDistance_[pI] = ((p - rp) & n);

			if (vertexDistance_[pI] > tol_)
			{
				cPtsPtr_->append(p);
				newVertexLabel_[pI] = origNumVertices_++;
				vertexTypes_[pI] |= KEEP;
			}
			else if (vertexDistance_[pI] >= -tol_)
			{
				cPtsPtr_->append(p);
				newVertexLabel_[pI] = origNumVertices_++;
				vertexTypes_[pI] |= INPLANE;
				vertexDistance_[pI] = 0.0;
			}
		}

#ifdef DEBUGSmooth
		Info << "tolerance " << tol_ << endl;
		Info << "New number of vertices is " << origNumVertices_ << endl;
		forAll(points, pI)
			Info << "Original vertex " << pI << " is " << points[pI]
			<< ". Vertex distance from plane is " << vertexDistance_[pI]
			<< " and its new label is " << newVertexLabel_[pI] << endl;
#endif

		if (origNumVertices_ < points.size())
		{
			return true;
		}
		else
		{
			deleteDemandDrivenData(cPtsPtr_);

			return false;
		}
	}

	void meshUntangler::cutRegion::removeCoincidentVertices()
	{
		const DynList<point, 64>& points = *pointsPtr_;
		DynList<edge, 128>& edges = *edgesPtr_;
		DynList<label, 64> newLabelForPoint;
		newLabelForPoint.setSize(points.size());
		newLabelForPoint = -1;

		bool found(false);
		forAll(points, pI)
		{
			if (newLabelForPoint[pI] != -1) continue;
			for (label pJ = pI + 1; pJ < points.size(); ++pJ)
				if (mag(points[pJ] - points[pI]) < tol_)
				{
# ifdef DEBUGSmooth
					Info << "Vertices " << pI << " and " << pJ
						<< " are too close" << endl;
# endif

					newLabelForPoint[pJ] = pI;
					found = true;
				}
		}

		if (!found)
			return;

		forAll(edges, eI)
		{
			edge& e = edges[eI];
			if (newLabelForPoint[e.start()] != -1)
				e.start() = newLabelForPoint[e.start()];
			if (newLabelForPoint[e.end()] != -1)
				e.end() = newLabelForPoint[e.end()];
		}

		//- remove edges which contain the same vertex
		newEdgeLabel_ = -1;
		label edgeLabel(0);

		cEdgesPtr_ = new DynList<edge, 128>();
		forAll(edges, eI)
			if (edges[eI].start() != edges[eI].end())
			{
				cEdgesPtr_->append(edges[eI]);
				newEdgeLabel_[eI] = edgeLabel++;
			}

		deleteDemandDrivenData(edgesPtr_);
		edgesPtr_ = cEdgesPtr_;
		cEdgesPtr_ = NULL;

		//- renumber faces
		const DynList<DynList<label, 8>, 64>& faces = *facesPtr_;
		cFacesPtr_ = new DynList<DynList<label, 8>, 64>();
		forAll(faces, fI)
		{
			const DynList<label, 8>& f = faces[fI];

			DynList<label, 8> nf;

			forAll(f, eI)
				if (newEdgeLabel_[f[eI]] != -1)
					nf.append(newEdgeLabel_[f[eI]]);

			if (nf.size() > 2)
			{
				cFacesPtr_->append(nf);
			}
		}

		deleteDemandDrivenData(facesPtr_);
		facesPtr_ = cFacesPtr_;
		cFacesPtr_ = NULL;
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //