#include <vectorField.hxx>

#define TEMPLATE
#include <FieldFunctionsM.cxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * Global Functions  * * * * * * * * * * * * * //

	TEMPLATE void scaleRow ( Field<vector>& res, const UList<vector>& f1, const UList<scalar>& f2 )
	{
		TFOR_ALL_F_OP_FUNC_F_F ( vector, res, =, ::tnbLib::scaleRow, vector, f1, scalar, f2 )
	} 
	TEMPLATE tmp<Field<vector>> scaleRow ( const UList<vector>& f1, const UList<scalar>& f2 )
	{
		tmp<Field<vector>> tRes(new Field<vector>(f1.size())); scaleRow(tRes(), f1, f2); return tRes;
	} 
	TEMPLATE tmp<Field<vector>> scaleRow ( const UList<vector>& f1, const tmp<Field<scalar>>& tf2 )
	{
		tmp<Field<vector>> tRes = reuseTmp<vector, scalar>::New(tf2); scaleRow(tRes(), f1, tf2()); reuseTmp<vector, scalar>::clear(tf2); return tRes;
	} 
	TEMPLATE tmp<Field<vector>> scaleRow ( const tmp<Field<vector>>& tf1, const UList<scalar>& f2 )
	{
		tmp<Field<vector>> tRes = reuseTmp<vector, vector>::New(tf1); scaleRow(tRes(), tf1(), f2); reuseTmp<vector, vector>::clear(tf1); return tRes;
	} 
	TEMPLATE tmp<Field<vector>> scaleRow ( const tmp<Field<vector>>& tf1, const tmp<Field<scalar>>& tf2 )
	{
		tmp<Field<vector>> tRes = reuseTmpTmp<vector, vector, vector, scalar>::New(tf1, tf2); 
		scaleRow(tRes(), tf1(), tf2()); reuseTmpTmp<vector, vector, vector, scalar>::clear(tf1, tf2); 
		return tRes;
	}
		
	TEMPLATE void scaleRow ( Field<vector>& res, const vector& s1, const UList<scalar>& f2 )
	{
		TFOR_ALL_F_OP_FUNC_S_F ( vector, res, =, ::tnbLib::scaleRow, vector, s1, scalar, f2 )
	} 
	TEMPLATE tmp<Field<vector>> scaleRow ( const vector& s1, const UList<scalar>& f2 )
	{
		tmp<Field<vector>> tRes(new Field<vector>(f2.size())); scaleRow(tRes(), s1, f2); return tRes;
	} 
	TEMPLATE tmp<Field<vector>> scaleRow ( const vector& s1, const tmp<Field<scalar>>& tf2 )
	{
		tmp<Field<vector>> tRes = reuseTmp<vector, scalar>::New(tf2); scaleRow(tRes(), s1, tf2()); reuseTmp<vector, scalar>::clear(tf2); return tRes;
	} 
	
	TEMPLATE void scaleRow ( Field<vector>& res, const UList<vector>& f1, const scalar& s2 )
	{
		TFOR_ALL_F_OP_FUNC_F_S ( vector, res, =, ::tnbLib::scaleRow, vector, f1, scalar, s2 )
	} 
	TEMPLATE tmp<Field<vector>> scaleRow ( const UList<vector>& f1, const scalar& s2 )
	{
		tmp<Field<vector>> tRes(new Field<vector>(f1.size())); scaleRow(tRes(), f1, s2); return tRes;
	} 
	TEMPLATE tmp<Field<vector>> scaleRow ( const tmp<Field<vector>>& tf1, const scalar& s2 )
	{
		tmp<Field<vector>> tRes = reuseTmp<vector, vector>::New(tf1); scaleRow(tRes(), tf1(), s2); reuseTmp<vector, vector>::clear(tf1); return tRes;
	}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <undefFieldFunctionsM.hxx>