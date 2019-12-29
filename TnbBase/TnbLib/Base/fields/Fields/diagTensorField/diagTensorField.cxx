#include <diagTensorField.hxx>

#include <transformField.hxx>

#define TEMPLATE
#include <FieldFunctionsM.cxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * global functions  * * * * * * * * * * * * * //

	TEMPLATE void diag(Field<diagTensor>& res, const UList<tensor>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(diagTensor, res, =, ::tnbLib::diag, tensor, f)
	} 
	TEMPLATE tmp<Field<diagTensor>> diag(const UList<tensor>& f)
	{
		tmp<Field<diagTensor>> tRes(new Field<diagTensor>(f.size())); diag(tRes(), f); return tRes;
	} 
	TEMPLATE tmp<Field<diagTensor>> diag(const tmp<Field<tensor>>& tf)
	{
		tmp<Field<diagTensor>> tRes = reuseTmp<diagTensor, tensor>::New(tf); diag(tRes(), tf()); reuseTmp<diagTensor, tensor>::clear(tf); return tRes;
	}
		
	TEMPLATE void tr(Field<scalar>& res, const UList<diagTensor>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(scalar, res, =, ::tnbLib::tr, diagTensor, f)
	} 
	TEMPLATE tmp<Field<scalar>> tr(const UList<diagTensor>& f)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f.size())); tr(tRes(), f); return tRes;
	} 
	TEMPLATE tmp<Field<scalar>> tr(const tmp<Field<diagTensor>>& tf)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, diagTensor>::New(tf); tr(tRes(), tf()); reuseTmp<scalar, diagTensor>::clear(tf); return tRes;
	}
		
	TEMPLATE void sph(Field<sphericalTensor>& res, const UList<diagTensor>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(sphericalTensor, res, =, ::tnbLib::sph, diagTensor, f)
	} 
	TEMPLATE tmp<Field<sphericalTensor>> sph(const UList<diagTensor>& f)
	{
		tmp<Field<sphericalTensor>> tRes(new Field<sphericalTensor>(f.size())); sph(tRes(), f); return tRes;
	} 
	TEMPLATE tmp<Field<sphericalTensor>> sph(const tmp<Field<diagTensor>>& tf)
	{
		tmp<Field<sphericalTensor>> tRes = reuseTmp<sphericalTensor, diagTensor>::New(tf); sph(tRes(), tf()); reuseTmp<sphericalTensor, diagTensor>::clear(tf); return tRes;
	}
		
	TEMPLATE void det(Field<scalar>& res, const UList<diagTensor>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(scalar, res, =, ::tnbLib::det, diagTensor, f)
	} 
	TEMPLATE tmp<Field<scalar>> det(const UList<diagTensor>& f)
	{
		tmp<Field<scalar>> tRes(new Field<scalar>(f.size())); det(tRes(), f); return tRes;
	} 
	TEMPLATE tmp<Field<scalar>> det(const tmp<Field<diagTensor>>& tf)
	{
		tmp<Field<scalar>> tRes = reuseTmp<scalar, diagTensor>::New(tf); det(tRes(), tf()); reuseTmp<scalar, diagTensor>::clear(tf); return tRes;
	}
		
	TEMPLATE void inv(Field<diagTensor>& res, const UList<diagTensor>& f)
	{
		TFOR_ALL_F_OP_FUNC_F(diagTensor, res, =, ::tnbLib::inv, diagTensor, f)
	} 
	TEMPLATE tmp<Field<diagTensor>> inv(const UList<diagTensor>& f)
	{
		tmp<Field<diagTensor>> tRes(new Field<diagTensor>(f.size())); inv(tRes(), f); return tRes;
	}
	TEMPLATE tmp<Field<diagTensor>> inv(const tmp<Field<diagTensor>>& tf)
	{
		tmp<Field<diagTensor>> tRes = reuseTmp<diagTensor, diagTensor>::New(tf); inv(tRes(), tf()); reuseTmp<diagTensor, diagTensor>::clear(tf); return tRes;
	}


		
	TEMPLATE void add ( Field<tensor>& res, const UList<diagTensor>& f1, const UList<tensor>& f2 )
	{
		TFOR_ALL_F_OP_F_OP_F(tensor, res, =, diagTensor, f1, +, tensor, f2)
	} 
	TEMPLATE tmp<Field<tensor>> operator + ( const UList<diagTensor>& f1, const UList<tensor>& f2 )
	{
		tmp<Field<tensor>> tRes(new Field<tensor>(f1.size())); add(tRes(), f1, f2); return tRes;
	} 
	TEMPLATE tmp<Field<tensor>> operator + ( const UList<diagTensor>& f1, const tmp<Field<tensor>>& tf2 )
	{
		tmp<Field<tensor>> tRes = reuseTmp<tensor, tensor>::New(tf2); add(tRes(), f1, tf2()); reuseTmp<tensor, tensor>::clear(tf2); return tRes;
	} 
	TEMPLATE tmp<Field<tensor>> operator + ( const tmp<Field<diagTensor>>& tf1, const UList<tensor>& f2 )
	{
		tmp<Field<tensor>> tRes = reuseTmp<tensor, diagTensor>::New(tf1); add(tRes(), tf1(), f2); reuseTmp<tensor, diagTensor>::clear(tf1); return tRes;
	} 
	TEMPLATE tmp<Field<tensor>> operator + ( const tmp<Field<diagTensor>>& tf1, const tmp<Field<tensor>>& tf2 )
	{
		tmp<Field<tensor>> tRes = reuseTmpTmp<tensor, diagTensor, diagTensor, tensor>::New(tf1, tf2); add(tRes(), tf1(), tf2()); reuseTmpTmp<tensor, diagTensor, diagTensor, tensor>::clear(tf1, tf2); return tRes;
	}
		
	TEMPLATE void subtract ( Field<tensor>& res, const UList<diagTensor>& f1, const UList<tensor>& f2 )
	{
		TFOR_ALL_F_OP_F_OP_F(tensor, res, =, diagTensor, f1, -, tensor, f2)
	} 
	TEMPLATE tmp<Field<tensor>> operator - ( const UList<diagTensor>& f1, const UList<tensor>& f2 )
	{
		tmp<Field<tensor>> tRes(new Field<tensor>(f1.size())); subtract(tRes(), f1, f2); return tRes;
	} 
	TEMPLATE tmp<Field<tensor>> operator - ( const UList<diagTensor>& f1, const tmp<Field<tensor>>& tf2 )
	{
		tmp<Field<tensor>> tRes = reuseTmp<tensor, tensor>::New(tf2); subtract(tRes(), f1, tf2()); reuseTmp<tensor, tensor>::clear(tf2); return tRes;
	} 
	TEMPLATE tmp<Field<tensor>> operator - ( const tmp<Field<diagTensor>>& tf1, const UList<tensor>& f2 )
	{
		tmp<Field<tensor>> tRes = reuseTmp<tensor, diagTensor>::New(tf1); subtract(tRes(), tf1(), f2); reuseTmp<tensor, diagTensor>::clear(tf1); return tRes;
	} 
	TEMPLATE tmp<Field<tensor>> operator - ( const tmp<Field<diagTensor>>& tf1, const tmp<Field<tensor>>& tf2 )
	{
		tmp<Field<tensor>> tRes = reuseTmpTmp<tensor, diagTensor, diagTensor, tensor>::New(tf1, tf2); subtract(tRes(), tf1(), tf2()); reuseTmpTmp<tensor, diagTensor, diagTensor, tensor>::clear(tf1, tf2); return tRes;
	}

		
	TEMPLATE void add ( Field<tensor>& res, const diagTensor& s1, const UList<tensor>& f2 )
	{
		TFOR_ALL_F_OP_S_OP_F(tensor, res, =, diagTensor, s1, +, tensor, f2)
	} 
	TEMPLATE tmp<Field<tensor>> operator + ( const diagTensor& s1, const UList<tensor>& f2 )
	{
		tmp<Field<tensor>> tRes(new Field<tensor>(f2.size())); add(tRes(), s1, f2); return tRes;
	} 
	TEMPLATE tmp<Field<tensor>> operator + ( const diagTensor& s1, const tmp<Field<tensor>>& tf2 )
	{
		tmp<Field<tensor>> tRes = reuseTmp<tensor, tensor>::New(tf2); add(tRes(), s1, tf2()); reuseTmp<tensor, tensor>::clear(tf2); return tRes;
	} 
	TEMPLATE void add ( Field<tensor>& res, const UList<diagTensor>& f1, const tensor& s2 )
	{
		TFOR_ALL_F_OP_F_OP_S(tensor, res, =, diagTensor, f1, +, tensor, s2)
	} 
	TEMPLATE tmp<Field<tensor>> operator + ( const UList<diagTensor>& f1, const tensor& s2 )
	{
		tmp<Field<tensor>> tRes(new Field<tensor>(f1.size())); add(tRes(), f1, s2); return tRes;
	} 
	TEMPLATE tmp<Field<tensor>> operator + ( const tmp<Field<diagTensor>>& tf1, const tensor& s2 )
	{
		tmp<Field<tensor>> tRes = reuseTmp<tensor, diagTensor>::New(tf1); add(tRes(), tf1(), s2); reuseTmp<tensor, diagTensor>::clear(tf1); return tRes;
	}
		
	TEMPLATE void subtract ( Field<tensor>& res, const diagTensor& s1, const UList<tensor>& f2 )
	{
		TFOR_ALL_F_OP_S_OP_F(tensor, res, =, diagTensor, s1, -, tensor, f2)
	} 
	TEMPLATE tmp<Field<tensor>> operator - ( const diagTensor& s1, const UList<tensor>& f2 )
	{
		tmp<Field<tensor>> tRes(new Field<tensor>(f2.size())); subtract(tRes(), s1, f2); return tRes;
	} 
	TEMPLATE tmp<Field<tensor>> operator - ( const diagTensor& s1, const tmp<Field<tensor>>& tf2 )
	{
		tmp<Field<tensor>> tRes = reuseTmp<tensor, tensor>::New(tf2); subtract(tRes(), s1, tf2()); reuseTmp<tensor, tensor>::clear(tf2); return tRes;
	} 
	TEMPLATE void subtract ( Field<tensor>& res, const UList<diagTensor>& f1, const tensor& s2 )
	{
		TFOR_ALL_F_OP_F_OP_S(tensor, res, =, diagTensor, f1, -, tensor, s2)
	} 
	TEMPLATE tmp<Field<tensor>> operator - ( const UList<diagTensor>& f1, const tensor& s2 )
	{
		tmp<Field<tensor>> tRes(new Field<tensor>(f1.size())); subtract(tRes(), f1, s2); return tRes;
	} 
	TEMPLATE tmp<Field<tensor>> operator - ( const tmp<Field<diagTensor>>& tf1, const tensor& s2 )
	{
		tmp<Field<tensor>> tRes = reuseTmp<tensor, diagTensor>::New(tf1); subtract(tRes(), tf1(), s2); reuseTmp<tensor, diagTensor>::clear(tf1); return tRes;
	}

		
	TEMPLATE void divide ( Field<vector>& res, const UList<vector>& f1, const UList<diagTensor>& f2 )
	{
		TFOR_ALL_F_OP_F_OP_F(vector, res, =, vector, f1, /, diagTensor, f2)
	} 
	TEMPLATE tmp<Field<vector>> operator / ( const UList<vector>& f1, const UList<diagTensor>& f2 )
	{
		tmp<Field<vector>> tRes(new Field<vector>(f1.size())); divide(tRes(), f1, f2); return tRes;
	} 
	TEMPLATE tmp<Field<vector>> operator / ( const UList<vector>& f1, const tmp<Field<diagTensor>>& tf2 )
	{
		tmp<Field<vector>> tRes = reuseTmp<vector, diagTensor>::New(tf2); divide(tRes(), f1, tf2()); reuseTmp<vector, diagTensor>::clear(tf2); return tRes;
	} 
	TEMPLATE tmp<Field<vector>> operator / ( const tmp<Field<vector>>& tf1, const UList<diagTensor>& f2 )
	{
		tmp<Field<vector>> tRes = reuseTmp<vector, vector>::New(tf1); divide(tRes(), tf1(), f2); reuseTmp<vector, vector>::clear(tf1); return tRes;
	} TEMPLATE tmp<Field<vector>> operator / ( const tmp<Field<vector>>& tf1, const tmp<Field<diagTensor>>& tf2 ) { tmp<Field<vector>> tRes = reuseTmpTmp<vector, vector, vector, diagTensor>::New(tf1, tf2); divide(tRes(), tf1(), tf2()); reuseTmpTmp<vector, vector, vector, diagTensor>::clear(tf1, tf2); return tRes; }
		
	TEMPLATE void divide ( Field<vector>& res, const vector& s1, const UList<diagTensor>& f2 )
	{
		TFOR_ALL_F_OP_S_OP_F(vector, res, =, vector, s1, /, diagTensor, f2)
	} 
	TEMPLATE tmp<Field<vector>> operator / ( const vector& s1, const UList<diagTensor>& f2 )
	{
		tmp<Field<vector>> tRes(new Field<vector>(f2.size())); divide(tRes(), s1, f2); return tRes;
	} 
	TEMPLATE tmp<Field<vector>> operator / ( const vector& s1, const tmp<Field<diagTensor>>& tf2 )
	{
		tmp<Field<vector>> tRes = reuseTmp<vector, diagTensor>::New(tf2); divide(tRes(), s1, tf2()); reuseTmp<vector, diagTensor>::clear(tf2); return tRes;
	} 
	TEMPLATE void divide ( Field<vector>& res, const UList<vector>& f1, const diagTensor& s2 )
	{
		TFOR_ALL_F_OP_F_OP_S(vector, res, =, vector, f1, /, diagTensor, s2)
	} 
	TEMPLATE tmp<Field<vector>> operator / ( const UList<vector>& f1, const diagTensor& s2 )
	{
		tmp<Field<vector>> tRes(new Field<vector>(f1.size())); divide(tRes(), f1, s2); return tRes;
	} 
	TEMPLATE tmp<Field<vector>> operator / ( const tmp<Field<vector>>& tf1, const diagTensor& s2 )
	{
		tmp<Field<vector>> tRes = reuseTmp<vector, vector>::New(tf1); divide(tRes(), tf1(), s2); reuseTmp<vector, vector>::clear(tf1); return tRes;
	}


		template<>
	tmp<Field<diagTensor> > transformFieldMask<diagTensor>
		(
			const tensorField& tf
			)
	{
		tmp<Field<diagTensor> > ret(new Field<diagTensor>(tf.size()));

		ret().component(diagTensor::XX) = tf.component(tensor::XX);
		ret().component(diagTensor::YY) = tf.component(tensor::YY);
		ret().component(diagTensor::ZZ) = tf.component(tensor::ZZ);

		return ret;
	}

	template<>
	tmp<Field<diagTensor> > transformFieldMask<diagTensor>
		(
			const tmp<tensorField>& ttf
			)
	{
		tmp<Field<diagTensor> > ret =
			transformFieldMask<diagTensor>(ttf());
		ttf.clear();
		return ret;
	}


	template<>
	tmp<Field<diagTensor> > transformFieldMask<diagTensor>
		(
			const symmTensorField& stf
			)
	{
		tmp<Field<diagTensor> > ret(new Field<diagTensor>(stf.size()));

		ret().component(diagTensor::XX) = stf.component(symmTensor::XX);
		ret().component(diagTensor::YY) = stf.component(symmTensor::YY);
		ret().component(diagTensor::ZZ) = stf.component(symmTensor::ZZ);

		return ret;
	}

	template<>
	tmp<Field<diagTensor> > transformFieldMask<diagTensor>
		(
			const tmp<symmTensorField>& tstf
			)
	{
		tmp<Field<diagTensor> > ret =
			transformFieldMask<diagTensor>(tstf());
		tstf.clear();
		return ret;
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <undefFieldFunctionsM.hxx>