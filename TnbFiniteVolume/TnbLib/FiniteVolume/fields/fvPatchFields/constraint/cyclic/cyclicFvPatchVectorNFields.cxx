#include <cyclicFvPatchVectorNFields.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <fvPatchVectorNFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

#define VectorNMatrixInterfaceFunc(Type)                                      \
template<>                                                                    \
void cyclicFvPatchField<Type>::updateInterfaceMatrix                          \
(                                                                             \
    const Field<Type>& psiInternal,                                           \
    Field<Type>& result,                                                      \
    const BlockLduMatrix<Type>&,                                              \
    const CoeffField<Type>& coeffs,                                           \
    const Pstream::commsTypes commsType,                                      \
    const bool switchToLhs                                                    \
) const                                                                       \
{                                                                             \
    Field<Type> pnf(this->size());                                            \
                                                                              \
    label sizeby2 = this->size()/2;                                           \
    const unallocLabelList& faceCells = cyclicPatch_.faceCells();             \
                                                                              \
    for (label facei=0; facei<sizeby2; facei++)                               \
    {                                                                         \
        pnf[facei] = psiInternal[faceCells[facei + sizeby2]];                 \
        pnf[facei + sizeby2] = psiInternal[faceCells[facei]];                 \
    }                                                                         \
                                                                              \
    if (coeffs.activeType() == blockCoeffBase::SCALAR)                        \
    {                                                                         \
        pnf = coeffs.asScalar() * pnf;                                        \
    }                                                                         \
    else if (coeffs.activeType() == blockCoeffBase::LINEAR)                   \
    {                                                                         \
        pnf = cmptMultiply(coeffs.asLinear(), pnf);                           \
    }                                                                         \
    else if (coeffs.activeType() == blockCoeffBase::SQUARE)                   \
    {                                                                         \
        pnf = coeffs.asSquare() & pnf;                                        \
    }                                                                         \
                                                                              \
    if (switchToLhs)                                                          \
    {                                                                         \
        forAll(faceCells, elemI)                                              \
        {                                                                     \
            result[faceCells[elemI]] += pnf[elemI];                           \
        }                                                                     \
    }                                                                         \
    else                                                                      \
    {                                                                         \
        forAll(faceCells, elemI)                                              \
        {                                                                     \
            result[faceCells[elemI]] -= pnf[elemI];                           \
        }                                                                     \
    }                                                                         \
}


#define doMakePatchTypeField(type, Type, args)                             \
                                                                              \
VectorNMatrixInterfaceFunc(type)                                              \
                                                                              \
