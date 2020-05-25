#pragma once
#ifndef _wedgeFvPatchVectorNFields_Header
#define _wedgeFvPatchVectorNFields_Header

#include <volVectorNFields.hxx>
#include <fvPatchVectorNFields.hxx>

#include <wedgeFvPatchVectorNFieldsFwd.hxx>
#include <wedgeFvPatchField.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#define doMakeVectorTensorNWedgeFuncDefs(type, Type, args)       \
template<>                                                          \
tmp<Field<type > > wedgeFvPatchField<type >::snGrad() const;        \
                                                                    \
template<>                                                          \
void wedgeFvPatchField<type >::evaluate                             \
(                                                                   \
    const Pstream::commsTypes commsType                             \
);                                                                  \
                                                                    \
template<>                                                          \
tmp<Field<type > >                                                  \
wedgeFvPatchField<type >::snGradTransformDiag() const;

	forAllVectorNTypes(doMakeVectorTensorNWedgeFuncDefs)

		forAllTensorNTypes(doMakeVectorTensorNWedgeFuncDefs)

		forAllDiagTensorNTypes(doMakeVectorTensorNWedgeFuncDefs)

		forAllSphericalTensorNTypes(doMakeVectorTensorNWedgeFuncDefs)

#undef doMakeVectorTensorNWedgeFuncDefs

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_wedgeFvPatchVectorNFields_Header
