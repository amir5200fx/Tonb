#include <wedgeFvPatchVectorNFields.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

#define makeVectorTensorNWedgeFuncDefs(Type)                                  \
template<>                                                                    \
tmp<Field<Type> > wedgeFvPatchField<Type>::snGrad() const                     \
{                                                                             \
    return tmp<Field<Type> >                                                  \
    (                                                                         \
        new Field<Type>(size(), pTraits<Type>::zero)                          \
    );                                                                        \
}                                                                             \
                                                                              \
template<>                                                                    \
void wedgeFvPatchField<Type>::evaluate                                        \
(                                                                             \
    const Pstream::commsTypes commsType                                       \
)                                                                             \
{                                                                             \
    if (!updated())                                                           \
    {                                                                         \
        updateCoeffs();                                                       \
    }                                                                         \
                                                                              \
    this->operator==(patchInternalField());                                   \
}                                                                             \
                                                                              \
template<>                                                                    \
tmp<Field<Type> > wedgeFvPatchField<Type>::snGradTransformDiag()              \
const                                                                         \
{                                                                             \
    return tmp<Field<Type> >                                                  \
    (                                                                         \
        new Field<Type>(this->size(), pTraits<Type>::zero)                    \
    );                                                                        \
}


#define doMakePatchTypeField(type, Type, args)                             \
                                                                              \
makeVectorTensorNWedgeFuncDefs(type)                                          \
                                                                              \
makeTemplatePatchTypeField                                                    \
(                                                                             \
    fvPatch##Type##Field,                                                     \
    wedgeFvPatch##Type##Field                                                 \
);


	forAllVectorNTypes(doMakePatchTypeField)

		forAllTensorNTypes(doMakePatchTypeField)

		forAllDiagTensorNTypes(doMakePatchTypeField)

		forAllSphericalTensorNTypes(doMakePatchTypeField)


#undef doMakePatchTypeField

#undef makeVectorTensorNWedgeFuncDefs

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //