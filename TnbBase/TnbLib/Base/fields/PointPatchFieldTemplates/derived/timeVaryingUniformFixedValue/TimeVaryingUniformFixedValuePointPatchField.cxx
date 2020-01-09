#include <TimeVaryingUniformFixedValuePointPatchField.hxx>

#include <tnbTime.hxx>
#include <IFstream.hxx>
#include <error.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	template
		<
		template<class> class PatchField,
		class Mesh,
		class PointPatch,
		template<class> class MatrixType,
		class Type
		>
		TimeVaryingUniformFixedValuePointPatchField
		<PatchField, Mesh, PointPatch, MatrixType, Type>::
		TimeVaryingUniformFixedValuePointPatchField
		(
			const PointPatch& p,
			const DimensionedField<Type, Mesh>& iF
		)
		:
		FixedValuePointPatchField
		<PatchField, Mesh, PointPatch, MatrixType, Type>(p, iF)
	{}


	template
		<
		template<class> class PatchField,
		class Mesh,
		class PointPatch,
		template<class> class MatrixType,
		class Type
		>
		TimeVaryingUniformFixedValuePointPatchField
		<PatchField, Mesh, PointPatch, MatrixType, Type>::
		TimeVaryingUniformFixedValuePointPatchField
		(
			const PointPatch& p,
			const DimensionedField<Type, Mesh>& iF,
			const dictionary& dict
		)
		:
		FixedValuePointPatchField
		<PatchField, Mesh, PointPatch, MatrixType, Type>(p, iF),
		timeSeries_(dict)
	{}


	template
		<
		template<class> class PatchField,
		class Mesh,
		class PointPatch,
		template<class> class MatrixType,
		class Type
		>
		TimeVaryingUniformFixedValuePointPatchField
		<PatchField, Mesh, PointPatch, MatrixType, Type>::
		TimeVaryingUniformFixedValuePointPatchField
		(
			const
			TimeVaryingUniformFixedValuePointPatchField
			<PatchField, Mesh, PointPatch, MatrixType, Type>& ptf,
			const PointPatch& p,
			const DimensionedField<Type, Mesh>& iF,
			const PointPatchFieldMapper& mapper
		)
		:
		FixedValuePointPatchField
		<PatchField, Mesh, PointPatch, MatrixType, Type>(p, iF),
		timeSeries_(ptf.timeSeries_)
	{}


	template
		<
		template<class> class PatchField,
		class Mesh,
		class PointPatch,
		template<class> class MatrixType,
		class Type
		>
		TimeVaryingUniformFixedValuePointPatchField
		<PatchField, Mesh, PointPatch, MatrixType, Type>::
		TimeVaryingUniformFixedValuePointPatchField
		(
			const TimeVaryingUniformFixedValuePointPatchField
			<PatchField, Mesh, PointPatch, MatrixType, Type>& ptf
		)
		:
		FixedValuePointPatchField
		<PatchField, Mesh, PointPatch, MatrixType, Type>(ptf),
		timeSeries_(ptf.timeSeries_)
	{}


	template
		<
		template<class> class PatchField,
		class Mesh,
		class PointPatch,
		template<class> class MatrixType,
		class Type
		>
		TimeVaryingUniformFixedValuePointPatchField
		<PatchField, Mesh, PointPatch, MatrixType, Type>::
		TimeVaryingUniformFixedValuePointPatchField
		(
			const TimeVaryingUniformFixedValuePointPatchField
			<PatchField, Mesh, PointPatch, MatrixType, Type>& ptf,
			const DimensionedField<Type, Mesh>& iF
		)
		:
		FixedValuePointPatchField
		<PatchField, Mesh, PointPatch, MatrixType, Type>(ptf, iF),
		timeSeries_(ptf.timeSeries_)
	{}


	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	template
		<
		template<class> class PatchField,
		class Mesh,
		class PointPatch,
		template<class> class MatrixType,
		class Type
		>
		void
		TimeVaryingUniformFixedValuePointPatchField
		<PatchField, Mesh, PointPatch, MatrixType, Type>::
		initEvaluate
		(
			const Pstream::commsTypes commsType
		)
	{
		Field<Type>& patchField = *this;

		patchField = timeSeries_(this->db().time().timeOutputValue());

		FixedValuePointPatchField
			<PatchField, Mesh, PointPatch, MatrixType, Type>::
			initEvaluate(commsType);
	}


	// Write
	template
		<
		template<class> class PatchField,
		class Mesh,
		class PointPatch,
		template<class> class MatrixType,
		class Type
		>
		void TimeVaryingUniformFixedValuePointPatchField
		<PatchField, Mesh, PointPatch, MatrixType, Type>::write(Ostream& os) const
	{
		PatchField<Type>::write(os);
		timeSeries_.write(os);
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //