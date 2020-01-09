#include <transformGeometricField.hxx>

#include <transformField.hxx>
#include <transformFieldField.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * global functions  * * * * * * * * * * * * * //

	template<class Type, template<class> class PatchField, class GeoMesh>
	void transform
	(
		GeometricField<Type, PatchField, GeoMesh>& rtf,
		const GeometricField<tensor, PatchField, GeoMesh>& trf,
		const GeometricField<Type, PatchField, GeoMesh>& tf
	)
	{
		transform(rtf.internalField(), trf.internalField(), tf.internalField());
		transform(rtf.boundaryField(), trf.boundaryField(), tf.boundaryField());
	}


	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh> > transform
	(
		const GeometricField<tensor, PatchField, GeoMesh>& trf,
		const GeometricField<Type, PatchField, GeoMesh>& tf
	)
	{
		tmp<GeometricField<Type, PatchField, GeoMesh> > tranf
		(
			new GeometricField<Type, PatchField, GeoMesh>
			(
				IOobject
				(
					"transform(" + trf.name() + ',' + tf.name() + ')',
					tf.instance(),
					tf.db(),
					IOobject::NO_READ,
					IOobject::NO_WRITE
				),
				tf.mesh(),
				tf.dimensions()
				)
		);

		transform(tranf(), trf, tf);

		return tranf;
	}


	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh> > transform
	(
		const GeometricField<tensor, PatchField, GeoMesh>& trf,
		const tmp<GeometricField<Type, PatchField, GeoMesh> >& ttf
	)
	{
		tmp<GeometricField<Type, PatchField, GeoMesh> > tranf =
			transform(trf, ttf());
		ttf.clear();
		return tranf;
	}


	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh> > transform
	(
		const tmp<GeometricField<tensor, PatchField, GeoMesh> >& ttrf,
		const GeometricField<Type, PatchField, GeoMesh>& tf
	)
	{
		tmp<GeometricField<Type, PatchField, GeoMesh> > tranf =
			transform(ttrf(), tf);
		ttrf.clear();
		return tranf;
	}


	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh> > transform
	(
		const tmp<GeometricField<tensor, PatchField, GeoMesh> >& ttrf,
		const tmp<GeometricField<Type, PatchField, GeoMesh> >& ttf
	)
	{
		tmp<GeometricField<Type, PatchField, GeoMesh> > tranf =
			transform(ttrf(), ttf());
		ttf.clear();
		ttrf.clear();
		return tranf;
	}


	template<class Type, template<class> class PatchField, class GeoMesh>
	void transform
	(
		GeometricField<Type, PatchField, GeoMesh>& rtf,
		const dimensionedTensor& t,
		const GeometricField<Type, PatchField, GeoMesh>& tf
	)
	{
		transform(rtf.internalField(), t.value(), tf.internalField());
		transform(rtf.boundaryField(), t.value(), tf.boundaryField());
	}


	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh> > transform
	(
		const dimensionedTensor& t,
		const GeometricField<Type, PatchField, GeoMesh>& tf
	)
	{
		tmp<GeometricField<Type, PatchField, GeoMesh> > tranf
		(
			new GeometricField<vector, PatchField, GeoMesh>
			(
				IOobject
				(
					"transform(" + t.name() + ',' + tf.name() + ')',
					tf.instance(),
					tf.db(),
					IOobject::NO_READ,
					IOobject::NO_WRITE
				),
				tf.mesh(),
				tf.dimensions()
				)
		);

		transform(tranf(), t, tf);

		return tranf;
	}


	template<class Type, template<class> class PatchField, class GeoMesh>
	tmp<GeometricField<Type, PatchField, GeoMesh> > transform
	(
		const dimensionedTensor& t,
		const tmp<GeometricField<Type, PatchField, GeoMesh> >& ttf
	)
	{
		tmp<GeometricField<Type, PatchField, GeoMesh> > tranf =
			transform(t, ttf());
		ttf.clear();
		return tranf;
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //