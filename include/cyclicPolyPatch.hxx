#pragma once
#ifndef _cyclicPolyPatch_Header
#define _cyclicPolyPatch_Header

#include <coupledPolyPatch.hxx>
#include <SubField.hxx>
#include <FixedList.hxx>
#include <edgeList.hxx>
#include <transform.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						  Class cyclicPolyPatch Declaration
	\*---------------------------------------------------------------------------*/

	class cyclicPolyPatch
		: public coupledPolyPatch
	{
	public:

		enum transformType
		{
			UNKNOWN,
			ROTATIONAL,
			TRANSLATIONAL
		};
		static const NamedEnum<transformType, 3> transformTypeNames;


	private:

		// Private data

			//- List of edges formed from connected points. e[0] is the point on
			//  the first half of the patch, e[1] the corresponding point on the
			//  second half.
		mutable edgeList* coupledPointsPtr_;

		//- List of connected edges. e[0] is the edge on the first half of the
		//  patch, e[1] the corresponding edge on the second half.
		mutable edgeList* coupledEdgesPtr_;

		//- Morph:angle between normals of neighbouring faces.
		//  Used to split cyclic into halves.
		scalar featureCos_;

		//- Type of transformation - rotational or translational
		transformType transform_;

		// For rotation

			//- Axis of rotation for rotational cyclics
		vector rotationAxis_;

		//- Point on axis of rotation for rotational cyclics
		point rotationCentre_;

		//- Angle of rotation for rotational cyclics
		scalar rotationAngle_;


		// For translation

			//- Translation vector
		vector separationVector_;


		// Private member functions

			// Geometry

				//- Find amongst selected faces the one with the largest area
		static label findMaxArea(const pointField&, const faceList&);

		//- Force calculation of transformation tensors
		virtual void calcTransforms() const;


		// Face ordering

			//- Find the two parts of the faces of pp using feature edges.
			//  Returns true if successfull.
		bool getGeometricHalves
		(
			const primitivePatch&,
			labelList&,
			labelList&
		) const;

		//- Calculate geometric factors of the two halves.
		void getCentresAndAnchors
		(
			const primitivePatch&,
			const faceList& half0Faces,
			const faceList& half1Faces,
			pointField& ppPoints,
			pointField& half0Ctrs,
			pointField& half1Ctrs,
			pointField& anchors0,
			scalarField& tols
		) const;

		//- Given matched faces matches the anchor point. Sets faceMap,
		//  rotation. Returns true if all matched.
		bool matchAnchors
		(
			const bool report,
			const primitivePatch&,
			const labelList&,
			const pointField&,
			const labelList&,
			const faceList&,
			const labelList&,
			const scalarField&,

			labelList& faceMap,
			labelList& rotation
		) const;

		//- For rotational cases, try to find a unique face on each side
		//  of the cyclic.
		label getConsistentRotationFace
		(
			const pointField& faceCentres
		) const;


	protected:

		// Protected Member functions

			//- Initialise the calculation of the patch addressing
		virtual void initAddressing();

		//- Calculate the patch addressing
		virtual void calcAddressing();

		//- Initialise the calculation of the patch geometry
		virtual void initGeometry();

		//- Calculate the patch geometry
		virtual void calcGeometry();

		//- Initialise the patches for moving points
		virtual void initMovePoints(const pointField&);

		//- Correct patches after moving points
		virtual void movePoints(const pointField&);

		//- Initialise the update of the patch topology
		virtual void initUpdateMesh();

		//- Update of the patch topology
		virtual void updateMesh();

	public:

		//- Runtime type information
		TypeName("cyclic");


		// Constructors

			//- Construct from components
		cyclicPolyPatch
		(
			const word& name,
			const label size,
			const label start,
			const label index,
			const polyBoundaryMesh& bm
		);

		//- Construct from dictionary
		cyclicPolyPatch
		(
			const word& name,
			const dictionary& dict,
			const label index,
			const polyBoundaryMesh& bm
		);

		//- Construct as copy, resetting the boundary mesh
		cyclicPolyPatch(const cyclicPolyPatch&, const polyBoundaryMesh&);

		//- Construct given the original patch and resetting the
		//  face list and boundary mesh information
		cyclicPolyPatch
		(
			const cyclicPolyPatch& pp,
			const polyBoundaryMesh& bm,
			const label index,
			const label newSize,
			const label newStart
		);

		//- Construct and return a clone, resetting the boundary mesh
		virtual autoPtr<polyPatch> clone(const polyBoundaryMesh& bm) const
		{
			return autoPtr<polyPatch>(new cyclicPolyPatch(*this, bm));
		}

		//- Construct and return a clone, resetting the face list
		//  and boundary mesh
		virtual autoPtr<polyPatch> clone
		(
			const polyBoundaryMesh& bm,
			const label index,
			const label newSize,
			const label newStart
		) const
		{
			return autoPtr<polyPatch>
				(
					new cyclicPolyPatch(*this, bm, index, newSize, newStart)
					);
		}


		// Destructor

		virtual ~cyclicPolyPatch();


		// Member Functions

			//- Return connected points (in patch local point indexing). Demand
			//  driven calculation. Does primitivePatch::clearOut
			//  after calculation!
		const edgeList& coupledPoints() const;

		//- Return connected edges (in patch local edge indexing). Demand
		//  driven calculation. Does primitivePatch::clearOut
		//  after calculation!
		const edgeList& coupledEdges() const;



		// Transformation

		vector separation(const label facei) const
		{
			if (facei < size() / 2)
			{
				return coupledPolyPatch::separation()[0];
			}
			else
			{
				return -coupledPolyPatch::separation()[0];
			}
		}

		const tensor& transformT(const label facei) const
		{
			if (facei < size() / 2)
			{
				return reverseT()[0];
			}
			else
			{
				return forwardT()[0];
			}
		}

		template<class T>
		T transform(const T& t, const label facei) const
		{
			if (parallel())
			{
				return t;
			}
			else
			{
				return tnbLib::transform(transformT(facei), t);
			}
		}

		label transformLocalFace(const label facei) const
		{
			if (facei < size() / 2)
			{
				return facei + size() / 2;
			}
			else
			{
				return facei - size() / 2;
			}
		}

		label transformGlobalFace(const label facei) const
		{
			if (facei - start() < size() / 2)
			{
				return facei + size() / 2;
			}
			else
			{
				return facei - size() / 2;
			}
		}

		//- Type of transform
		transformType transform() const
		{
			return transform_;
		}

		//- Axis of rotation for rotational cyclics
		const vector& rotationAxis() const
		{
			return rotationAxis_;
		}

		//- point on axis of rotation for rotational cyclics
		const point& rotationCentre() const
		{
			return rotationCentre_;
		}

		//- Translation vector for translational cyclics
		const vector& separationVector() const
		{
			return separationVector_;
		}



		//- Initialize ordering for primitivePatch. Does not
		//  refer to *this (except for name() and type() etc.)
		virtual void initOrder(const primitivePatch&) const;

		//- Return new ordering for primitivePatch.
		//  Ordering is -faceMap: for every face
		//  index of the new face -rotation:for every new face the clockwise
		//  shift of the original face. Return false if nothing changes
		//  (faceMap is identity, rotation is 0), true otherwise.
		virtual bool order
		(
			const primitivePatch&,
			labelList& faceMap,
			labelList& rotation
		) const;

		//- Synchronise communications of ordering for primitivePatch
		//  Used in cases when no topological change happens locally,
		//  but is happening on other processors
		virtual void syncOrder() const;


		//- Write the polyPatch data as a dictionary
		virtual void write(Ostream&) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_cyclicPolyPatch_Header