makeTemplatePatchTypeField                                                    \
(                                                                             \
    fvPatch##Type##Field,                                                     \
    cyclicFvPatch##Type##Field                                                \
);

	template <>
	void cyclicFvPatchField<vector2>::updateInterfaceMatrix(const Field<vector2>& psiInternal, Field<vector2>& result,
	                                                        const BlockLduMatrix<vector2>&,
	                                                        const CoeffField<vector2>& coeffs,
	                                                        const Pstream::commsTypes commsType,
	                                                        const bool switchToLhs) const
	{
		Field<vector2> pnf(this->size());
		label sizeby2 = this->size() / 2;
		const unallocLabelList& faceCells = cyclicPatch_.faceCells();
		for (label facei = 0; facei < sizeby2; facei++)
		{
			pnf[facei] = psiInternal[faceCells[facei + sizeby2]];
			pnf[facei + sizeby2] = psiInternal[faceCells[facei]];
		}
		if (coeffs.activeType() == blockCoeffBase::SCALAR) { pnf = coeffs.asScalar() * pnf; }
		else if (coeffs.activeType() == blockCoeffBase::LINEAR) { pnf = cmptMultiply(coeffs.asLinear(), pnf); }
		else if (coeffs.activeType() == blockCoeffBase::SQUARE) { pnf = coeffs.asSquare() & pnf; }
		if (switchToLhs)
		{
			for (tnbLib::label elemI = 0; elemI < (faceCells).size(); elemI++) { result[faceCells[elemI]] += pnf[elemI]; }
		}
		else
		{
			for (tnbLib::label elemI = 0; elemI < (faceCells).size(); elemI++) { result[faceCells[elemI]] -= pnf[elemI]; }
		}
	}

	template <>
	const ::tnbLib::word cyclicFvPatchVector2Field::typeName(cyclicFvPatchVector2Field::typeName_());
	template <>
	::tnbLib::debug::debugSwitch cyclicFvPatchVector2Field::debug(std::string(cyclicFvPatchVector2Field::typeName_()), 0,
	                                                              "");;
	fvPatchVector2Field::addpatchConstructorToTable<cyclicFvPatchVector2Field>
	addcyclicFvPatchVector2FieldpatchConstructorTofvPatchVector2FieldTable_;
	fvPatchVector2Field::addpatchMapperConstructorToTable<cyclicFvPatchVector2Field>
	addcyclicFvPatchVector2FieldpatchMapperConstructorTofvPatchVector2FieldTable_;
	fvPatchVector2Field::adddictionaryConstructorToTable<cyclicFvPatchVector2Field>
	addcyclicFvPatchVector2FielddictionaryConstructorTofvPatchVector2FieldTable_;;;

	template <>
	void cyclicFvPatchField<vector3>::updateInterfaceMatrix(const Field<vector3>& psiInternal, Field<vector3>& result,
	                                                        const BlockLduMatrix<vector3>&,
	                                                        const CoeffField<vector3>& coeffs,
	                                                        const Pstream::commsTypes commsType,
	                                                        const bool switchToLhs) const
	{
		Field<vector3> pnf(this->size());
		label sizeby2 = this->size() / 2;
		const unallocLabelList& faceCells = cyclicPatch_.faceCells();
		for (label facei = 0; facei < sizeby2; facei++)
		{
			pnf[facei] = psiInternal[faceCells[facei + sizeby2]];
			pnf[facei + sizeby2] = psiInternal[faceCells[facei]];
		}
		if (coeffs.activeType() == blockCoeffBase::SCALAR) { pnf = coeffs.asScalar() * pnf; }
		else if (coeffs.activeType() == blockCoeffBase::LINEAR) { pnf = cmptMultiply(coeffs.asLinear(), pnf); }
		else if (coeffs.activeType() == blockCoeffBase::SQUARE) { pnf = coeffs.asSquare() & pnf; }
		if (switchToLhs)
		{
			for (tnbLib::label elemI = 0; elemI < (faceCells).size(); elemI++) { result[faceCells[elemI]] += pnf[elemI]; }
		}
		else
		{
			for (tnbLib::label elemI = 0; elemI < (faceCells).size(); elemI++) { result[faceCells[elemI]] -= pnf[elemI]; }
		}
	}

	template <>
	const ::tnbLib::word cyclicFvPatchVector3Field::typeName(cyclicFvPatchVector3Field::typeName_());
	template <>
	::tnbLib::debug::debugSwitch cyclicFvPatchVector3Field::debug(std::string(cyclicFvPatchVector3Field::typeName_()), 0,
	                                                              "");;
	fvPatchVector3Field::addpatchConstructorToTable<cyclicFvPatchVector3Field>
	addcyclicFvPatchVector3FieldpatchConstructorTofvPatchVector3FieldTable_;
	fvPatchVector3Field::addpatchMapperConstructorToTable<cyclicFvPatchVector3Field>
	addcyclicFvPatchVector3FieldpatchMapperConstructorTofvPatchVector3FieldTable_;
	fvPatchVector3Field::adddictionaryConstructorToTable<cyclicFvPatchVector3Field>
	addcyclicFvPatchVector3FielddictionaryConstructorTofvPatchVector3FieldTable_;;;

	template <>
	void cyclicFvPatchField<vector4>::updateInterfaceMatrix(const Field<vector4>& psiInternal, Field<vector4>& result,
	                                                        const BlockLduMatrix<vector4>&,
	                                                        const CoeffField<vector4>& coeffs,
	                                                        const Pstream::commsTypes commsType,
	                                                        const bool switchToLhs) const
	{
		Field<vector4> pnf(this->size());
		label sizeby2 = this->size() / 2;
		const unallocLabelList& faceCells = cyclicPatch_.faceCells();
		for (label facei = 0; facei < sizeby2; facei++)
		{
			pnf[facei] = psiInternal[faceCells[facei + sizeby2]];
			pnf[facei + sizeby2] = psiInternal[faceCells[facei]];
		}
		if (coeffs.activeType() == blockCoeffBase::SCALAR) { pnf = coeffs.asScalar() * pnf; }
		else if (coeffs.activeType() == blockCoeffBase::LINEAR) { pnf = cmptMultiply(coeffs.asLinear(), pnf); }
		else if (coeffs.activeType() == blockCoeffBase::SQUARE) { pnf = coeffs.asSquare() & pnf; }
		if (switchToLhs)
		{
			for (tnbLib::label elemI = 0; elemI < (faceCells).size(); elemI++) { result[faceCells[elemI]] += pnf[elemI]; }
		}
		else
		{
			for (tnbLib::label elemI = 0; elemI < (faceCells).size(); elemI++) { result[faceCells[elemI]] -= pnf[elemI]; }
		}
	}

	template <>
	const ::tnbLib::word cyclicFvPatchVector4Field::typeName(cyclicFvPatchVector4Field::typeName_());
	template <>
	::tnbLib::debug::debugSwitch cyclicFvPatchVector4Field::debug(std::string(cyclicFvPatchVector4Field::typeName_()), 0,
	                                                              "");;
	fvPatchVector4Field::addpatchConstructorToTable<cyclicFvPatchVector4Field>
	addcyclicFvPatchVector4FieldpatchConstructorTofvPatchVector4FieldTable_;
	fvPatchVector4Field::addpatchMapperConstructorToTable<cyclicFvPatchVector4Field>
	addcyclicFvPatchVector4FieldpatchMapperConstructorTofvPatchVector4FieldTable_;
	fvPatchVector4Field::adddictionaryConstructorToTable<cyclicFvPatchVector4Field>
	addcyclicFvPatchVector4FielddictionaryConstructorTofvPatchVector4FieldTable_;;;

	template <>
	void cyclicFvPatchField<vector6>::updateInterfaceMatrix(const Field<vector6>& psiInternal, Field<vector6>& result,
	                                                        const BlockLduMatrix<vector6>&,
	                                                        const CoeffField<vector6>& coeffs,
	                                                        const Pstream::commsTypes commsType,
	                                                        const bool switchToLhs) const
	{
		Field<vector6> pnf(this->size());
		label sizeby2 = this->size() / 2;
		const unallocLabelList& faceCells = cyclicPatch_.faceCells();
		for (label facei = 0; facei < sizeby2; facei++)
		{
			pnf[facei] = psiInternal[faceCells[facei + sizeby2]];
			pnf[facei + sizeby2] = psiInternal[faceCells[facei]];
		}
		if (coeffs.activeType() == blockCoeffBase::SCALAR) { pnf = coeffs.asScalar() * pnf; }
		else if (coeffs.activeType() == blockCoeffBase::LINEAR) { pnf = cmptMultiply(coeffs.asLinear(), pnf); }
		else if (coeffs.activeType() == blockCoeffBase::SQUARE) { pnf = coeffs.asSquare() & pnf; }
		if (switchToLhs)
		{
			for (tnbLib::label elemI = 0; elemI < (faceCells).size(); elemI++) { result[faceCells[elemI]] += pnf[elemI]; }
		}
		else
		{
			for (tnbLib::label elemI = 0; elemI < (faceCells).size(); elemI++) { result[faceCells[elemI]] -= pnf[elemI]; }
		}
	}

	template <>
	const ::tnbLib::word cyclicFvPatchVector6Field::typeName(cyclicFvPatchVector6Field::typeName_());
	template <>
	::tnbLib::debug::debugSwitch cyclicFvPatchVector6Field::debug(std::string(cyclicFvPatchVector6Field::typeName_()), 0,
	                                                              "");;
	fvPatchVector6Field::addpatchConstructorToTable<cyclicFvPatchVector6Field>
	addcyclicFvPatchVector6FieldpatchConstructorTofvPatchVector6FieldTable_;
	fvPatchVector6Field::addpatchMapperConstructorToTable<cyclicFvPatchVector6Field>
	addcyclicFvPatchVector6FieldpatchMapperConstructorTofvPatchVector6FieldTable_;
	fvPatchVector6Field::adddictionaryConstructorToTable<cyclicFvPatchVector6Field>
	addcyclicFvPatchVector6FielddictionaryConstructorTofvPatchVector6FieldTable_;;;

	template <>
	void cyclicFvPatchField<vector8>::updateInterfaceMatrix(const Field<vector8>& psiInternal, Field<vector8>& result,
	                                                        const BlockLduMatrix<vector8>&,
	                                                        const CoeffField<vector8>& coeffs,
	                                                        const Pstream::commsTypes commsType,
	                                                        const bool switchToLhs) const
	{
		Field<vector8> pnf(this->size());
		label sizeby2 = this->size() / 2;
		const unallocLabelList& faceCells = cyclicPatch_.faceCells();
		for (label facei = 0; facei < sizeby2; facei++)
		{
			pnf[facei] = psiInternal[faceCells[facei + sizeby2]];
			pnf[facei + sizeby2] = psiInternal[faceCells[facei]];
		}
		if (coeffs.activeType() == blockCoeffBase::SCALAR) { pnf = coeffs.asScalar() * pnf; }
		else if (coeffs.activeType() == blockCoeffBase::LINEAR) { pnf = cmptMultiply(coeffs.asLinear(), pnf); }
		else if (coeffs.activeType() == blockCoeffBase::SQUARE) { pnf = coeffs.asSquare() & pnf; }
		if (switchToLhs)
		{
			for (tnbLib::label elemI = 0; elemI < (faceCells).size(); elemI++) { result[faceCells[elemI]] += pnf[elemI]; }
		}
		else
		{
			for (tnbLib::label elemI = 0; elemI < (faceCells).size(); elemI++) { result[faceCells[elemI]] -= pnf[elemI]; }
		}
	}

	template <>
	const ::tnbLib::word cyclicFvPatchVector8Field::typeName(cyclicFvPatchVector8Field::typeName_());
	template <>
	::tnbLib::debug::debugSwitch cyclicFvPatchVector8Field::debug(std::string(cyclicFvPatchVector8Field::typeName_()), 0,
	                                                              "");;
	fvPatchVector8Field::addpatchConstructorToTable<cyclicFvPatchVector8Field>
	addcyclicFvPatchVector8FieldpatchConstructorTofvPatchVector8FieldTable_;
	fvPatchVector8Field::addpatchMapperConstructorToTable<cyclicFvPatchVector8Field>
	addcyclicFvPatchVector8FieldpatchMapperConstructorTofvPatchVector8FieldTable_;
	fvPatchVector8Field::adddictionaryConstructorToTable<cyclicFvPatchVector8Field>
	addcyclicFvPatchVector8FielddictionaryConstructorTofvPatchVector8FieldTable_;;;

#undef doMakePatchTypeField

#undef VectorNMatrixInterfaceFunc

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //